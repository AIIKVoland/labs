const int PIN_TRIG = 8; // Задаем пин триггера первого ультразвукового датчика
const int PIN_ECHO = A0; // Задаем пин эхо первого ультразвукового датчика
const int PIN_TRIG_2 = 9; // Задаем пин триггера второго ультразвукового датчика
const int PIN_ECHO_2 = A1; // Задаем пин эхо второго ультразвукового датчика
const int PIN_TRIG_3 = 10; // Задаем пин триггера третьего ультразвукового датчика
const int PIN_ECHO_3 = A2; // Задаем пин эхо третьего ультразвукового датчика
const int PIN_TRIG_4 = 11; // Задаем пин триггера четвертого ультразвукового датчика
const int PIN_ECHO_4 = A3; // Задаем пин эхо четвертого ультразвукового датчика
const int BUTTON_PIN1 = 5; // Задаем пин для первой кнопки
const int BUTTON_PIN2 = 4; // Задаем пин для второй кнопки
const int BUTTON_PIN3 = 3; // Задаем пин для третьей кнопки
const int BUTTON_PIN4 = 2; // Задаем пин для четвертой кнопки


// Функция для измерения расстояния
unsigned long measureDistance(int PIN_TRIG, int PIN_ECHO) {
digitalWrite(PIN_TRIG, LOW); // Устанавливаем пин триггера в низкий уровень
delayMicroseconds(2); // Задержка на 2 микросекунды
digitalWrite(PIN_TRIG, HIGH); // Устанавливаем пин триггера в высокий уровень
delayMicroseconds(10); // Задержка на 10 микросекунд
digitalWrite(PIN_TRIG, LOW); // Устанавливаем пин триггера в низкий уровень

unsigned long duration = pulseIn(PIN_ECHO, HIGH); // Измеряем длительность импульса на пине эхо
unsigned long distance = duration * 0.034 / 2; // Рассчитываем расстояние на основе времени

return distance; // Возвращаем расстояние
}

void setup() {
// Инициализация пинов для ультразвуковых датчиков и кнопок
pinMode(PIN_TRIG, OUTPUT);
pinMode(PIN_ECHO, INPUT);
pinMode(PIN_TRIG_2, OUTPUT);
pinMode(PIN_ECHO_2, INPUT);
pinMode(PIN_TRIG_3, OUTPUT);
pinMode(PIN_ECHO_3, INPUT);
pinMode(PIN_TRIG_4, OUTPUT);
pinMode(PIN_ECHO_4, INPUT);
pinMode(BUTTON_PIN1, INPUT);
pinMode(BUTTON_PIN2, INPUT);
pinMode(BUTTON_PIN3, INPUT);
pinMode(BUTTON_PIN4, INPUT);

Serial.begin(9600); // Инициализация последовательного порта

}

void loop() {
// Измерение расстояний и считывание состояний кнопок
unsigned long distance1 = measureDistance(PIN_TRIG, PIN_ECHO);
unsigned long distance2 = measureDistance(PIN_TRIG_2, PIN_ECHO_2);
unsigned long distance3 = measureDistance(PIN_TRIG_3, PIN_ECHO_3);
unsigned long distance4 = measureDistance(PIN_TRIG_4, PIN_ECHO_4);

int buttonState1 = digitalRead(BUTTON_PIN1);
int buttonState2 = digitalRead(BUTTON_PIN2);
int buttonState3 = digitalRead(BUTTON_PIN3);
int buttonState4 = digitalRead(BUTTON_PIN4);

// Вывод расстояний в монитор последовательного порта
Serial.print("Distance 1: ");
Serial.print(distance1);
Serial.println(" cm");

Serial.print("Distance 2: ");
Serial.print(distance2);
Serial.println(" cm");

Serial.print("Distance 3: ");
Serial.print(distance3);
Serial.println(" cm");

Serial.print("Distance 4: ");
Serial.print(distance4);
Serial.println(" cm");

// Вывод состояний кнопок
Serial.print("Button 1: ");
Serial.println(buttonState1);

Serial.print("Button 2: ");
Serial.println(buttonState2);

Serial.print("Button 3: ");
Serial.println(buttonState3);

Serial.print("Button 4: ");
Serial.println(buttonState4);

// Задержка между измерениями
delay(500);
}