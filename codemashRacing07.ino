#include <DualMC33926MotorShield.h>
DualMC33926MotorShield md;

float minHeartrate = 60;                                      // pulse sensors highest speed at this heartrate
float maxHeartrate = 140;                                     // pulse sensors highest speed at this heartrate
float minSpeed = 200;                                         // the minimal speed the cars can drive
float maxSpeed = 400;                                         // the maximal speed the cars can drive

float currentMaxSpeed[] = {0, 0};                             // storring the current Max speed information

float car1speed[] = {0, 0};                                   // current speed of the cars

// pin declarations
// motor pins: 4,7,8,9,10,12,A0,A1
int lightBarrierPins[] = {2, 3};                              // interupts for light barriers
int trottlePins[] = {A4, A5};

boolean lightBarrier[] = {false, false};

long outputTimer = 0;                                         // timer variable for pulse output
long outputTimeout = 20;                                      // time to next pulse info

long myTimer1 = 0;                                            // timer for light barriers
long myTimer2 = 0;                                            // timer for light barriers
//int timeout = 100;
int sensorTimeout = 300;                                      // shortest time to break the light barrier again

void stopIfFault() {                                          // if motorshield fails
  /*if (md.getFault())
    {
    Serial.println("motorshield failure");
    while (1);
    }*/
}

void setup() {
  Serial.begin(250000);                                       // speed to talk to processing

  Serial.println("Trying to init the motor shield.");
  md.init();                                                  // initialising of the motor shield
  Serial.println("Motor shield initialised.");

  pinMode(lightBarrierPins[0], INPUT);                                           // interrupt for light barrier
  pinMode(lightBarrierPins[1], INPUT);                                           // interrupt for light barrier
  attachInterrupt(digitalPinToInterrupt(lightBarrierPins[0]), carOn1, HIGH);     // interrupt for light barrier
  attachInterrupt(digitalPinToInterrupt(lightBarrierPins[1]), carOn2, HIGH);     // interrupt for light barrier

}

void loop() {



  car1speed[0] = map(analogRead(trottlePins[0]), 140, 0, 0, 400);
  car1speed[1] = map(analogRead(trottlePins[1]), 140, 0, 0, 400);

  //currentMaxSpeed[0]=minSpeed+(constrain(pulseSensor.getBeatsPerMinute(0),minHeartrate,maxHeartrate)/maxHeartrate)*(maxSpeed-minSpeed);
  //currentMaxSpeed[1]=minSpeed+(constrain(pulseSensor.getBeatsPerMinute(1),minHeartrate,maxHeartrate)/maxHeartrate)*(maxSpeed-minSpeed);

  car1speed[0] = constrain(car1speed[0], 0, currentMaxSpeed[0]);
  car1speed[1] = constrain(car1speed[1], 0, currentMaxSpeed[1]);

  if (outputTimer + outputTimeout < millis()) {
    //Serial.print("P1="); Serial.print(pulseSensor.getBeatsPerMinute(0)); Serial.print("\t");
    Serial.print("T1="); Serial.print(analogRead(trottlePins[0])); Serial.print("\t");
    Serial.print("S1="); Serial.print(car1speed[0]); Serial.print("\t");
    Serial.print("X1="); Serial.print(currentMaxSpeed[0]); Serial.print("\t");
    Serial.println("");
    //Serial.print("P2="); Serial.print(pulseSensor.getBeatsPerMinute(1)); Serial.print("\t");
    Serial.print("T2="); Serial.print(analogRead(trottlePins[1])); Serial.print("\t");
    Serial.print("S2="); Serial.print(car1speed[1]); Serial.print("\t");
    Serial.print("X2="); Serial.print(currentMaxSpeed[1]); Serial.print("\t");
    Serial.println("");
    Serial.println("");
    outputTimer = millis();
  }


}


void carOn1() {
  if (myTimer1 + sensorTimeout < millis()) {

    myTimer1 = millis();
    Serial.println("C1");
  }
}

void carOn2() {
  if (myTimer2 + sensorTimeout < millis()) {

    myTimer2 = millis();
    Serial.println("C2");
  }
}
