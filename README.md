# Kit armado de Medidor de CO2 WEMOS D1 mini
Esta es la última versión del medidor de CO2 con una placa WEMOS D1 mini utilizando un display I2C, un sensor MH-Z19C, un led simple y un buzzer. Está modelado utilizando OOP (Object Oriented Programming).

## WEMOS D1 Mini
Es una placa que cuenta con un ESP8255-ESP12F para el uso de WiFi.

### Pinout de la WEMOS
![Wemos Pinout](wemos-pinout.png)

## Librerias utilizadas:
Sensor MH-Z19:  https://github.com/piot-jp-Team/mhz19_uart 

Display: https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library 

Wifi Manager: https://github.com/tzapu/WiFiManager

En este repositorio se encuentran las librerias como archivos .zip para ser instaladas facilmente en el IDE de Arduino.

## Preparando el IDE para usar Wemos/esp8266
* Se debe abrir el IDE e ir a preferencias. Agregar el siguiente enlace ```https://arduino.esp8266.com/stable/package_esp8266com_index.json``` a la sección de Additional Board Manager URLs.
* Abrir el Boards Manager desde el menú de Placas en las herramientas, buscar ESP8266 e instalar el paquete de ESP8266 Community
* Ir al Library Manager desde el menú de Sketch e instalar el paquete ESP8266 Microgear de Chavee Issariyapat
* Seleccionar la placa WEMOS D1 R1

Y ya está todo listo para cargar código en la placa

## Driver del microcontrolador
El microcontrolador de esta placa es un CH340G, el driver para su sistema operativo correspondiente se puede descargar desde este [enlace](http://www.wch.cn/download/CH341SER_EXE.html)


## Acerca del proyecto
La información del proyecto se puede encontrar en la [página web de Jorge Aliaga](http://www.jorgealiaga.com.ar/?page_id=2864)