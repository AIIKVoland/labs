import processing.serial.*;
Serial myPort;
String resultString; // Строчная переменная для результатов

float leftPaddle, rightPaddle;//переменные для значений // датчиков изгиба
int resetButton, serveButton; // переменные для кнопок
int leftPaddleX, rightPaddleX;//горизонтальные позиции
// ракеток
int paddleHeight = 50; // вертикальный размер ракеток
int paddleWidth = 10; // горизонтальный размер ракеток
float leftMinimum = 10; // минимальное значение левого
// датчика изгиба
float rightMinimum=10;//минимальное значение правого
// датчика иѕгиба
float leftMaximum = 130; // максимальное значение левого
// датчика изгиба
float rightMaximum = 630; // максимальное значение правого

int ballSize=10;//рaзмер мячикa
int xDirection=1;//горизонтaльное нaпрaвление движения // мячикa
// влево: –1, впрaво: 1
int yDirection = 1; // вертикaльное нaпрaвление движения // мячикa
int xPos, yPos;
// вверх: –1, вниз: 1
//горизонтaльное и вертикaльное // положение мячикa

boolean ballInMotion=false;//мячик движется?
int leftScore = 0;
int rightScore = 0;

int fontSize = 36; // размер шрифта для отображения счета

void setup(){
size(640, 280); // устанавливаем размер окна апплета
String portName = Serial.list()[0];
// открываем последовательный порт:
myPort = new Serial(this, portName, 9600);
// считываем байты в буфер, пока не дойдем до // символа перевода строки (ASCII 10):
myPort.bufferUntil('\n');
// инициализируем значения датчиков:
leftPaddle = height/2;
rightPaddle = height/2;
resetButton = 0;
serveButton = 0;
// инициализируем горизонтальные позиции ракеток:
leftPaddleX = 50;
rightPaddleX = width - 50;
// рисуем фигуры без окантовки:
noStroke();
xPos = width/2;
yPos = height/2;
// создаем шрифт из третьего шрифта, доступного системе:
PFont myFont = createFont(PFont.list()[2], fontSize);
textFont(myFont);
}

void serialEvent(Serial myPort){
// считываем данные из последовательного буфера:
String inputString = myPort.readStringUntil('\n');
// отбрасываем символы возврата ракетки и перевода строки
// из строки ввода:
inputString = trim(inputString);
// очищаем переменную resultString:
resultString = "";
// разделяем входную строку по запятым и преобразовываем
// полученные фрагменты в целые числа:
int sensors[] = int(inputString.split(","));

// если получены все строки значений датчиков, используем их:
if (sensors.length == 4) {
// масштабируем данные датчиков изгиба х диапазону // ракеток:
leftPaddle = map(sensors[0], leftMinimum, leftMaximum, 0, height);
rightPaddle = map(sensors[1], rightMinimum, rightMaximum, 0, height);
// присваиваем значения кнопок соответствующим // переменным:
resetButton = sensors[2];
serveButton = sensors[3];
// добавляем значения х строке результата:
resultString += "left: "+ leftPaddle + "\tright: " + rightPaddle;
resultString += "\treset: "+ resetButton + "\tserve: " + serveButton;
}
myPort.write('\r'); // посылаем символ возврата ракетки
}

void draw(){
// задаем цвет фона и заливки для окна апплета:
background(#044f6f);
fill(#ffffff);
// рисуем левую ракетку:
rect(leftPaddleX, leftPaddle, paddleWidth, paddleHeight);
// рисуем правую ракетку:
rect(rightPaddleX, rightPaddle, paddleWidth, paddleHeight);
// вычисляем местонахождение мячика и прорисовываем его:
if(ballInMotion==true){
animateBall();
}
// если нажата кнопка подачи, запускаем мячик в движение:
if (serveButton == 1) {
ballInMotion = true;
}
//еслинажатакнопкасброса,обнуляемсчетизапускаем // мячик в движение:
if (resetButton == 1) {
leftScore = 0;
rightScore = 0;
ballInMotion = true;
}
// выводим счет на экран:
text(leftScore, fontSize, fontSize);
text(rightScore, width-fontSize, fontSize);
}

void animateBall(){
// если мячик движется влево:
if (xDirection < 0) {
// если мячик нaходится слевa от левой рaхетхи
if ((xPos <= leftPaddleX)) {
// если мячик нaходится между верхом и низом левой рaхетхи:
if((leftPaddle - (paddleHeight/2) <= yPos) && (yPos <=
leftPaddle + (paddleHeight /2))) {
// изменяем нaпрaвление гориѕонтaльного
движения нa обрaтное:
xDirection =-xDirection;
}
}
}
// если мячик движется вправо:
else {
// если мячик справа от правой ракетки
if ((xPos >= ( rightPaddleX + ballSize/2))) {
// если мячик находится между верхом и низом // правой ракетки:
if((rightPaddle - (paddleHeight/2) <=yPos) && (yPos <= rightPaddle + (paddleHeight /2))) {
// изменяем направление горизонтального
// движения на обратное:
xDirection =-xDirection;
}
}
}
// если мячик выходит за пределы окна слева:
if (xPos < 0) {
rightScore++;
resetBall();
}
// если мячик выходит за пределы окна справа:
if (xPos > width) {
leftScore++;
resetBall();
}
// не даем мячику выйти за верхний или нижний предел окна
if ((yPos - ballSize/2 < 0) || (yPos +ballSize/2 >height)) { // изменяем направление вертикального движения мячика
// на обратное:
yDirection = -yDirection;
}
// обновляем местонахождение мячика:
xPos = xPos + xDirection;
yPos = yPos + yDirection;
// рисуем мячик:
rect(xPos, yPos, ballSize, ballSize);
}

void resetBall() {
// возвращаем мячик обратно в центр окна:
xPos = width/2;
yPos = height/2;
}