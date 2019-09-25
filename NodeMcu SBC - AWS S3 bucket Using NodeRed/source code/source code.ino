#include <ESP8266WiFi.h>    //needed for the ESP8266
#include "DHT.h"                    //uncomment if using a DHT sensor with Adafruit DHT library
#define DHTPIN D3               // what digital pin we're connected to  pin2 to D4 on esp board
#define DHTTYPE DHT11 


DHT dht(DHTPIN,DHTTYPE);

long randomNumberT, randomNumberH; //randoms variables for temperature and humidity for testing
const char WEBSITE[] = "digiotai112.eu-gb.mybluemix.net"; //Static IP at Node Red do not use http or https prefix

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


void loop()
{
  
  //Change loop delay as you see fit
  delay(5000); //5 seconds, adjust as you like relative to sampling rate vs. service call quota

 
  
  float temperatureData = dht.readTemperature();
   float humidityData = dht.readHumidity();
 
  // Check if any reads failed and exit early (to try again).
  if (isnan(temperatureData) || isnan(humidityData))
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

 

  //Print to Serial monitor or Terminal of your chocice at 115200 Baud
  Serial.print("Temperature: ");
  Serial.print(temperatureData);
  Serial.print(" %\t ");
  Serial.print("Humidity: ");
  Serial.print(humidityData);
  Serial.print(" %\h");
  
 
    
WiFiClient client;  //Instantiate WiFi object, can scope from here or Globally

    //Start or API service using our WiFi Client through PushingBox then relayed to Google
    if (client.connect(WEBSITE, 80))
      { 
         randomNumberT = dht.readTemperature(); 
         randomNumberH = dht.readHumidity();
        
         Serial.print(" sending data package now \n");
         //http URl format is --->   ?variable1=value&variable2=value2
         client.print("GET /digiotai?Temperature=" + (String)randomNumberT
       + "&Humidity=" + (String) randomNumberH
 
         );
         

      // HTTP 1.1 provides a persistent connection, allowing multiple requests to be batched
      // or pipelined to an output buffer.  Careful when altering headers, they arnt forgiving!
      client.println(" HTTP/1.1"); 
      client.print("Host: ");
      client.println(WEBSITE);
      client.println("User-Agent: ESP32/1.0");
      client.println("Connection: close");
      client.println();
      Serial.print(" finished sending http headers \n");
      }
}
