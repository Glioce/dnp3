# DNP3

DNP3  
https://es.wikipedia.org/wiki/DNP3  
https://www.youtube.com/watch?v=CwMFrvins5Q  
https://www.dpstele.com/pdfs/white_papers/dnp3_tutorial.pdf  

SCADA  
https://es.wikipedia.org/wiki/SCADA  
https://www.youtube.com/watch?v=X0U8-4ZPcro  
https://na.eventscloud.com/file_uploads/ea71f859feae020526fd797b0195b9eb_SCADAforRelayTechs-SlidesNotes-HRS2019.pdf  

Open PLC 
Funciona como un servidor web que se comunica con otros dispositivos por diferentes puertos. Se pueden agregar terminales de entrada y salida con Arduino (u otros disposirivos compatibles con Arduino).  
https://github.com/thiagoralves/OpenPLC_v3  
https://github.com/thiagoralves/OpenPLC_v3/tree/development  

Pede funcionar como DNP3 Outstation  
https://openplcproject.com/reference/dnp3-outstation/  
Se debe instalar la versión "development" para usar el protocolo DNP3
(según la documentación, no funciona en Windows, pero podemos probar).

Usa las siguientes instrucciones para instalar la versión development en Linux.  
```
git clone -b development https://github.com/thiagoralves/OpenPLC_v3.git
cd OpenPLC_v3
./install.sh linux
```

Para instalar la versión estándar en Windows, usar el instalador.
La ruta de instalación no debe tener espacios.  
https://www.openplcproject.com/runtime/windows/

Puerto OpenPLC  
localhost:8080  

## Ejecutar OpenPLC Runtime
### Windows
Menú Inicio / OpenPLC Runtime  

### Linux
```
cd .../OpenPLC_v3
./start_openplc.sh
```

## Instalar ScadaBR  
### Windows  
Descargar e instalar Java Runtime Environment 6  
https://www.oracle.com/java/technologies/javase-java-archive-javase6-downloads.html  
Descargar e instalar SCADABR 1.0  
https://sourceforge.net/projects/scadabr/files/latest/download  
En los últimos ajustes de instalación cambiar el puerto a 9090 para evitar conflictos con el 8080 que usa OpenPLC  

Video de referencia
https://www.youtube.com/watch?v=OLRvenXLPtU  

Manual ScadaBR  
https://sourceforge.net/p/scadabr/wiki/Manual%20ScadaBR%20English%200%20Summary/  

## Ejecutar ScadaBR
### Windows
Ejecutar cmd como administrador  
```
cd C:\Program Files\ScadaBR\bin
startup.bat
```   

### Linux
```
sudo /opt/tomcat6/apache-tomcat-6.0.53/bin/startup.sh
```
## Configuración de OpenPLC development brach 
Este ejemplo es de una versión anterior  
https://openplc.discussion.community/post/openplc-with-scadabr-and-dnp3-10501470?pid=1311343872  

## Tutoriales lógica cableada y Beremiz Editor
https://ladderlogicworld.com  
http://www.plcs.net/contents.shtml  
https://www.youtube.com/user/andrewskvortzov/videos  

## Bibliotecas para sensor ultrasónico  
Esta funciona muy bien con AVR, pero hay algunas incompatibilidades con ESP8266  
https://bitbucket.org/teckel12/arduino-new-ping/wiki/Home  

Aquí tenermos un fork de la biblioteca anterior para ESP8266, funciona bien  
https://github.com/jshaw/NewPingESP8266  

Esta no se ha probado  
https://github.com/eadf/esp8266_ping  

**"How to show water level in ScadaBR?"**  

## Otros temas relacionados
https://en.wikipedia.org/wiki/Industrial_internet_of_things  
https://es.wikipedia.org/wiki/Protocolo_simple_de_administración_de_red  
