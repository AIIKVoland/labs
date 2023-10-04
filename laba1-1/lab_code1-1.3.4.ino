#define R_PIN 6 // Красный пин 6
#define G_PIN 3 // Зеленый пин 3
#define B_PIN 5 // Синий пин 5

void setup() {
pinMode(R_PIN, OUTPUT); // Установка пина R_PIN в режим OUTPUT (выход)
pinMode(G_PIN, OUTPUT); // Установка пина G_PIN в режим OUTPUT (выход)
pinMode(B_PIN, OUTPUT); // Установка пина B_PIN в режим OUTPUT (выход)
}

void loop() {
digitalWrite(R_PIN, 1); // Установка пина R_PIN в HIGH (включение светодиода красного цвета)
delay(1000); // Задержка 1000 миллисекунд (1 секунда)
digitalWrite(R_PIN, 0); // Установка пина R_PIN в LOW (выключение светодиода красного цвета)

digitalWrite(G_PIN, 1); // Установка пина G_PIN в HIGH (включение светодиода зеленого цвета)
delay(1000); // Задержка 1000 миллисекунд (1 секунда)
digitalWrite(G_PIN, 0); // Установка пина G_PIN в LOW (выключение светодиода зеленого цвета)

digitalWrite(B_PIN, 1); // Установка пина B_PIN в HIGH (включение светодиода синего цвета)
delay(1000); // Задержка 1000 миллисекунд (1 секунда)
digitalWrite(B_PIN, 0); // Установка пина B_PIN в LOW (выключение светодиода синего цвета)
}