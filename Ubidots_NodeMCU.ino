  



#include "UbidotsESPMQTT.h"
#include "DHT.h"        
#define DHTTYPE DHT11
#define dht_dpin D4
DHT dht(dht_dpin, DHTTYPE); 


#define WIFINAME "Your SSID" 
#define WIFIPASS "Your Password" 
#define TOKEN "Your Token"


#define Relay1 D0
#define Relay2 D1
#define Relay3 D2
#define Relay4 D3


Ubidots client(TOKEN);


void callback(char* topic, byte* payload, unsigned int length) {

  if ((String)topic == "/v1.6/devices/nodemcu/relay1/lv"){
    int mytopic = atoi(topic);
    payload[length] = '\0';
    int mymsg = atoi ((const char*)payload);

    int val1 = mymsg;
    digitalWrite(Relay1, !val1);
  }

  else if ((String)topic == "/v1.6/devices/nodemcu/relay2/lv"){

    int mytopic = atoi(topic);
    payload[length] = '\0';
    int mymsg = atoi ((const char*)payload);

    int val1 = mymsg;
    digitalWrite(Relay2, !val1);
  }
  else if ((String)topic == "/v1.6/devices/nodemcu/relay3/lv"){

    int mytopic = atoi(topic);
    payload[length] = '\0';
    int mymsg = atoi ((const char*)payload);

    int val1 = mymsg;
    digitalWrite(Relay3, !val1);
  }
  else if ((String)topic == "/v1.6/devices/nodemcu/relay4/lv")
  {

    int mytopic = atoi(topic);
    payload[length] = '\0';
    int mymsg = atoi ((const char*)payload);

    int val1 = mymsg;
    digitalWrite(Relay4, !val1);
  }
  else
  {}
}




void setup() {
  Serial.begin(115200);
  dht.begin();
  client.ubidotsSetBroker("business.api.ubidots.com");
  client.setDebug(true); 
  client.wifiConnection(WIFINAME, WIFIPASS);
  pinMode(Relay1, OUTPUT);
  pinMode(Relay2, OUTPUT);
  pinMode(Relay3, OUTPUT);
  pinMode(Relay4, OUTPUT);
  digitalWrite(Relay1, HIGH);
  digitalWrite(Relay2, HIGH);
  digitalWrite(Relay3, HIGH);
  digitalWrite(Relay4, HIGH);
  client.begin(callback);
  client.ubidotsSubscribe("nodemcu", "relay1"); 
  client.ubidotsSubscribe("nodemcu", "relay2");
  client.ubidotsSubscribe("nodemcu", "relay3");
  client.ubidotsSubscribe("nodemcu", "relay4");
}

void loop() {
  float t = dht.readTemperature();  
  float h = dht.readHumidity();

  if (!client.connected()) {
    client.reconnect();
    client.ubidotsSubscribe("nodemcu", "relay1");
    client.ubidotsSubscribe("nodemcu", "relay2");
    client.ubidotsSubscribe("nodemcu", "relay3");
    client.ubidotsSubscribe("nodemcu", "relay4"); 

  }
  client.add("Temperature",t);
  client.add("Humidity",h);
  client.ubidotsPublish("nodemcu");
  client.loop();
}
