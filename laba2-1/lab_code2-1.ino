#include <WiFi.h> 
#include <WebServer.h> 
 
const char* ssid = "ESP32"; 
const char* password = "11234567"; 
IPAddress local_ip(192,168,2,1); 
IPAddress gateway(192,168,2,1); 
IPAddress subnet(255,255,255,0); 
WebServer server(80); 
uint8_t LED1pin = 4; 
bool LED1status = LOW; 
uint8_t LED2pin = 5; 
bool LED2status = LOW; 
unsigned long serverStartTime = 0; 
 
void setup() { 
  Serial.begin(115200); 
  pinMode(LED1pin, OUTPUT); 
  pinMode(LED2pin, OUTPUT); 
  WiFi.softAP(ssid, password); 
  WiFi.softAPConfig(local_ip, gateway, subnet); 
  delay(100); 
  server.on("/", handle_OnConnect); 
  server.on("/led1on", handle_led1on); 
  server.on("/led1off", handle_led1off); 
  server.on("/led2on", handle_led2on); 
  server.on("/led2off", handle_led2off); 
  server.onNotFound(handle_NotFound); 
  server.begin(); 
  Serial.println("HTTP server started"); 
  serverStartTime = millis(); 
} 
 
void loop() { 
  server.handleClient(); 
  if (LED1status) { 
    digitalWrite(LED1pin, HIGH); 
  } else { 
    digitalWrite(LED1pin, LOW); 
  } 
  if (LED2status) { 
    digitalWrite(LED2pin, HIGH); 
  } else { 
    digitalWrite(LED2pin, LOW); 
  } 
} 
 
void handle_OnConnect() { 
  LED1status = LOW; 
  LED2status = LOW; 
  Serial.println("GPIO4 Status: OFF | GPIO5 Status: OFF"); 
  server.send(200, "text/html", SendHTML(LED1status, LED2status)); 
} 
 
void handle_led1on() { 
  LED1status = HIGH; 
  Serial.println("GPIO4 Status: ON"); 
  server.send(200, "text/html", SendHTML(true, LED2status)); 
} 
 
void handle_led1off() { 
  LED1status = LOW; 
  Serial.println("GPIO4 Status: OFF"); 
  server.send(200, "text/html", SendHTML(false, LED2status)); 
} 
 
void handle_led2on() { 
  LED2status = HIGH; 
  Serial.println("GPIO5 Status: ON"); 
  server.send(200, "text/html", SendHTML(LED1status, true)); 
} 
 
void handle_led2off() { 
  LED2status = LOW; 
  Serial.println("GPIO5 Status: OFF"); 
  server.send(200, "text/html", SendHTML(LED1status, false)); 
} 
 
void handle_NotFound() { 
  server.send(404, "text/plain", "Not found"); 
} 
 
String SendHTML(uint8_t led1stat, uint8_t led2stat) { 
  String ptr = "<!DOCTYPE html> <html>\n"; 
  ptr += "<meta http-equiv=\"Content-type\" content=\"text/html; charset=utf-8\"><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n"; 
  ptr += "<title>Управление светодиодом</title>\n"; 
  ptr += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n"; 
  ptr += "body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n"; 
  ptr += ".button {display: block;width: 80px;background-color: #3498db;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n"; 
  ptr += ".button-on {background-color: #f00a0a;}\n"; 
  ptr += ".button-on:active {background-color: #f00a0a;}\n"; 
  ptr += ".button-off {background-color: #52e820;}\n"; 
  ptr += ".button-off:active {background-color: #52e820;}\n"; 
  ptr += "p {font-size: 14px;color: #888;margin-bottom: 10px;}\n"; 
  ptr += "</style>\n"; 
  ptr += "</head>\n"; 
  ptr += "<body>\n"; 
  ptr += "<h1>ESP32 Веб сервер разработка группы Воланд</h1>\n"; 
  ptr += "<h3>Режим точка доступа WiFi (AP)</h3>\n"; 
  if (led1stat) { 
    ptr += "<p>Состояние LED1: ВКЛ.</p><a class=\"button button-off\" href=\"/led1off\">ВЫКЛ.</a>\n"; 
  } else { 
    ptr += "<p>Состояние LED1: ВЫКЛ.</p><a class=\"button button-on\" href=\"/led1on\">ВКЛ.</a>\n"; 
  } 
  if (led2stat) { 
    ptr += "<p>Состояние LED2: ВКЛ.</p><a class=\"button button-off\" href=\"/led2off\">ВЫКЛ.</a>\n"; 
  } else { 
    ptr += "<p>Состояние LED2: ВЫКЛ.</p><a class=\"button button-on\" href=\"/led2on\">ВКЛ.</a>\n"; 
  } 
  ptr += "<p>Время работы сервера: " + String((millis() - serverStartTime) / 1000) + " секунд</p>\n"; 
  ptr += "</body>\n"; 
  ptr += "</html>\n"; 
  return ptr; 
}	