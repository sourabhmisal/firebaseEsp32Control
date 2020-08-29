#define timeSeconds 10

const int relayPin = 32;

int relayStatus;
int appStatus;

void relayStateCheck(StreamData data)
{
  if (data.dataType() == "int") {
    relayStatus = data.intData();
  }
}

void relayStreamTimeoutCallback(bool timeout)
{
  if (timeout)
  {
    Serial.println();
    Serial.println("Relay Stream timeout, resuming streaming...");
    Serial.println();
  }
}
