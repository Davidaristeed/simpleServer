#include <WiFi.h>
#include <WebServer.h>
const char* wname = "ZU-STAFF";
const char* password = "G5GUQAZY2B";

//=== SETTING POT NUMBER ===
WebServer server(80);

// ----------------------------------------------
int ledPin = 2;
bool status = false;


String SendHTML(int ledPin){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>LED Control</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr +=".button {display: block;width: 80px;background-color: #3498db;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr +=".button-on {background-color: #3498db;}\n";
  ptr +=".button-on:active {background-color: #2980b9;}\n";
  ptr +=".button-off {background-color: #34495e;}\n";
  ptr +=".button-off:active {background-color: #2c3e50;}\n";
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<h1>ESP32 Web Server</h1>\n";
    ptr +="<h3>Using Station(STA) Mode</h3>\n";
  
   if(status)
  {ptr +="<p>LED1 Status: ON</p><a class=\"button button-off\" href=\"/led1off\">OFF</a>\n";}
  else
  {ptr +="<p>LED1 Status: OFF</p><a class=\"button button-on\" href=\"/led1on\">ON</a>\n";}

 
  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}

// handle functions

void handle_connect(){
    status = LOW;
    server.send(200,"text/html",SendHTML(status));

}

void handle_ledOn(){
    status = HIGH;
    server.send(200,"text/html",SendHTML(status));
}

void handle_ledOff(){
    status = LOW;
    server.send(200,"text/html",SendHTML(status));
}

// Principle code 
void setup(){
    Serial.begin(115200);
    delay(2000);
    pinMode(ledPin, OUTPUT);

      Serial.println("Connecting to ");
  Serial.println(wname);

  //connect to your local wi-fi network
  WiFi.begin(wname, password);

  //check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");  Serial.println(WiFi.localIP());

  server.on("/", handle_connect);
  server.on("/led1on", handle_ledOn);
  server.on("/led1off", handle_ledOff);
  
  //server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP server started");
}
void loop(){
    server.handleClient();
    digitalWrite(ledPin,status);
    
}
