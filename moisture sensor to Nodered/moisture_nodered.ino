#include <ESP8266WiFi.h>    //needed for the ESP8266

const char WEBSITE[] = "awsiot-nodemcu.eu-gb.mybluemix.net"; //Static IP at Node Red do not use http or https prefix

const char* MY_SSID = "ACT FIBERNET";
const char* MY_PWD =  "act12345";
const int sensor_pin = A0;

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


void loop()
{
  
  //Change loop delay as you see fit
  delay(5000); //5 seconds, adjust as you like relative to sampling rate vs. service call quota

 
  
  float moisture_percentage;
  moisture_percentage = ( 100.00 - ( (analogRead(sensor_pin)/1023.00) * 100.00 ) );
  Serial.print("Soil Moisture(in Percentage) = ");
  Serial.print(moisture_percentage);
  Serial.println("%");
 
    
WiFiClient client;  //Instantiate WiFi object, can scope from here or Globally

    //Start or API service using our WiFi Client through PushingBox then relayed to Google
    if (client.connect(WEBSITE, 80))
      { 
        
        
         Serial.print(" Data sent to Node red \n");
         //http URl format is --->   ?variable1=value&variable2=value2
         client.print("GET /moisture?moisture=" + (String)moisture_percentage
 
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
