# dnp3

DNP3  
https://es.wikipedia.org/wiki/DNP3  

SCADA  
https://es.wikipedia.org/wiki/SCADA  

Algunos dispositivos Sonoff están basados en ESP8266  
https://sonoff.tech  

Open PLC puede funcionar como DNP3 Outstation  
https://openplcproject.com/reference/dnp3-outstation/  
Se debe instalar la versión "development" para usar el protocolo DNP3
(según la documentación, no funciona en Windows, pero podríamos probar).
Escribe las siguientes instrucciones en la consola.
```
git clone -b development https://github.com/thiagoralves/OpenPLC_v3.git
cd OpenPLC_v3
./install.sh linux
```

Puerto OpenPLC  
localhost:8080  
