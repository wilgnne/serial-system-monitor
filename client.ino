#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

char recived;
String buffer;
const unsigned long TIME_OUT = 10; // timeout 10 ms
String hightBuffer;
String lowBuffer;

void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);
}

void loop() {
  // when characters arrive over the serial port...
  if (Serial.available()) {
    buffer = "";
    // wait a bit for the entire message to arrive
    delay(100);
    // clear the screen
    lcd.clear();
    // read all the available characters
    while (Serial.available() > 0) {
      buffer += char(Serial.read());
    }

    hightBuffer = buffer.substring(0 , 16);
    lowBuffer = buffer.substring(16);
    lcd.setCursor(0, 0);
    lcd.print(hightBuffer);
    lcd.setCursor(0, 1);
    lcd.print(lowBuffer);
  }
}
