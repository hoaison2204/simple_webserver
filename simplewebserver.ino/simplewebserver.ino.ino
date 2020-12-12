#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server; //turn the board into web server
uint8_t pin_led = 16;

char* SSID = "Test_WiFi";
char* password = "1234567890";

void setup() {
  // put your setup code here, to run once:
  pinMode(pin_led, OUTPUT);
 WiFi.begin(SSID, password); //connect to network
 Serial.begin(115200);
 while(WiFi.status()!=WL_CONNECTED) //check connection
 {
  Serial.print("."); // print out the dots = not connected
  delay(500);
  }
  Serial.println("");
  Serial.print("ID address: "); // will print this out ip if connected
  Serial.print(WiFi.localIP());

  server.on("/", [](){server.send(200, "text/plain", "Hello World!");}); //this will happen if u go into the website of this ip address
  server.on("/toggle", toggleLED); //call to function toggleLED, call to pin 16 in this case
  server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
server.handleClient();
}

void toggleLED()
{
  digitalWrite(pin_led, !digitalRead(pin_led));  
  server.send(204, "");
}
