/*
 * Author: Mardan
 * Date: 2019.6.10
 * Project: GuzalAida
 */
// include the library code:
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
SoftwareSerial mySerial(11, 12); // RX, TX
void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  Serial.begin(9600);
  // Print a message to the LCD.
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("Welcome to");
  lcd.setCursor(1, 1);
  lcd.print("GuzalAida CVN");
  while (!Serial) {}
  mySerial.begin(115200);
  mySerial.println("Hello");
  delay(1000);
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("connecting..."); // wait for serial port to connect. Needed for native USB port only
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.clear();
  lcd.setCursor(0, 0);
  if (mySerial.available()) {
    // print the info of seconds since reset:
    lcd.print(mySerial.read());
  }
}
