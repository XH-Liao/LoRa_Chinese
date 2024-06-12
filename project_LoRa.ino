#include <Arduino_HS300x.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED 寬度像素
#define SCREEN_HEIGHT 64 // OLED 高度像素

// 設定OLED
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

String data;

void setup() {
  Serial.begin(9600);        //設定硬體串列埠速率
  Serial1.begin(115200);      //設定軟體串列埠速率
  delay(1000);
  Serial.println("sip reset");
  Serial1.write("sip reset");    //初始化
  while(!Serial1.available()>0){} 
  Serial.println(Serial1.readString());
  delay(1000);
  
  Serial.println("mac join abp");   //設定join mode
  Serial1.write("mac join abp");
  while(!Serial1.available()>0){} 
  Serial.println(Serial1.readString());
  delay(1000);

  Serial.println("mac set_class C");
  Serial1.write("mac set_class C");    //初始化
  while(!Serial1.available()>0){} 
  Serial.println(Serial1.readString());
  delay(1000);

  Serial.println("sip set_log info");   //關閉debug模式
  Serial1.write("sip set_log info");
  while(!Serial1.available()>0){} 
  Serial.println(Serial1.readString());
  delay(500);

  Serial.println("mac save");   //儲存設定
  Serial1.write("mac save");
  while(!Serial1.available()>0){} 
  Serial.println(Serial1.readString());
  delay(500);     
  Serial.println("==============");

   // 偵測是否安裝好OLED了
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // 一般1306 OLED的位址都是0x3C
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // 顯示Adafruit的LOGO，算是開機畫面
  display.display();
  delay(1000); // 停1秒
}

void loop() {

  String data;
  String mesg = "mac tx ucnf 2 00";
  
  Serial.println(mesg);
  Serial1.write(mesg.c_str());
  while(!Serial1.available()>0){}
  data=Serial1.readString();

  int pos=data.indexOf("mac rx 2 ");
  if(pos>0)
  {
    int pos1 = data.indexOf(">> Ok");
    String info = data.substring(pos + 9, pos1 - 4);
    String goods_info = hexToString(info);

    int separatorPos = goods_info.indexOf("|");
    String goods_name = goods_info.substring(0, separatorPos);
    String goods_price = goods_info.substring(separatorPos + 1);

    Serial.println(goods_name);
    Serial.println(goods_price);
    displayGoodsInfo(goods_name, goods_price);
  }
  
  delay(5000);
}

void displayGoodsInfo(String goods_name, String goods_price) {
  
  display.clearDisplay();
  display.setTextSize(2);             // 設定文字大小
  display.setTextColor(SSD1306_WHITE);        // 1:OLED預設的顏色(這個會依該OLED的顏色來決定)
  display.setCursor(0, 0);             // 設定起始座標
  display.print(goods_name);        // 顯示商品名稱
  display.setCursor(0, 30);             // 設定起始座標
  display.print("$");
  display.print(goods_price);        // 顯示商品價格
  display.display();                  // 要有這行才會把文字顯示出來
  delay(1000);
}


String hexToString(String hex) {
  String result = "";
  for (int i = 0; i < hex.length(); i += 2) {
    // 獲取兩個字符，將它們轉換為一個十六進制數
    String byteString = hex.substring(i, i + 2);
    char byte = strtol(byteString.c_str(), NULL, 16);
    result += byte;
  }
  return result;
}