#include <Keypad.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(7,6,5,4,3,2);

const byte ROWS = 4; 
const byte COLS = 4; 

String eingabe = "";

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {11, 10, 9, 8}; 
byte colPins[COLS] = {A5, A4, A3, A2}; 

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

const String password = "1234"; // change your password here
String input_password;

void setup(){
  Serial.begin(9600);
  input_password.reserve(10);// maximum input characters
  lcd.begin(16,2);
}

void loop(){
  //char reset = '#';
  char customKey = customKeypad.getKey();
  if (customKey){
    Serial.println(customKey);
        if(customKey == '*') {
      input_password = ""; // clear input password
    } else if(customKey == '#') {
      if(password == input_password) {
        delay(1000);
        lcd.print("password is correct");
        // DO YOUR WORK HERE
        
      } else {
        lcd.print("password incorrect");
        delay(1000);
      }

      input_password = ""; // clear input password
    } else {
      input_password += customKey; // append new character to input password string
    }
    //eingabe = eingabe + customKey;
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(eingabe);
  delay(100);
}
