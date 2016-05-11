#include <DmxSimple.h>

const int numPresets = 6;                       // amount of presets
const int buttonPins[] = {1,2,3,4,5,6};      // buttons pins
const int potPin = A0;                          // pot meter pin
const int switchPin = A1;                        // on/off switch pin
const int ledPins[] = {7,8,9,10,12,13};        // led pins
int brightness, lastBrightness;                 // brightness variables (two to measure if there is a difference)
int currentPreset = 5;                              // currently active preset

void setPreset(int preset, boolean doLightsOff = true);

void setup() {
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

  DmxSimple.usePin(11);       // set the pin that the DMX shield uses
  DmxSimple.maxChannel(512);  // set the maxchannel to the max of one dmx loop
}

void loop() {
  if(digitalRead(switchPin)) {
    on();
  } else {
    off();
  }
}

void off() {
  // switch everything off
  for(int i = 0; i < 512; i++) {
    DmxSimple.write(i,0);
  }
  setLed(-1);
}

void on() {
  // read pot pin and map to brightness
  int valuePotPin = analogRead(potPin);
  brightness = map(valuePotPin,0,1023,0,255);

  // if the potmeter is adjusted, then update the brightness by setting the preset
  if(lastBrightness != brightness) {
    lastBrightness = brightness;
    setPreset(currentPreset, false);
  }

  // read buttons and do preset if a button is pressed
  for(int i = 0; i < numPresets;i++) {
    int valueButtonPin = digitalRead(buttonPins[i]);
    if(valueButtonPin == HIGH) {
      setPreset(i);
    }
  }
}

// activate the preset and its led
void setPreset(int preset, boolean doLightsOff) {  
  currentPreset = preset;   // save the preset that is being set (we need it when updating the brightness
  setLed(preset);           // and set the right led 

  // switch all lights off
  if(doLightsOff) lightsOff();
  
  switch(preset) {
    case 0: { // presentation
        int channels[] = {34,38,42,46,  49,50,51, 57,58,59, 65,66,67, 73,74,75};
        setScene(channels, 16);
      }
      break;
    case 1: { // exhibition
        int channels[] = {33,34,37,38,41,42,45,46};
        setScene(channels, 8);
      }
      break;
    case 2: { // work
        int channels[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16, 
                          33,34,37,38,41,42,45,46, 
                          49,50,51, 57,58,59, 65,66,67, 73,74,75,
                          81,82,83,84,  86,87,88,89, 91,92,93,94 };
        setScene(channels, 48);
      }
      break;
    case 3: { // cozy
        int channels[] = {1,2, 5,6, 9,10, 13,14,  17,18,  21,22,
                          34,38,42,46,
                          49,51, 57,59, 65,67, 73,75,
                          81,84, 86,88, 91,93 };
        setScene(channels, 30);
      }
      break;
    case 4: { // funky / brainstorm
        int channels[] = {1,2, 5,8, 9,10, 13,16,  17,19,  21,22,
                          34,38,42,46,
                          49,51, 57,59, 65,67, 73,75,
                          81,83,84, 86,87,89, 92,93,94 };
        setScene(channels, 33);
      }
      break;
    case 5: { // blackout
        lightsOff();
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
  // if LED isn't zero then switch the right one on
  if(led >= 0) {
    digitalWrite(ledPins[led],HIGH);  
  } 
}

void setScene(int* channels, int n) {
  // turn the right channels on
  for(int c = 0; c < n; c++) {
    DmxSimple.write(channels[c],brightness);
  }
}

void lightsOff() {
  for(int i = 0; i < 512;i++) {
    DmxSimple.write(i,0);
  }
}



