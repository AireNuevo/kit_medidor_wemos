/*----------------------------------------------------------
    Librería para crear objeto Medidor
  ----------------------------------------------------------*/
#ifndef MEDIDOR_H
#define MEDIDOR_H
#include <Arduino.h>

#define STR_LEN 12
#define NOTE_C7  2093

class Medidor {
private:
  byte rx_pin;
  byte tx_pin;
  byte led_pin;
  byte buzzer_pin;
  byte pulsador_pin;
  String numero_de_serie;
  
  char str_to_print[STR_LEN]={'A','i','r','e',' ','N','u','e','v','o'}; 
  void displayPrint(int posicion, int linea, String texto);
  void scrollingText(uint8_t scrolled_by);
  
public:
  Medidor(void);
  void imprimirCO2(int co2ppm);
  void imprimirTemp(int temp);
  void imprimirPantalla(int co2ppm, int temp);
  void logoUNAHUR();
  void scrollAireNuevo();
  void calibrar();
  void sonarAlarma(int duracionNota);
  void prenderLed();
  void apagarLed();
  void alarma(int veces, int duracionNota);
  void iniciar();
  void calentar();
  void verificarEstadoPulsador();
  void presentarMedidor();
  void sensarCO2();
};


#endif
