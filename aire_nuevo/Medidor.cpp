#include "Medidor.h"
#include <MHZ19_uart.h>     
#include <LiquidCrystal_I2C.h>
#include <Wire.h> 

MHZ19_uart sensor;
LiquidCrystal_I2C display(0x27,16,2);  

Medidor::Medidor(void) {
  rx_pin = 13;
  tx_pin = 15;
  led_pin = 16;
  buzzer_pin = 14;
  pulsador_pin = 12;
  numero_de_serie = "0000"; 
}

void Medidor::iniciar() {
  pinMode(led_pin, OUTPUT);
  pinMode(buzzer_pin, OUTPUT);
  pinMode(pulsador_pin, INPUT_PULLUP);
  Serial.begin(9600); 
  display.begin();          
  display.clear();
  display.backlight();
  alarma(1, 250);
  Serial.print("N° de serie " + numero_de_serie + "\n");
  Serial.print("INICIANDO \n");
  displayPrint(0, 0, "N/S: " + numero_de_serie);
  displayPrint(0, 1, "INICIANDO");       
  logoUNAHUR();
  delay(10000);
  calentar();
}

void Medidor::calentar() {
  display.clear();
  sensor.begin(rx_pin, tx_pin); 
  sensor.setAutoCalibration(false);
  Serial.print("Calentando, espere 1 minuto \n");
  displayPrint(0, 0, "Calentando");       
  displayPrint(0, 1, "Espere 1 minuto"); 
  delay(60000); 
  display.clear();
  alarma(3, 250);
}

void Medidor::verificarEstadoPulsador() {
  if (digitalRead(pulsador_pin) == LOW) {
    alarma(1, 250);
    calibrar();
  }
}

void Medidor::presentarMedidor() {
  Serial.print("AireNuevo UNAHUR \n"); 
  Serial.print("MEDIDOR de CO2 \n");  
  display.clear();
  displayPrint(0, 0, "Aire Nuevo");
  displayPrint(0, 1, "Medidor de CO2");    
  delay(500);
  scrollAireNuevo();      
  delay(5000);
}

void Medidor::sensarCO2() {
  while(sensor.getPPM() >= 1200) {  
    imprimirPantalla(sensor.getPPM(), sensor.getTemperature());
    alarma(1, 250);                             
  }
  int co2ppm = sensor.getPPM();
  int temp = sensor.getTemperature();
  imprimirPantalla(co2ppm, temp);
  if(co2ppm >= 1000){
    alarma(4, 500);             
  }
  else if(co2ppm >= 800) {
    alarma(2, 1000);
  }
  delay(10000);  
}

void Medidor::displayPrint(int posicion, int linea, String texto) {
  display.setCursor(posicion, linea);
  display.print(texto);
}

void Medidor::imprimirCO2(int co2ppm) {
  Serial.print("CO2: " + String(co2ppm) + "ppm \n");                         
  displayPrint(0, 0, "CO2: " + String(co2ppm) + "ppm");                                             
}
void Medidor::imprimirTemp(int temp) {
  Serial.print("Temp: " + String(temp) + " \n");                
  displayPrint(0, 1, "Temp: " + String(temp) + "* C"); 
}
void Medidor::imprimirPantalla(int co2ppm, int temp) {
  display.clear();
  imprimirCO2(co2ppm);
  imprimirTemp(temp);
  logoUNAHUR(); 
}

void Medidor::logoUNAHUR() {
  // Primero creamos todos los caracteres necesarios para dibujar el logo
  byte UNAHUR1[] = { 
    B11100,
    B11110,
    B11111,
    B11111,
    B11111,
    B11111,
    B01111,
    B00111
  };
  byte UNAHUR2[] = { 
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111
  };
  byte UNAHUR3[] = { 
    B00111,
    B01111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11110,
    B11100
  };
  display.createChar(0, UNAHUR1); 
  display.createChar(1, UNAHUR2); 
  display.createChar(2, UNAHUR3); 
  display.setCursor(13, 0);       
  display.write(0);               
  display.setCursor(14, 0);      
  display.write(1);
  display.setCursor(15, 0);       
  display.write(2);
  display.setCursor(13, 1);      
  display.write(2);
  display.setCursor(14, 1);      
  display.write(1);
  display.setCursor(15, 1);       
  display.write(0);
}

void Medidor::scrollingText(uint8_t scrolled_by) {
  for (uint8_t i=0;i<11;i++) {
    display.setCursor(i,0);
    if (scrolled_by>=11) scrolled_by=0;   
    if (scrolled_by<10) display.print(str_to_print[scrolled_by]);      
    else display.print(' ');                       
    scrolled_by++;
  }
}

void Medidor::scrollAireNuevo() {
  for (uint8_t i=0;i<STR_LEN;i++) {
    scrollingText(i);
    delay(500);
  }
}

void Medidor::calibrar()
{
  const long segundosEspera = 1800;        
  long segundosPasados = 0;                 
  // Print por serial
  Serial.print("COMIENZA CALIBRACION \n");  
  // Print por display
  display.clear();                       
  displayPrint(0, 0, "COMIENZA");
  displayPrint(0, 1, "CALIBRACION");
  delay(10000);                             
 
  while(segundosPasados <= segundosEspera) {                      
    if (++segundosPasados % 60 == 0) {                                                                
      Serial.print(String(segundosPasados / 60) + " minutos \n");  
    }
    display.clear();                                             
    displayPrint(0, 0, "CALIBRANDO");                  
    displayPrint(0, 1, String(segundosPasados / 60) + " minutos");
    delay(1000);
    }
  sensor.calibrateZero();                   
  Serial.print("PRIMERA CALIBRACION \n");   
  display.clear();                          
  displayPrint(0, 0, "PRIMERA");             
  displayPrint(0, 1, "CALIBRACION");     
  alarma(1, 250);                        
  delay(60000);                               
  sensor.calibrateZero();                    
  Serial.print("SEGUNDA CALIBRACION \n");
  display.clear();                            
  displayPrint(0, 0, "SEGUNDA");        
  displayPrint(0, 1, "CALIBRACION");    
  alarma(1, 250);                     
  delay(10000);
  Serial.print("CALIBRACION TERMINADA \n");
  display.clear();                         
  displayPrint(0, 0, "CALIBRACION");       
  displayPrint(0, 1, "TERMINADA");    
  alarma(5, 250);                      
  delay(10000);
}

void Medidor::prenderLed() {
  digitalWrite(led_pin, HIGH);
}

void Medidor::apagarLed() {
  digitalWrite(led_pin, LOW);
}

void Medidor::alarma(int veces, int duracionNota) {
  for(int i=0; i<veces; i++) {
    prenderLed();                                  
    sonarAlarma(duracionNota); 
    delay(duracionNota); 
    apagarLed();
  }
}

void Medidor::sonarAlarma(int duracionNota) {
  tone(buzzer_pin, NOTE_C7, duracionNota);   
  delay(duracionNota);
  noTone(buzzer_pin);
}
