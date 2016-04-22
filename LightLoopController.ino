#include <DmxSimple.h>

const int numPresets = 6;                       // amount of presets
const int buttonPins[6] = {0,1,2,3,4,5};      // buttons pins
const int potPin = A0;                          // pot meter pin
const int ledPins[6] = {6,7,8,9,10,11};        // led pins
int brightness, lastBrightness;                 // brightness variables (two to measure if there is a difference)
int currentPreset;                              // currently active preset

void setup() {
  // serial  
  Serial.begin(9600);
  Serial.println("Boot lightcontroller");

  // init button pins
  for(int i = 0;i < numPresets; i++) {
    pinMode(buttonPins[i],INPUT);
  }
  // init pot meter pin
  pinMode(potPin,INPUT);
  
  // init led pins
  for(int i = 0;i < numPresets; i++) {
    pinMode(ledPins[i],OUTPUT);
  }

  DmxSimple.usePin(10);       // set the pin that the DMX shield uses
  DmxSimple.maxChannel(512);  // set the maxchannel to the max of one dmx loop
}

void loop() {
  // read pot pin and map to brightness
  int valuePotPin = analogRead(potPin);
  brightness = map(valuePotPin,0,1023,0,255);

  // if the potmeter is adjusted, then update the brightness by setting the preset
  if(lastBrightness != brightness) {
    lastBrightness = brightness;
    setPreset(currentPreset);
  }

  // read buttons and do preset if a button is pressed
  for(int i = 0; i < numPresets;i++) {
    int valueButtonPin = digitalRead(buttonPins[i]);
    if(valueButtonPin) {
      setPreset(i);
    }
  }
}

// activate the preset and its led
void setPreset(int preset) {
  Serial.print("Set preset nr: ");
  Serial.println(preset);
  
  currentPreset = preset;   // save the preset that is being set (we need it when updating the brightness
  setLed(preset);           // and set the right led 
  switch(preset) {
    case 0: // presentation

      break;
    case 1: // exhibition

      break;
    case 2: // work

      break;
    case 3: // cozy

      break;
    case 4: // funky / brainstorm

      break;
    case 5: // blackout
      for(int i = 0; i < 512;i++) {
        DmxSimple.write(i,0);
      }
      break;
    default:
      // do nothing
      break;
  }
}

void setLed(int led) {
  // first switch all the leds off
  for(int i = 0; i < numPresets; i++) {
    digitalWrite(ledPins[i],LOW);
  }
  // and then switch the right one on
  digitalWrite(ledPins[led],HIGH);
}




