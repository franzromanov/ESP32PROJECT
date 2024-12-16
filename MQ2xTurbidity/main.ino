/*
 * Abnormal_condition>>TurbidityAbove_buffer | Gas detected | user_command
 * 
 */

#include "library_all.h"
#include "IoT_Mod.h"
#include "menu.h"
#include "sense.h"
uint8_t detected_gas,turbidty_danger,user_command;
unsigned long startClock,currentClock;
const unsigned NormalDuration=7200000;

void setup() {

  NET_START("IN UTERO", "coppernotgood666");
  startClock=millis();
  Serial.println("Clock Up"); //change to oled
}

  
void loop(){
  currentClock=millis();



  //Abnormal_condition

  while(detected_gas|turbidty_danger|user_command==1){
  
    //subProcess:sendToTelegram
    Serial.println("SeNdInG To TeLeGrAm...");//change to oled
    SEND_TO_TELEGRAM(smokeState(12),turbidityReading(13));
   
    //reset_millis
    startClock = millis(); // Reset timer for another 2 hours (optional) 
  }

  //NORMAL_CONDITION>>>
  if (currentClock - startClock >= NormalDuration) {
    
    //subProcess:sendToSheet
    Serial.println("SeNdInG To GsHeEt...");//change to oled
    SEND_TO_GSHEET(smokeState(12),turbidityReading(13));

    //subProcess:sendToTelegram
    Serial.println("SeNdInG To TeLeGrAm...");//change to oled
    SEND_TO_TELEGRAM(smokeState(12),turbidityReading(13));

    //reset_millis
    startClock = millis(); // Reset timer for another 2 hours (optional)
    
  }

     
}
