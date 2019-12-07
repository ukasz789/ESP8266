#include <ESP8266WiFi.h>
WiFiServer server(80);
void setup() {
  
WiFi.mode(WIFI_AP);
WiFi.softAP("SSID", "Password");
server.begin();
Serial.begin(115200);
IPAddress HTTPS_ServerIP = WiFi.softAPIP();

 pinMode(LED_BUILTIN, OUTPUT); 
}
void loop() {
  
WiFiClient client  = server.available();
if (!client) {
  return;
}
Serial.println("Ktos sie polaczyl");
String request = client.readStringUntil('\r');
Serial.println(request);
if (request.indexOf("/OFF") != -1) {
  
  digitalWrite(LED_BUILTIN, HIGH);
} else if (request.indexOf("/ON") != -1){

 digitalWrite(LED_BUILTIN, LOW);
}
String f = "HTTP/1.1 200 OK\r\n";
f += "Content-Type: text/html\r\n\r\n";
f += "<!DOCTYPE HTML>\r\n<html>\r\n";
f += "<h2 style=background-color:DodgerBlue;>My Intrnet of My Things</h2>";
f += "<h1>Oswietlenie</h1>";
f += "<br><input type=\"button\" name=\b1\" value=\"Turn LED ON\" onclick=\"location.href='/ON'\">";
f += "<br><br><br>";
f += "<input type=\"button\" name=\"b1\" value=\"Turn LED OFF\" onclick=\"location.href='/OFF'\">";
f += "<br><br><br>";
 
f += "</html>\n";
 
client.flush();
client.print(f);
delay(1);
Serial.println("Client disconnected");
}
