// 

// test for function

int pulsePins[] = {A2, A3};                       // the pins where the puls sensors are connected to
int ledPins[] = {5, 6};                           // the pins of the leds
int threshold = 550;

float theBPMs[] = {66, 66};

long thePulseStopwatch[] = {0, 0};
int thePulseMinTime = 500;
int thePulseMaxTime = 1500;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(250000);
  pinMode(ledPins[0], OUTPUT);
  pinMode(ledPins[1], OUTPUT);
}



void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println(getThreshold());
  updatePulseData();
  //Serial.print(getBPM(0)); Serial.print(" - "); Serial.println(getBPM(1));
  delay(10);
}

int updatePulseData() {                                                           // write pulse data to arrays
  for (int i = 0; i < 2; i++) {
    if (analogRead(pulsePins[i]) > threshold) {
      digitalWrite(ledPins[i], HIGH);                                             // switch led on
      if (thePulseStopwatch[i] + thePulseMinTime < millis()) {      // not under the time for a regular pulse
        if (thePulseStopwatch[i] + thePulseMaxTime > millis()) {    // in regular time for a pulse
          float bpm=60000/(millis()-thePulseStopwatch[i]);          // this is the duration from one pulse to the next
          if (bpm>theBPMs[i]) theBPMs[i]++;
          if (bpm<theBPMs[i]) theBPMs[i]--;
          Serial.print(i);Serial.print(" ");Serial.println(theBPMs[i]);
        }
        thePulseStopwatch[i] = millis();
      }
    } else {
      digitalWrite(ledPins[i], LOW);                                              // switch led off
    }
  }
}

int getBPM(int myIndex) {
  float theReturn = 0;
  return int(theReturn);
}
