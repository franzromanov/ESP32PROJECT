#include "IoT_Mod.h"
#include "menu.h"
#include "sense.h"

void setup() {
  NET_START("IN UTERO", "coppernotgood666");
 
}

  
void loop(){



     //subProcess:sendToSheet
     SEND_TO_GSHEET(smokeState(12),turbidityReading(13));
     //subProcess:sendToTelegram
     SEND_TO_TELEGRAM(smokeState(12),turbidityReading(13))
}
