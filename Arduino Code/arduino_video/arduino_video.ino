#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <TimerOne.h>
#include "SdFat.h"

SdFat SD;

File file;

Adafruit_SSD1306 OLED(4);

void setup() {
  OLED.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  OLED.clearDisplay();
  OLED.display();
  Serial.begin(115200);
  
  Serial.println("Initializing SD card...");
  if (!SD.begin(4)) {
    Serial.println("COULD NOT INITIALIZE SD CARD");
    return;
  }

  Serial.println("Loading file...");
  file = SD.open("video.rawr", FILE_READ);
  if (!file){
    Serial.print("COULD NOT LOAD FILE");
    return;
  }
  
  Serial.println("Done.");
  while (1){
    displayFrame();
  }
}

void loop() {
  // Do Nothing...
}

void displayFrame(void)
{
  byte b = 0x00;
  for (int y = 0; y < 64; y++){
    for (int x = 0; x < 128; x += 8){
      b = file.read();
      OLED.drawPixel(x, y, b & 0x01);
      OLED.drawPixel(x + 1, y, (b >> 1) & 0x01);
      OLED.drawPixel(x + 2, y, (b >> 2) & 0x01);
      OLED.drawPixel(x + 3, y, (b >> 3) & 0x01);
      OLED.drawPixel(x + 4, y, (b >> 4) & 0x01);
      OLED.drawPixel(x + 5, y, (b >> 5) & 0x01);
      OLED.drawPixel(x + 6, y, (b >> 6) & 0x01);
      OLED.drawPixel(x + 7, y, (b >> 7) & 0x01);
    }
  }
  OLED.display();
}
