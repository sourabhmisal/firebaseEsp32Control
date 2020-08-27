/*****PIR CONTROL CODE ****/


#include <FirebaseESP32HTTPClient.h>
#include <FirebaseJson.h>
#include <FirebaseESP32.h>
#include <WiFi.h>

#define FIREBASE_HOST "esp32-firebase-project-61b02.firebaseio.com"
#define FIREBASE_AUTH "TozK3NEEAguQ195XUFoZS2GdvYnPcOTgycYT7rEy"
#define WIFI_SSID "HQEuclidAI"
#define WIFI_PASSWORD "alanturing"

#define timeSeconds 10

const int MOTION_SENSOR_PIN = 27;

int motionStateCurrent = LOW;
int motionStatePrevious = LOW;

bool startTimer=0;
unsigned long lastTrigger=0;

FirebaseData firebaseData1;
FirebaseData firebaseData2;
FirebaseData firebaseData3;
const int swPin = 26;
bool swState = false;
String path = "/test_house/light";
String nodeID = "status";
String pirControl = "pirControl";
String pirOutput="pirOutput";

int pir_st;
void streamCallback(StreamData data)
{
  if (data.dataType() == "int" && !pir_st) {
    if (!data.intData())
      Serial.println("Set " + nodeID + " to High");
    else
      Serial.println("Set " + nodeID + " to Low");
    digitalWrite(swPin, !data.intData());
  }
}
void streamCallback2(StreamData data)
{
  if (data.dataType() == "int") {

    pir_st= data.intData();
  }
}

void streamTimeoutCallback(bool timeout)
{
  if (timeout)
  {
    Serial.println();
    Serial.println("Stream timeout, resuming streaming...");
    Serial.println();
  }
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(swPin, OUTPUT);
  pinMode(MOTION_SENSOR_PIN, INPUT);
  Serial.println();
  Serial.println();
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  Serial.println("RELAY CONTROL ESP32");

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  if (!Firebase.beginStream(firebaseData1, path + "/" + nodeID) || !Firebase.beginStream(firebaseData2, path + "/" + pirControl) )
  {
    Serial.println("Could not begin stream");
    Serial.println("REASON: " + firebaseData1.errorReason());
    Serial.println();
  }

 // Firebase.setStreamCallback(firebaseData1, streamCallback, streamTimeoutCallback);
  Firebase.setStreamCallback(firebaseData2, streamCallback2, streamTimeoutCallback);
}

void loop() {
  if(pir_st) {
  
   // motionStatePrevious = motionStateCurrent;
    //motionStateCurrent = digitalRead(MOTION_SENSOR_PIN);
    Firebase.setInt(firebaseData3, path + "/" + pirOutput, digitalRead(MOTION_SENSOR_PIN));
   
    Serial.println(digitalRead(MOTION_SENSOR_PIN));/*if (motionStatePrevious == LOW && motionStateCurrent == HIGH) {
      Serial.println("Motion detected!");
      digitalWrite(swPin, LOW);
      startTimer = true;
      lastTrigger = millis();
    }
    
    if (motionStatePrevious == HIGH && motionStateCurrent == HIGH) {  
      lastTrigger = millis();
    }
    
    if(startTimer && (millis() - lastTrigger > (timeSeconds*1000))) {  
      Serial.println("Motion stopped...");
      digitalWrite(swPin, HIGH);
      Serial.println("Relay switched off...");
      startTimer = false;
    }*/
    
    Serial.println("pir_ has access");
  }
  else {
    Serial.println("pir_ dont has access");
  }
}
