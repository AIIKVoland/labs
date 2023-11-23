#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
char stringToMorseCode[] = "";
int j=0;
int light = 2;
int audio8 = 8; // к контакту 8 подключен зуммер
int note = 1200; // music note/pitch (используемый тон)
int dotLen = 100; // length of the morse code 'dot'(длительность звучания точки)
int dashLen = dotLen * 3; // length of the morse code 'dash' (длительность звучания тире)
int pinCS = 10;
int numberOfHorizontalDisplays = 1;          // Количество матриц по горизонтали
int numberOfVerticalDisplays = 4;
void setup() {
Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  pinMode(light, OUTPUT);
  
}
void loop()
{
  j=0;
char inChar = 0;
char inData[100] = ""; // data length of 6 characters
String variable = "";
String variable1 = "";
int index1 = 0;
if ( Serial.available() > 0 ) { // если в последовательном порту есть принятые данные
  while (Serial.available() > 0 && index1 < 100) // read till 6th character
{
delay(100);
inChar = Serial.read(); // начинаем их последовательно считывать и сохранять в символьный массив (по одному символу)
inData[index1] = inChar;
index1++;
inData[index1] = '\0'; // добавляем 0 в конец
}
variable.toUpperCase(); // преобразуем нижний регистр в верхний
for (byte i = 0 ; i < 100 ; i++) {
variable.concat(String(inData[i])); // объединяем строки
}
delay(20);
}
String stringToMorseCode = String(variable);
for (int i = 0; i < sizeof(stringToMorseCode) - 1; i++)
{
char tmpChar = stringToMorseCode[i];
tmpChar = toLowerCase(tmpChar);
GetChar(tmpChar);
  delay(500);
  lcd.setCursor(j, 0);
  lcd.print(tmpChar);
  Serial.print(tmpChar);
  j ++;
  
}
}
void MorseDot()
{
tone(audio8, note, dotLen); // start playing a tone
digitalWrite(light, HIGH);
delay(dotLen); // hold in this position
digitalWrite(light, LOW);
}
void MorseDash()
{
tone(audio8, note, dashLen); // start playing a tone
digitalWrite(light, HIGH);
delay(dashLen); // hold in this position
digitalWrite(light, LOW);
}
void GetChar(char tmpChar)
{
switch (tmpChar) {
case 'a':
MorseDot();
delay(100);
MorseDash();
delay(100);
break;
case 'b':
MorseDash();
delay(100);
MorseDot();
delay(100);
MorseDot();
delay(100);
  MorseDot();
delay(100);
break;
case 'c':
MorseDash();
delay(100);
MorseDot();
delay(100);
MorseDash();
delay(100);
MorseDot();
delay(100);
break;
case 'd':
MorseDash();
delay(100);
MorseDot();
delay(100);
MorseDot();
delay(100);
break;
case 'e':
MorseDot();
delay(100);
break;
case 'f':
MorseDot();
delay(100);
MorseDot();
delay(100);
MorseDash();
delay(100);
MorseDot();
delay(100);
break;
case 'g':
MorseDash();
delay(100);
MorseDash();
delay(100);
MorseDot();
delay(100);
break;
case 'h':
MorseDot();
delay(100);
MorseDot();
delay(100);
MorseDot();
delay(100);
MorseDot();
delay(100);
break;
  case 'i':
MorseDot();
delay(100);
MorseDot();
delay(100);
break;
case 'j':
MorseDot();
delay(100);
MorseDash();
delay(100);
MorseDash();
delay(100);
MorseDash();
delay(100);
break;
case 'k':
MorseDash();
delay(100);
MorseDot();
delay(100);
MorseDash();
delay(100);
break;
case 'l':
MorseDot();
delay(100);
MorseDash();
delay(100);
MorseDot();
delay(100);
MorseDot();
delay(100);
break;
case 'm':
MorseDash();
delay(100);
MorseDash();
delay(100);
break;
case 'n':
MorseDash();
delay(100);
MorseDot();
delay(100);
break;
case 'o':
MorseDash();
delay(100);
MorseDash();
delay(100);
MorseDash();
delay(100);
  break;
case 'p':
MorseDot();
delay(100);
MorseDash();
delay(100);
MorseDash();
delay(100);
MorseDot();
delay(100);
break;
case 'q':
MorseDash();
delay(100);
MorseDash();
delay(100);
MorseDot();
delay(100);
MorseDash();
delay(100);
break;
case 'r':
MorseDot();
delay(100);
MorseDash();
delay(100);
MorseDot();
delay(100);
break;
case 's':
MorseDot();
delay(100);
MorseDot();
delay(100);
MorseDot();
delay(100);
break;
case 't':
MorseDash();
delay(100);
break;
case 'u':
MorseDot();
delay(100);
MorseDot();
delay(100);
MorseDash();
delay(100);
break;
case 'v':
MorseDot();
delay(100);
MorseDot();
delay(100);
MorseDot();
delay(100);
MorseDash();
delay(100);
break;
case 'w':
MorseDot();
delay(100);
MorseDash();
delay(100);
MorseDash();
delay(100);
break;
case 'x':
MorseDash();
delay(100);
MorseDot();
delay(100);
MorseDot();
delay(100);
MorseDash();
delay(100);
break;
case 'y':
MorseDash();
delay(100);
MorseDot();
delay(100);
MorseDash();
delay(100);
MorseDash();
delay(100);
break;
case 'z':
MorseDash();
delay(100);
MorseDash();
delay(100);
MorseDot();
delay(100);
MorseDot();
delay(100);
break;
default:
break;
    

}
delay(100);
}