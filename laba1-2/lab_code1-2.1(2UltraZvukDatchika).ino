const int leftTrigPin = A0; // Задаем номер пина для подключения триггера левого датчика
const int leftEchoPin = 2; // Задаем номер пина для подключения эхо левого датчика
const int rightTrigPin = A1; // Задаем номер пина для подключения триггера правого датчика
const int rightEchoPin = 3; // Задаем номер пина для подключения эхо правого датчика
const int resetButton = 4; // Задаем номер пина для подключения кнопки сброса
const int serveButton = 5; // Задаем номер пина для подключения кнопки старта

long leftDistance = 0; // Переменная для хранения расстояния, измеренного левым датчиком
long rightDistance = 0; // Переменная для хранения расстояния, измеренного правым датчиком
int resetReading = 0; // Переменная для хранения значения, считанного с кнопки сброса
int serveReading = 0; // Переменная для хранения значения, считанного с кнопки старта

void setup() {
Serial.begin(9600); // Инициализируем последовательную связь с компьютером
pinMode(leftTrigPin, OUTPUT); // Устанавливаем пин триггера левого датчика в режим "OUTPUT" (выход)
pinMode(leftEchoPin, INPUT); // Устанавливаем пин эхо левого датчика в режим "INPUT" (вход)
pinMode(rightTrigPin, OUTPUT); // Устанавливаем пин триггера правого датчика в режим "OUTPUT" (выход)
pinMode(rightEchoPin, INPUT); // Устанавливаем пин эхо правого датчика в режим "INPUT" (вход)
pinMode(resetButton, INPUT); // Устанавливаем пин кнопки сброса в режим "INPUT" (вход)
pinMode(serveButton, INPUT); // Устанавливаем пин кнопки старта в режим "INPUT" (вход)
}

void loop() {
leftDistance = readDistance(leftTrigPin, leftEchoPin); // Считываем расстояние измеренное левым датчиком
rightDistance = readDistance(rightTrigPin, rightEchoPin); // Считываем расстояние измеренное правым датчиком

resetReading = digitalRead(resetButton); // Считываем значение кнопки сброса
serveReading = digitalRead(serveButton); // Считываем значение кнопки старта

Serial.print(leftDistance); // Отправляем на компьютер значение расстояния левого датчика
Serial.print(','); // Добавляем разделитель
Serial.print(rightDistance); // Отправляем на компьютер значение расстояния правого датчика
Serial.print(','); // Добавляем разделитель
Serial.print(resetReading); // Отправляем на компьютер значение кнопки сброса
Serial.print(','); // Добавляем разделитель
Serial.println(serveReading); // Отправляем на компьютер значение кнопки старта
}

long readDistance(int trigPin, int echoPin) {
digitalWrite(trigPin, LOW); // Устанавливаем пин триггера в "LOW" (низкий уровень)
delayMicroseconds(2); // Задержка на 2 микросекунды
digitalWrite(trigPin, HIGH); // Устанавливаем пин триггера в "HIGH" (высокий уровень)
delayMicroseconds(10); // Задержка на 10 микросекунд
digitalWrite(trigPin, LOW); // Устанавливаем пин триггера в "LOW" (низкий уровень)

long duration = pulseIn(echoPin, HIGH); // Измеряем длительность импульса приходящего с эхо датчика
long distance = (duration / 2) / 29.1; // Вычисляем расстояние на основе времени прохождения сигнала

return distance; // Возвращаем полученное расстояние
}