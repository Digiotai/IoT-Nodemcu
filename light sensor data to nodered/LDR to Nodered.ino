#include <ESP8266WiFi.h>
const char WEBSITE[] = "awsiot-nodemcu.eu-gb.mybluemix.net"; //Static IP at Node Red do not use http or https prefix

const char* MY_SSID = "ACT FIBERNET";
const char* MY_PWD =  "act12345";

void setup()
{
  Serial.begin(115200);
 // dht.begin();
  Serial.print("Connecting to "+*MY_SSID);
  WiFi.begin(MY_SSID, MY_PWD);
  Serial.println("going into wl connect");

  while (WiFi.status() != WL_CONNECTED) //not connected,  ...waiting to connect
    {
      delay(1000);
      Serial.print(".");
    }
  Serial.println("wl connected");
  Serial.println("");
  Serial.println("Credentials accepted! Connected to wifi\n ");
  Serial.println("");
}


void loop() {
  delay(3000);
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = sensorValue * (1000.0 / 1023.0);
  
  // print out the value you read:
  Serial.print("sensor value=");
  Serial.print(voltage);
 
  WiFiClient client;  //Instantiate WiFi object, can scope from here or Globally

    //Start or API service using our WiFi Client through PushingBox then relayed to Google
    if (client.connect(WEBSITE, 80))
      { 
        
        
         Serial.print(" Data sent to Node red \n");
         //http URl format is --->   ?variable1=value&variable2=value2
         client.print("GET /moisture?sensorvalue=" + (String)voltage
 
         );
         

      // HTTP 1.1 provides a persistent connection, allowing multiple requests to be batched
      // or pipelined to an output buffer.  Careful when altering headers, they arnt forgiving!
      client.println(" HTTP/1.1"); 
      client.print("Host: ");
      client.println(WEBSITE);
      client.println("User-Agent: ESP32/1.0");
      client.println("Connection: close");
      client.println();
            }

}
