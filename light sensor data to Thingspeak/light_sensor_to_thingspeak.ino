#include <ESP8266WiFi.h>
#include <Wire.h> 
// replace with your channel's thingspeak API key, 
String apiKey = "WQKSFEACDEE92GCH";
const char* ssid = "ACT FIBERNET";
const char* password = "act12345";
 
const char* server = "api.thingspeak.com";
 
WiFiClient client;
void setup() {     
  Serial.begin(115200);
  pinMode(A0,INPUT);
   WiFi.begin(ssid, password);
   
  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("connecting to....");
  Serial.println("WiFi connected");
  
}
 
 
void loop() {
  int temp = analogRead(A0);
 
  if (client.connect(server,80)) {  //   "184.106.153.149" or api.thingspeak.com
    String postStr = apiKey;
           postStr +="&field1=";
           postStr += String(temp);
           postStr += "\r\n\r\n";
 
     client.print("POST /update HTTP/1.1\n"); 
     client.print("Host: api.thingspeak.com\n"); 
     client.print("Connection: close\n"); 
     client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n"); 
     client.print("Content-Type: application/x-www-form-urlencoded\n"); 
     client.print("Content-Length: "); 
     client.print(postStr.length()); 
     client.print("\n\n"); 
     client.print(postStr);
           
 
     Serial.print("Light Sensor Value: ");
     Serial.print(temp);
       Serial.println("sent to Thingspeak");
      }
  client.stop();
   

   Serial.println("Waiting...");    
  // thingspeak needs minimum 15 sec delay between updates
  // Here I set upload every 60 seconds
  
  {
    delay(10000);                         
  }                       
}
