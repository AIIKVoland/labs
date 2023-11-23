#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
#define PRINT(s, v) { Serial.print(F(s)); Serial.print(v); }

// Define the number of devices we have in the chain and the hardware interface
// NOTE: These pin numbers will probably not work with your hardware and may
// need to be adapted
#define HARDWARE_TYPE MD_MAX72XX::PAROLA_HW
#define MAX_DEVICES 4

#define CLK_PIN   13  // or SCK
#define DATA_PIN  11  // or MOSI
#define CS_PIN    10  // or SS

// SPI hardware interface
MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);
// Arbitrary pins
//MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

// Text parameters
#define CHAR_SPACING  1 // pixels between characters

// Global message buffers shared by Serial and Scrolling functions
#define BUF_SIZE  75
char message[BUF_SIZE] = "Hello!";
bool newMessageAvailable = true;
char stringToMorseCode[] = "";
int j=0;
int light = 2;
int audio8 = 8; // к контакту 8 подключен зуммер
int note = 1200; // music note/pitch (используемый тон)
int dotLen = 100; // length of the morse code 'dot'(длительность звучания точки)
int dashLen = dotLen * 3; // length of the morse code 'dash' (длительность звучания тире)
int pinCS = 10;


void readSerial(void)
{
  static uint8_t	putIndex = 0;
}

void printText(uint8_t modStart, uint8_t modEnd, char *pMsg)
// Print the text string to the LED matrix modules specified.
// Message area is padded with blank columns after printing.
{
  uint8_t   state = 0;
  uint8_t   curLen;
  uint16_t  showLen;
  uint8_t   cBuf[8];
  int16_t   col = ((modEnd + 1) * COL_SIZE) - 1;

  mx.control(modStart, modEnd, MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);

  do     // finite state machine to print the characters in the space available
  {
    switch(state)
    {
      case 0: // Load the next character from the font table
        // if we reached end of message, reset the message pointer
        if (*pMsg == '\0')
        {
          showLen = col - (modEnd * COL_SIZE);  // padding characters
          state = 2;
          break;
        }

        // retrieve the next character form the font file
        showLen = mx.getChar(*pMsg++, sizeof(cBuf)/sizeof(cBuf[0]), cBuf);
        curLen = 0;
        state++;
        // !! deliberately fall through to next state to start displaying

      case 1: // display the next part of the character
        mx.setColumn(col--, cBuf[curLen++]);

        // done with font character, now display the space between chars
        if (curLen == showLen)
        {
          showLen = CHAR_SPACING;
          state = 2;
        }
        break;

      case 2: // initialize state for displaying empty columns
        curLen = 0;
        state++;
        // fall through

      case 3:	// display inter-character spacing or end of message padding (blank columns)
        mx.setColumn(col--, 0);
        curLen++;
        if (curLen == showLen)
          state = 0;
        break;

      default:
        col = -1;   // this definitely ends the do loop
    }
  } while (col >= (modStart * COL_SIZE));

  mx.control(modStart, modEnd, MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
}

void setup() {
Serial.begin(9600);
mx.begin();
 Serial.print("\n[MD_MAX72XX Message Display]\nType a message for the display\nEnd message line with a newline");
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
  j ++;
  
}
readSerial();
  if (newMessageAvailable)
  {
    PRINT("\nProcessing new message: ", message);
    printText(0, MAX_DEVICES-1, message);
    newMessageAvailable = false;
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