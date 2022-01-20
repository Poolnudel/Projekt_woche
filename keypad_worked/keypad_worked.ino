#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Servo.h>

Servo myservo;

LiquidCrystal lcd(7,6,5,4,3,2);

const byte ROWS = 4; 
const byte COLS = 4; 

int red_light_pin= 11;
int green_light_pin = A0;
int blue_light_pin = A1;

String eingabe = "";

int pos = 0;

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {13, 12, 9, 8}; 
byte colPins[COLS] = {A5, A4, A3, A2}; 

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup(){
  pinMode(red_light_pin, OUTPUT);
  pinMode(green_light_pin, OUTPUT);
  pinMode(blue_light_pin, OUTPUT);
  myservo.attach(10,500,2300);
  myservo.writeMicroseconds(500);
  Serial.begin(9600);
  lcd.begin(16,2);
}

void loop(){
  char customKey = customKeypad.getKey();
  if (customKey){
    eingabe = eingabe + customKey;
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(eingabe);
  delay(100);
  Serial.println(customKey);
  if (customKey == 'A') {
    RGB_color(255, 0, 0); // Red
    myservo.writeMicroseconds(500);
    eingabe = "";
    delay(1000);
    RGB_color(0, 0, 0); // 0
  }
  if (eingabe.indexOf("123") >= 0) {
    eingabe = "";
    lcd.clear();
    lcd.print("ja");
    RGB_color(0, 255, 0); // Green
    delay(1000);
    myservo.writeMicroseconds(2500);
    RGB_color(0, 0, 0); // 0 
  } 
  if (customKey == '#') {
    eingabe = "";
    lcd.clear();
  }
}

void RGB_color(int red_light_value, int green_light_value, int blue_light_value) {
  analogWrite(red_light_pin, red_light_value);
  analogWrite(green_light_pin, green_light_value);
  analogWrite(blue_light_pin, blue_light_value);
}
