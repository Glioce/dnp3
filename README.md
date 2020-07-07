# DNP3

DNP3  
https://es.wikipedia.org/wiki/DNP3  
https://www.youtube.com/watch?v=CwMFrvins5Q  

SCADA  
https://es.wikipedia.org/wiki/SCADA  
https://www.youtube.com/watch?v=X0U8-4ZPcro  

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

## Ejecutar OpenPLC Runtime
### Windows
Menú Inicio / OpenPLC Runtime  

### Linux
cd .../OpenPLC_v3
./start_openplc.sh

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
cd C:\Program Files\ScadaBR\bin
startup.sh

### Linux
sudo /opt/tomcat6/apache-tomcat-6.0.53/bin/startup.sh

## Tutoriales lógica cableada y Beremiz Editor
https://ladderlogicworld.com  
http://www.plcs.net/contents.shtml  
https://www.youtube.com/user/andrewskvortzov/videos  

## Otros temas relacionados
https://en.wikipedia.org/wiki/Industrial_internet_of_things  
https://es.wikipedia.org/wiki/Protocolo_simple_de_administración_de_red  
