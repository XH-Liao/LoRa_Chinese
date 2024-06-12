#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

void setup(void) {
  
}

void loop(void) {
  u8g2.setFont(u8g2_font_unifont_t_chinese1); //使用我們做好的字型
  u8g2.firstPage();
  do {
    u8g2.setCursor(40, 14);
    u8g2.print("特價!");  
    u8g2.setCursor(0, 40);
    u8g2.print("蘋果");
    u8g2.setCursor(0, 60);
    u8g2.print("$500");
  } while ( u8g2.nextPage() );
  delay(1000);
}