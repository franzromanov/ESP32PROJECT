#include "sense.h"

   /*

    adc= (2.25/3.3)* 2^12 [0-2800]
    y = -2572.2x² + 8700.5x - 4352.9
   
   */

float turbidityReading(uint8_t port_tb){
  int adc_val=analogRead(port_tb);
  float voltage=(adc_val/4095)*3.3;
  float calc_tb=((-2572.2)*pow(voltage,2))+(8700.5*voltage)-4352.9;
  return calc_tb;
  }

uint8_t smokeState(uint8_t port_mq2){
  uint8_t state=digitalRead(port_mq2);
  return state;
  }
