#include <PubSubClient.h>
#include <stdlib.h>
#include <ESP8266WiFi.h>

#define STASSID "HDAp"
#define STAPSK  "hd253612"

const char* ssid = STASSID;
const char* password = STAPSK;
const char* mqtt_server = "broker.mqtt-dashboard.com";

char pub_str[100];

WiFiClient espClient;
PubSubClient client(espClient);
void setup_wifi()
{

delay(10);

Serial.print("connecting to");
 Serial.println(ssid);
 WiFi.begin(ssid, password);

while (WiFi.status() != WL_CONNECTED)
 {
 delay(500);
 Serial.print("-");
 }

Serial.println();
 Serial.println("WiFi Connected");
 Serial.println("WiFi got IP");
 Serial.println();
 Serial.println(WiFi.localIP());
}


void reconnect()
{

  while(!client.connected()){
    Serial.println("Attempting MQTT connection");
    if(client.connect("myesp"))
    {
      Serial.println("Connected");
      client.publish("testtopic/1","We are re connected!!");
      //client.subscribe("...Your_topic_to_control_led...");
      //Serial.print("subscribed!");
    }
    else
    {
      Serial.print("Failed, rc = ");
      Serial.print(client.state());
      Serial.println("Waiting for 5 seconds to try again");
      delay(5000);
     }
   }
}

void setup()
{
 
 //pinMode(2, OUTPUT);
 Serial.begin(115200);
 setup_wifi();
 client.setServer(mqtt_server, 1883);
 reconnect();
}

void loop()
{

if(!client.connected())
{
reconnect();
Serial.print("disconnected");
}

//sprintf(pub_str,"%f", tmp);
//dtostrf(tmp,2,6,pub_str);
//Serial.print(pub_str);
//Serial.println(tmp);
client.publish("testtopic/1","We are connected from loop");
delay(2000);
//client.loop();
}
