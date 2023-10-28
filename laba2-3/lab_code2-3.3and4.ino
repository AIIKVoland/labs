#define WIFI_SSID "**********"   
#define WIFI_PASS "**********"   
#define BOT_TOKEN "6430240374:AAH795XhUKTs3_-IRPRtb74StcaMxOswBco"   

#include <FastBot.h>   
FastBot bot(BOT_TOKEN);

#include <KY038.h>
KY038 soundSensor(A0);

#include <KY018.h>
KY018 lightSensor(A1);

String greetings[] = {"Привет!", "Приветствую!", "Здравствуй!", "Привет-привет!"};

void setup() {  
  connectWiFi();  
  randomSeed(analogRead(0));  
  bot.attach(newMsg);  
} 

void loop() {  
  bot.tick();  
}

void newMsg(FB_msg& msg) {  
  String tem = "("+msg.chatID+", "+msg.username+", "+msg.text+")";
  
  if(msg.text == "Hello"){  
    String otp = "Привет!";  
    bot.sendMessage(otp, msg.chatID);  
    Serial.println(tem+otp);  
  } else if(msg.text == "Как дела?" || msg.text == "Как ты?"){  
    int randomIndex = random(0, sizeof(greetings)/sizeof(greetings[0]));  
    String otp = greetings[randomIndex];  
    bot.sendMessage(otp, msg.chatID);  
    Serial.println(tem+otp);  
  }
  
  if (msg.text == "/start") { 
    sendInlineKeyboard(msg.chatID); 
  } else if (msg.text == "Звук") {
    int soundLevel = soundSensor.getSoundLevel();
    String otp = "Уровень звука: " + String(soundLevel);
    bot.sendMessage(otp, msg.chatID);
    Serial.println(tem+otp);
  } else if (msg.text == "Свет") {
    int lightLevel = lightSensor.getLightLevel();
    String otp = "Уровень освещенности: " + String(lightLevel);
    bot.sendMessage(otp, msg.chatID);
    Serial.println(tem+otp);
  }
   
  Serial.println(tem);  
} 

void connectWiFi() {  
  delay(2000);  
  Serial.begin(115200);  
  Serial.println();  
  WiFi.begin(WIFI_SSID, WIFI_PASS);  
  while (WiFi.status() != WL_CONNECTED) {  
    delay(500);  
    Serial.print(".");  
    if (millis() > 15000) ESP.restart();  
  }  
  Serial.println("Connected");  
} 

void sendInlineKeyboard(String chatID) { 
  String keyboard = "[[\"Поздороваться\"],[\"Задать вопрос\"],[\"Звук\"],[\"Свет\"]]"; 
  String text = "Выберите действие:"; 
  bot.sendMessageWithInlineKeyboard(text, chatID, keyboard); 
}