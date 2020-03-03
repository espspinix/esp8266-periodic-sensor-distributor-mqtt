class LEDBlinker {
  int ledPin;
  long OnTime = 50;
  long OffTime = 10;

  unsigned long previousMillis = 0;
  int ledState = HIGH;
  int pendingBlinks = 0;
  int pendingBlinkType = 0;
  int pendingBlinkTypes[1000];

  public: LEDBlinker(int pin) {
    ledPin = pin;
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, HIGH);
  }

  void blink(int blinks, int type = 1) {
    if (pendingBlinks + blinks > 1000) return; //cannot remember more than 1000 blinks

    for (int i = 0; i < blinks; i++) {
      int pointer = pendingBlinkType + pendingBlinks + i;
      if (pointer > 1000) pointer -= 1000;
      pendingBlinkTypes[pointer] = type;
    }

    pendingBlinks += (blinks);
  }

  void update() {
    if (pendingBlinks == 0) return;

    unsigned long currentMillis = millis();
    int currentBlinkType = pendingBlinkTypes[pendingBlinkType];
    int currentOnTime = currentBlinkType * OnTime;
    int currentOffTime = currentBlinkType * OffTime;

    if((ledState == HIGH) && (currentMillis - previousMillis >= currentOnTime)) {
      ledState = LOW;  // Turn it on
      previousMillis = currentMillis;
      digitalWrite(ledPin, ledState);
    } else if ((ledState == LOW) && (currentMillis - previousMillis >= currentOffTime)) {
      ledState = HIGH;  // turn it off
      previousMillis = currentMillis;
      digitalWrite(ledPin, ledState);
      pendingBlinks--;
      pendingBlinkType++;

      if(pendingBlinkType == 1000) pendingBlinkType = 0;
    }
  }
};
