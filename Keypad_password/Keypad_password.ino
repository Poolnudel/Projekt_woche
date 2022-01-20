#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Servo.h>

Servo doorServo;
Servo lockServo;

LiquidCrystal lcd(7,6,5,4,3,2);

const byte ROWS = 4; 
const byte COLS = 4; 

int red_light_pin= 11;
int green_light_pin = A0;
int blue_light_pin = A1;

String eingabe = "";

int pos = 0;

bool pinChecked = false;

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
  pinMode(A0, OUTPUT); // EDIT 20.1
  pinMode(red_light_pin, OUTPUT);
  pinMode(green_light_pin, OUTPUT);
  pinMode(blue_light_pin, OUTPUT);
  doorServo.attach(10,500,2300);
  doorServo.writeMicroseconds(500);
  lockServo.attach(11,500,2300);
  lockServo.writeMicroseconds(500);
  Serial.begin(9600);
  lcd.begin(16,2);
}

void loop(){
  switch (pinChecked)
  {
  case true:
    analogWrite(A0, HIGH); // EDIT 20.1
    break;
    
  case false:
    analogWrite(A0, LOW); // EDIT 20.1
    break;
  
  default:
    break;
  }
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
    pinChecked = false;
    lockServo.writeMicroseconds(500);
    delay(100);
    doorServo.writeMicroseconds(500);
    eingabe = "";
    delay(1000);
  }
  if (eingabe.indexOf("123") >= 0) {
    pinChecked = true;
    eingabe = "";
    lcd.clear();
    lcd.print("ja");
    delay(1000);
    lockServo.writeMicroseconds(2500);
    delay(100);
    doorServo.writeMicroseconds(2500);
  } 
  if (customKey == '#') {
    eingabe = "";
    lcd.clear();
  }
}
