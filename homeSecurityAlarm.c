/* 
  Sketch generated by the Arduino IoT Cloud Thing "Home Security Alarm"
  https://create.arduino.cc/cloud/things/a45f1da1-e90e-485a-bded-84a767accfa2 

  Arduino IoT Cloud Variables description

  The following variables are automatically generated and updated when changes are made to the Thing

  String message_update;
  bool light_alarm;
  bool light_event;
  bool movement_alarm;
  bool movement_event;
  bool shake_alarm;
  bool shake_event;

  Variables which are marked as READ/WRITE in the Cloud Thing will also have functions
  which are called when their values are changed from the Dashboard.
  These functions are generated with the Thing and added at the end of this sketch.
*/

#include "thingProperties.h"
#include <Arduino_MKRIoTCarrier.h>
MKRIoTCarrier carrier;

int pir = A5;
int pirState = 0;
int light = 0;

String light_alarm_state = "";
String movement_alarm_state = "";
String shake_alarm_state = "";

float Gx, Gy, Gz;

uint32_t redColor = carrier.leds.Color(0,255,0);
uint32_t noColor = carrier.leds.Color(0,0,0);

void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500); 

  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
 */
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
  
  while(ArduinoCloud.connected() != 1) {
    ArduinoCloud.update();
    delay(500);
  }
  
  delay(500);
  CARRIER_CASE = false;
  carrier.begin();
  carrier.display.setRotation(0);
  delay(1500);
  pinMode(A5, INPUT);
}

void loop() {
  ArduinoCloud.update();
  // Your code here 
  pirState = digitalRead(pir);
  while(!carrier.Light.colorAvailable()) {
    delay(5);
  }
  int none;
  carrier.Light.readColor(none, none, none, light);
  
  carrier.IMUmodule.readGyroscope(Gx, Gy, Gz);
  // Serial.print("Gyroscope: ");
  //   Serial.print("\tX: ");
  //   Serial.print(Gx);
  //   Serial.print("\tY: ");
  //   Serial.print(Gy);
  //   Serial.print("\tZ: ");
  //   Serial.println(Gz);
 
  //   Serial.print("Light: ");
  //   Serial.println(light);
 
    //Serial.print("PIR State: ");
    //Serial.println(pirState);
 
    //delay(500);
  if(light_alarm == true) {
    if (light > 200) {
      light_event = true;
    }
    if (light_event == true) {
      message_update = "Light alarm breached!";
      alarm();
    }
  }
  
  if(movement_alarm == true) {
    if (pirState == true) {
      movement_event = true;
    }
    if (movement_event == true) {
      message_update = "Movement alarm breached!";
      alarm();
    }
  }
  
  if (shake_alarm == true) {
    if (Gy > 100 || Gy < -100) {
      shake_event = true;
    }
    if (shake_event == true) {
      message_update = "Shake alarm breached!";
      alarm();
    }
  }
  delay(100);
}

void alarm() {
  carrier.leds.fill(redColor, 0, 5);
  carrier.leds.show();
  carrier.Buzzer.sound(500);
  delay(500);
  
  carrier.leds.fill(noColor, 0, 5);
  carrier.leds.show();
  carrier.Buzzer.noSound();
  delay(500);
}

void updateScreen() {
  carrier.display.fillScreen(ST77XX_BLACK);
  carrier.display.setTextColor(ST77XX_WHITE);
  carrier.display.setTextSize(2);
  
  carrier.display.setCursor(25,60);
  carrier.display.print(light_alarm_state);
  carrier.display.setCursor(10, 100);
  carrier.display.print(movement_alarm_state);
  carrier.display.setCursor(30, 140);
  carrier.display.print(shake_alarm_state);
}

void onLightAlarmChange() {
  if (light_alarm == true) {
    light_alarm_state = "Light alarm: ON";
  } else {
    light_alarm_state = "Light alarm: OFF";
  }
  updateScreen();
}

void onMovementAlarmChange() {
  if (movement_alarm == true) {
    movement_alarm_state = "Movement alarm: ON";
  } else {
    movement_alarm_state = "Movement alarm: OFF";
  }
  updateScreen();
}

void onShakeAlarmChange() {
  if (shake_alarm == true) {
    shake_alarm_state = "Shake alarm: ON";
  } else {
    shake_alarm_state = "Shake alarm: OFF";
  }
  updateScreen();
}
/*
  Since MessageUpdate is READ_WRITE variable, onMessageUpdateChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onMessageUpdateChange()  {
}
/*
  Since LightAlarm is READ_WRITE variable, onLightAlarmChange() is
  executed every time a new value is received from IoT Cloud.
*/
//void onLightAlarmChange()  {
//}
/*
  Since LightEvent is READ_WRITE variable, onLightEventChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onLightEventChange()  {
}
/*
  Since MovementAlarm is READ_WRITE variable, onMovementAlarmChange() is
  executed every time a new value is received from IoT Cloud.
*/
//void onMovementAlarmChange()  {
//}
/*
  Since MovementEvent is READ_WRITE variable, onMovementEventChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onMovementEventChange()  {
}
/*
  Since ShakeAlarm is READ_WRITE variable, onShakeAlarmChange() is
  executed every time a new value is received from IoT Cloud.
*/
//void onShakeAlarmChange()  {
//}
/*
  Since ShakeEvent is READ_WRITE variable, onShakeEventChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onShakeEventChange()  {
}

