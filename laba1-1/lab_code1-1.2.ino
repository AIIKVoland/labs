// Вначале обозначаем список констант 
const int greenPin = 3;   // инициализируем пин под красный цвет
const int redPin = 6; // инициализируем пин под зеленый цвет
const int bluePin = 5;   // инициализируем пин под синий цвет
int currentPin = 0;      // текущий контакт для задания яркости
int brightness = 10;      // контакт показывающий текущий уровень яркости

void setup()
{
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop()
{
  digitalWrite(redPin, HIGH); // включает светодиод
  delay(1000); // ждет секунду
  digitalWrite(redPin, LOW); // выключает светодиод
  delay(1000); // ждет секунду
  
  digitalWrite(greenPin, HIGH); // включает светодиод
  delay(1000); // ждет секунду
  digitalWrite(greenPin, LOW); // выключает светодиод
  delay(1000); // ждет секунду
  
  digitalWrite(bluePin, HIGH); // включает светодиод
  delay(1000); // ждет секунду
  digitalWrite(bluePin, LOW); // выключает светодиод
  delay(1000); // ждет секунду
}