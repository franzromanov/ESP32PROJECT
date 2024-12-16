#include "menu.h"
const unsigned char PROGMEM bitmap []=
{
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xfe, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x3f, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xc0, 0x00, 0x00, 0x00, 
  0x00, 0x1f, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x0f, 
  0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xf8, 
  0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0xc0, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xc1, 0xff, 0xfc, 0x00, 0x00, 0x7f, 0xff, 0x83, 0xff, 
  0xf8, 0x00, 0x00, 0xff, 0xff, 0x07, 0xff, 0xf8, 0x00, 0x00, 0xff, 0xfe, 0x0f, 0xff, 0xf0, 0x00, 
  0x01, 0xff, 0xfe, 0x0f, 0xff, 0xf0, 0x00, 0x03, 0xff, 0xfc, 0x1f, 0xff, 0xe0, 0x00, 0x03, 0xff, 
  0xf8, 0x3f, 0xff, 0xc0, 0x00, 0x07, 0xff, 0xf8, 0x3f, 0xff, 0xc0, 0x00, 0x0f, 0xff, 0xf0, 0x7f, 
  0xff, 0x80, 0x00, 0x0f, 0xff, 0xe0, 0xff, 0xff, 0x00, 0x00, 0x1f, 0xff, 0xe0, 0xff, 0xff, 0x00, 
  0x00, 0x3f, 0xff, 0xc1, 0xff, 0xfe, 0x00, 0x00, 0x3f, 0xff, 0xc1, 0xff, 0xf8, 0x00, 0x00, 0x7f, 
  0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 
  0x00, 0x00, 0x00, 0x01, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xfc, 0x00, 0x00, 0x00, 
  0x00, 0x03, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x07, 
  0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
// Define OLED display width and height
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Create an SSD1306 display object
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// I2C pins for ESP32
#define I2C_SDA 21
#define I2C_SCL 22
String greet_ = "Welcome User!";
int16_t dump_x, dump_y; // Use int16_t instead of int
int16_t x_ = 0, y_ = 0; // Coordinates must be int16_t
uint16_t text_w = 0, text_h = 0; //

void oledSet(uint8_t btn_state_any){
  // Initialize I2C
  Wire.begin(I2C_SDA, I2C_SCL);

  // Initialize the SSD1306 display
  if (!display.begin(SSD1306_PAGEADDR, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  // Clear the display buffer
  display.clearDisplay();

  // Display a startup message
  display.setTextSize(1); // Set text size to 1
  display.setTextColor(SSD1306_WHITE); // Set text color
  display.drawBitmap((128-56)/2,((64-48)/2),bitmap,56,47,SSD1306_WHITE);
  display.display();  
  delay(2000);
  display.clearDisplay();

  display.getTextBounds(greet_, 0, 0, &dump_x, &dump_y, &text_w, &text_h); // Correct types
  x_ = (128 - text_w) / 2; // Center horizontally
  y_ = (64 - text_h) / 2;  // Center vertically
  display.setCursor(x_, y_);
  display.println(greet_);
  display.display();
  delay(2000); // Wait 2 seconds
  display.clearDisplay();
  display.setCursor(0,0);
  display.print("Start_Measurement\n\nPress_Any_Button!\n");
  display.display();

  while(btn_state_any==1);
  
}

void MEASUREMENT_DISPLAY(float turbidity_val, uint8_t gas_state){
  display.clearDisplay();
  display.setCursor(0,0);
  display.println("Turbidity_Value:");
  display.print(turbidity_val);
  display.print("Gas_State: ");
  display.print(gas_state);  
  greet_="halt";
  display.getTextBounds(greet_, 0, 0, &dump_x, &dump_y, &text_w, &text_h);
  x_ = (128 - text_w) ; // allign right
  y_ = (64 - text_h);  // allign right
  display.setCursor(x_,y_);
  display.print(greet_); 
}
