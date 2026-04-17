#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

U8G2_SH1106_128X64_NONAME_F_HW_I2C display(U8G2_R0, U8X8_PIN_NONE);

void setup() {
  display.begin();
}

void loop() {
  display.clearBuffer();

  display.setFont(u8g2_font_logisoso32_tf);
  display.drawStr(0, 50, "HALLO !");

  display.sendBuffer();
  delay(2000);
}
