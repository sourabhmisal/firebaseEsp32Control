#include <FirebaseESP32HTTPClient.h>
#include <FirebaseJson.h>
#include <FirebaseESP32.h>
#include <WiFi.h>

FirebaseData relayGlobalData; // relay state data to firebase

FirebaseData appInput; // app state data from firebase
