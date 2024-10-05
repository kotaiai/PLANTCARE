
#include <FirebaseArduino.h>
#include <ESP8266WiFi.h>
#include <Wire.h>
#include <DHT.h>

#define FIREBASE_HOST "plantcare-b2134-default-rtdb.firebaseio.com" //firebase>>realtime database
#define WIFI_SSID "VENTI"
#define WIFI_PASSWORD "11112222"

#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht (DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
                                                  //reads dht sensor data 
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  dht.begin();  
                                   
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.print("Connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP()); 
  Firebase.begin(FIREBASE_HOST);
}

void loop() {
  int h = dht.readHumidity();
  int t = dht.readTemperature();  
 
  Serial.print("Humidity: ");  
  Serial.print(h);
  
  Serial.print("%  Temperature: ");  
  Serial.print(t);  
  Serial.println("°C ");
   
  Firebase.setInt ("Temp",t);
  Firebase.setInt ("Humidity",h);
  delay(3000);
}