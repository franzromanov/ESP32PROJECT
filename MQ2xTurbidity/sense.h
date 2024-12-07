#include <Arduino.h>
#include <stdint.h>
#include <math.h>

//TurbiditySensor
float turbidityReading(uint8_t port_tb);

//MQ2
uint8_t smokeState(uint8_t port_mq2);
