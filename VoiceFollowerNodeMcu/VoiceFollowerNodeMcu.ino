#include <ESP8266WiFi.h>
#include  <Wire.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#define led            D1


#define WLAN_SSID       "Martin Router King"             // Your SSID
#define WLAN_PASS       "rohan420"                       // Your password

/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "io.adafruit.com"                    //Adafruit Server
#define AIO_SERVERPORT  1883                   
#define AIO_USERNAME    "rohan00_00"                         // Username
#define AIO_KEY         "e4323fb63e5940c3ab4254d666dc382f"   // Auth Key

//WIFI CLIENT
WiFiClient client;

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

Adafruit_MQTT_Subscribe Light1 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME"/feeds/movecar"); // Feeds name should be same everywhere


void MQTT_connect();
char movestate;

void setup()
{                                          //Checks wifi status
  Wire.begin(D1,D2);
  WiFi.begin(WLAN_SSID, WLAN_PASS);
   while (WiFi.status() != WL_CONNECTED)
    {delay(500);}
  mqtt.subscribe(&Light1);
  WiFi.begin(WLAN_SSID, WLAN_PASS);
   while (WiFi.status() != WL_CONNECTED) 
   {delay(500);}

}


void loop() 
{
  MQTT_connect();

  Adafruit_MQTT_Subscribe *subscription;
 while ((subscription = mqtt.readSubscription(20000))) //waits 20000 mili sec for subscription message
  {
    if (subscription == &Light1)                       //& means that it points to the data stored in Light1 and then subscription has that data???
    {
      Serial.begin(9600);
       //char* movestate=(char *)Light1.lastread;    //atoi converts to an integer value
       Wire.beginTransmission(8);
       //Wire.write(movestate);
       Wire.write((char *)Light1.lastread);//NODEmcu writes the data to arduino
        Serial.println((char *)Light1.lastread);
       Wire.endTransmission();
     }
  }
}



void MQTT_connect() {
  int8_t ret;

  if (mqtt.connected()) {
    return;
  }
  Serial.begin(9600);
  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  
  while ((ret = mqtt.connect()) != 0) {
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(5000); 
    retries--;
    if (retries == 0) {
      while (1);
    }
  }
  Serial.println("MQTT Connected!");
  
}
