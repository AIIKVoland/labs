#include <Servo.h>

#define pirPin 8
#define servoPin 9 // сигнальный провод от серво на порт 9

Servo myservo;
bool serv_angl = false;

void setup() {
  Serial.begin(9600); // Объявляем работу com порта со скоростью 9600
  pinMode(pirPin, INPUT); //Объявляем пин, к которому подключендатчик движения, входом
  myservo.attach(servoPin);
}
void loop() {
  //Считываем значения сдатчика движения. Если обнаружили движение,то транслируем сигналтревоги в монитор порта и включаем светодиод
  int pirVal = digitalRead(pirPin); 
  if(pirVal == HIGH)
  {
    //поворачиваем сервопривод на 180 градусов
    if(serv_angl){
        serv_angl = false;
        myservo.write(0);   // поворот на 0 градусов
    }
    else{
        serv_angl = true;
        myservo.write(180); // поворот на 180 градусов
    }

    Serial.print("HIGH\n");

    delay(2000);
  } else
  {
    Serial.print("LOW\n");
    delay(1000);
  }
}