#include "firebase.h"
#include "credentials.h"
#include "globalStateObject.h"

String path = "/test_house/light";
String globalID = "status";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(relayPin, OUTPUT);

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

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  if (!Firebase.beginStream(relayGlobalData, path + "/" + globalID))
  {
    Serial.println("Could not begin stream");
    Serial.println("REASON: " + relayGlobalData.errorReason());
    Serial.println();
  }
  Firebase.setStreamCallback(relayGlobalData, relayStateCheck, relayStreamTimeoutCallback);
}

void loop() {
  // put your main code here, to run repeatedly:  
  Serial.print("Relay status is ");
  Serial.println(relayStatus);
  
  if (relayStatus == 1) {
    digitalWrite(relayPin, LOW);
    Serial.println("Relay is on");
    Serial.print("Relay Pin is ");
    Serial.println(digitalRead(relayPin));
//    Firebase.setInt(relayGlobalData, path + "/" + globalID, !digitalRead(relayPin));
  }
  else { 
    digitalWrite(relayPin, HIGH);
    Serial.println("Relay is off");
    Serial.print("Relay Pin is ");
    Serial.println(digitalRead(relayPin));
//    Firebase.setInt(relayGlobalD/ata, path + "/" + globalID, !digitalRead(relayPin));
   }
}
