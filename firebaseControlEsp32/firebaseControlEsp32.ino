#include <FirebaseESP32HTTPClient.h>
#include <FirebaseJson.h>
#include <FirebaseESP32.h>
#include <WiFi.h>

#define FIREBASE_HOST "esp32-firebase-project-61b02.firebaseio.com"
#define FIREBASE_AUTH "TozK3NEEAguQ195XUFoZS2GdvYnPcOTgycYT7rEy"
#define WIFI_SSID "Naidus"
#define WIFI_PASSWORD "INspiration@234"

FirebaseData firebaseData1;

const int swPin = 19;
bool swState = false;
String path = "/Nodes";
String nodeID = "Node";

void streamCallback(StreamData data)
{
  if (data.dataType() == "boolean") {
    if (!data.boolData())
      Serial.println("Set " + nodeID + " to High");
    else
      Serial.println("Set " + nodeID + " to Low");
    digitalWrite(swPin, !data.boolData());
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

  if (!Firebase.beginStream(firebaseData1, path + "/" + nodeID))
  {
    Serial.println("Could not begin stream");
    Serial.println("REASON: " + firebaseData1.errorReason());
    Serial.println();
  }

  Firebase.setStreamCallback(firebaseData1, streamCallback, streamTimeoutCallback);
  
}

void loop() {

//  if (digitalRead(swPin) == swState) {
//    bool _swState = swState;
//    swState = digitalRead(swPin);
//  }
}
