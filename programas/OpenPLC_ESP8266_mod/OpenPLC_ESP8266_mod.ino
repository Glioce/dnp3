//-----------------------------------------------------------------------------
// Copyright 2018 Thiago Alves
// This file is part of the OpenPLC Software Stack.
//
// OpenPLC is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// OpenPLC is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with OpenPLC.  If not, see <http://www.gnu.org/licenses/>.
//------
//
// This is the main file for the OpenPLC Arduino firmware. It contains the a
// Modbus RTU library to communciate with OpenPLC host as a slave device.
//
// Thiago Alves, Aug 2018
//
// Modificado para usar sensor ultrasónico HC-SR04 en ESP-01.
// ESP-01 solo tiene 2 GPIO disponibles: GPIO0 y GPIO2.
// Esos 2 pines se conectan TRIG y ECHO del sensor ultrasónico.
// Se usa una librería para el sensor https://github.com/jshaw/NewPingESP8266
// Se dejan de utilizar dos funciones: pinConfig() y updateIO().
// En lugar de pinConfig() el modo de los pines establece con la librería.
// En lugar de updateIO() se hace una lectura con el sensor y se guarda en mb_input_regs[0]
//-----------------------------------------------------------------------------

#include <ESP8266WiFi.h>

/*********NETWORK CONFIGURATION*********/

//const char *ssid = "Totalplay-B99F";
//const char *password = "B99FA5B1ebrhC8e7";
const char *ssid = "Inventoteca_2G";
const char *password = "science_7425";

/***************************************/

#define NODE_PIN_D0		16
#define NODE_PIN_D1		5
#define NODE_PIN_D2		4
#define NODE_PIN_D3		0
#define NODE_PIN_D4		2
#define NODE_PIN_D5		14
#define NODE_PIN_D6		12
#define NODE_PIN_D7		13
#define NODE_PIN_D8		15

//uint8_t pinMask_DIN[] = { NODE_PIN_D4, NODE_PIN_D5, NODE_PIN_D6, NODE_PIN_D7 };
//uint8_t pinMask_DOUT[] = { NODE_PIN_D0, NODE_PIN_D1, NODE_PIN_D2, NODE_PIN_D3 };
uint8_t pinMask_DIN[] = { NODE_PIN_D4, NODE_PIN_D3, NODE_PIN_D6, NODE_PIN_D7 };
uint8_t pinMask_DOUT[] = { NODE_PIN_D0, NODE_PIN_D1, NODE_PIN_D2, NODE_PIN_D5 };
uint8_t pinMask_AIN[] = { A0 };
uint8_t pinMask_AOUT[] = { NODE_PIN_D8 };

unsigned char modbus_buffer[100];
int processModbusMessage(unsigned char *buffer, int bufferSize);

#include <NewPingESP8266.h>
#define TRIGGER_PIN  0
#define ECHO_PIN     2
#define MAX_DISTANCE 100
#define PERIODO_LECTURA 30 //lectura de distancia cada 30 ms (o mas)
NewPingESP8266 sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
uint16_t distancia; //guarda lectura de distancia en cm
unsigned long t_leer; //momento de leer distancia
unsigned long t; //momento actual

#include "modbus.h"

extern bool mb_discrete_input[MAX_DISCRETE_INPUT];
extern bool mb_coils[MAX_COILS];
extern uint16_t mb_input_regs[MAX_INP_REGS];
extern uint16_t mb_holding_regs[MAX_HOLD_REGS];

//Create the modbus server instance
WiFiServer server(502);

void pinConfig()
{
  pinMode(NODE_PIN_D0, OUTPUT);
  pinMode(NODE_PIN_D1, OUTPUT);
  pinMode(NODE_PIN_D2, OUTPUT);
  pinMode(NODE_PIN_D3, OUTPUT);

  pinMode(NODE_PIN_D4, INPUT);
  pinMode(NODE_PIN_D5, INPUT);
  pinMode(NODE_PIN_D6, INPUT);
  pinMode(NODE_PIN_D7, INPUT);

  pinMode(NODE_PIN_D8, OUTPUT);
}

void setup()
{
  Serial.begin(115200);
  delay(10);

  //pinConfig();
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.print("My IP: ");
  Serial.println(WiFi.localIP());

  //updateIO();
  t = millis(); //momento actual
  distancia = sonar.ping_cm(); //leer distancia
  mb_input_regs[0] = distancia; //guardar en registro de entrada analogica
  t_leer = t + PERIODO_LECTURA; //siguiente lectura cuando trascurra el periodo

  //debug
  Serial.print(t);
  Serial.print(" Ping: ");
  Serial.print(distancia);
  Serial.println(" cm");
}

void PrintHex(uint8_t *data, uint8_t length) // prints 8-bit data in hex with leading zeroes
{
  for (int i = 0; i < length; i++)
  {
    if (data[i] < 0x10)
      Serial.print("0");
    Serial.print(data[i], HEX); Serial.print(" ");
  }
  Serial.println();
}

void updateIO()
{
  for (int i = 0; i < sizeof(pinMask_DIN); i++)
  {
    mb_discrete_input[i] = digitalRead(pinMask_DIN[i]);
  }

  for (int i = 0; i < sizeof(pinMask_DOUT); i++)
  {
    digitalWrite(pinMask_DOUT[i], mb_coils[i]);
  }

  for (int i = 0; i < sizeof(pinMask_AIN); i++)
  {
    //mb_input_regs[i] = (analogRead(pinMask_AIN[i]) * 64);
    mb_input_regs[i] = 100 + (10 * mb_discrete_input[1]) + mb_discrete_input[0];
  }

  for (int i = 0; i < sizeof(pinMask_AOUT); i++)
  {
    analogWrite(pinMask_AOUT[i], mb_holding_regs[i] / 64);
  }
}

void loop()
{
  WiFiClient client = server.available();
  if (!client)
    return;

  Serial.println("new client!");

  while (client.connected())
  {
    // Wait until the client sends some data
    while (!client.available())
    {
      delay(1);
      if (!client.connected())
        return;
    }

    int i = 0;
    while (client.available())
    {
      modbus_buffer[i] = client.read();
      i++;
      if (i == 100)
        break;
    }

    //DEBUG
    //Serial.print("Received MB frame: ");
    //PrintHex(modbus_buffer, i);

    //updateIO();
    t = millis();
    if (t >= t_leer) { //ha transcurrido el periodo, es momento de leer
      distancia = sonar.ping_cm(); //leer distancia
      t_leer = t + PERIODO_LECTURA; //siguiente lectura cuando trascurra el periodo
      //debug
      Serial.print(t);
      Serial.print(" Ping: ");
      Serial.print(distancia);
      Serial.println(" cm");
    }
    mb_input_regs[0] = distancia; //guardar en registro de entrada analogica

    unsigned int return_length = processModbusMessage(modbus_buffer, i);
    client.write((const uint8_t *)modbus_buffer, return_length);
    //updateIO();
    delay(1);
  }

  Serial.println("Client disonnected");
  delay(1);
}
