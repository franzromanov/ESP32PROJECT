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
uint8_t btn1=14,btn2=26,btn3=27,ack=0;

void setup() {

  NET_START("IN UTERO", "coppernotgood666");
  Serial.begin(115200);
  pinMode(btn1, INPUT_PULLUP);
  pinMode(btn2, INPUT_PULLUP);
  pinMode(btn3, INPUT_PULLUP);
  pinMode(19,OUTPUT);
  oledSet();
}
  
void loop(){
  Serial.println(digitalRead(btn1));
  Serial.println(digitalRead(btn2));
  Serial.println(digitalRead(btn3));

  while(1){
    if(!(digitalRead(btn1)&digitalRead(btn2)&digitalRead(btn3))==0){
    oled_greet();
    delay(200);
    }else break;
    
  }
  startClock=millis();  
  
  while(digitalRead(btn1)==1){ //exit
    delay(50);//debounce
    currentClock=millis();
    float tbdt_bag=turbidityReading(13);
    uint8_t gas_state=smokeState(12); 

    MEASUREMENT_DISPLAY(tbdt_bag,gas_state);
    if(currentClock-startClock>=NormalDuration){
      //sendToGsheet&Telegram
      startClock=millis();
    }else if((((gas_state==1)|(tbdt_bag>=500))&(!(ack)))==1){
      while(1){
        display.clearDisplay();
        display.setCursor(0,0);
        display.print("-!WARNING!-\nHazard Detected\Alarm_State_ON\nPress_Middle_Button_To_Stop");
        display.display();
        alarm_on(1,19);
        delay(50);
        if(!(digitalRead(btn2))==1){
          alarm_on(0,19);
          ack=1;
          startClock=millis();
          break;
        }
        //sendToGsheet&tele
        SEND_TO_GSHEET(gas_state,tbdt_bag);
        SEND_TO_TELEGRAM(gas_state,tbdt_bag);
        delay(500);
      }
    }else if(!(digitalRead(btn3))==1){
        delay(50);//debounce
        //sendToGsheet&tele
        SEND_TO_GSHEET(gas_state,tbdt_bag);
        SEND_TO_TELEGRAM(gas_state,tbdt_bag);
        startClock=millis();    
    }
    
    }


  }

     


void alarm_on(uint8_t state,uint8_t buzz_port){
  if(state==1)digitalWrite(buzz_port,state);
  else digitalWrite(buzz_port,state);
}
