#include "IoT_Mod.h"
//globalvariable

HTTPClient http_;

void NET_START(const char ssid[64],const char password[128]){
  //connect_to_wifi 
  Serial.begin(115200);
  delay(10);

  Serial.println();
  Serial.print("[WiFi] Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (true) {

    if(WiFi.status()==WL_CONNECTED){
        Serial.println("connected");
        break;
        }


    }
    
  //end

  //connect_to_gsheet




  
  //end

  //connect_to_telegram



  //end 

}

void SEND_TO_GSHEET(uint8_t MQ2Value_,float TurbidityValue_){


  const char *sheet_url="https://script.google.com/macros/s/AKfycbxbMdlL1fzg2AwWfNaaE5qxMWCNtGiW3Q7MnGDgHHCrkHS2wLc3YsGIzm_mRNKnBsji/exec";
  String json_data_= "{\"MQ2\": "+ String(MQ2Value_) + ", \"Turbidity\": "+String(TurbidityValue_)+"}";
  http_.begin(sheet_url);
  http_.addHeader("Content-Type","application/json");
  //error-handling
  if(http_.POST(json_data_)>0){
    String response_=http_.getString();
    Serial.println("Server:" + response_);
    }else Serial.println("Server: Not Responding!");
      
  http_.end();
  
  }
  
void SEND_TO_TELEGRAM(uint8_t MQ2Value_,float TurbidityValue_){
  
  String telegram_api = "https://api.telegram.org/bot" + String(botToken) +
                      "/sendMessage?chat_id=" + String(chatID) + 
                      "&text=" + "MQ2Value:" + String(MQ2Value_) + 
                      "%0ATurbidity:" + String(TurbidityValue_);

  http_.begin(telegram_api);

  if(http_.GET()){
    String responseAPI_ = http_.getString();
    Serial.println("Telegram:" + responseAPI_);   
    }else Serial.println("Server: Not Responding!");
    
  http_.end();
  
  }
