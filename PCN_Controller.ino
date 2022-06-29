#define DCSBIOS_IRQ_SERIAL
#include "DcsBios.h"

/*******************************************************************************************/
// pins definition
/*******************************************************************************************/
// keyboard
int col1 = 15;
int col2 = 14;
int col3 = 16;
int row1 = 11; 
int row2 = 8;
int row3 = 9;
int row4 = 10;

// leds
char led0 = 12;
char led1 = 13;

// buttons
int butSelector = 18;
int but0 = 2;
int but1 = 3;
int but2 = 7;
int but3 = 6;
int but4 = 5;
int but5 = 4;

// potentiometer
int pot = 7;

// 10 positions selector switch
int swSelector = 19;
int sw0 = 10;
int sw1 = 11;
int sw2 = 9;
int sw3 = 8;
int sw4 = 7;
int sw5 = 6;
int sw6 = 5;
int sw7 = 4;
int sw8 = 3;
int sw9 = 2;

void setup() {
  DcsBios::setup();
  
  // keyboard
  pinMode(col1, OUTPUT);
  pinMode(col2, OUTPUT);
  pinMode(col3, OUTPUT);
  pinMode(row1, INPUT);
  pinMode(row2, INPUT);
  pinMode(row3, INPUT);
  pinMode(row4, INPUT);

  // leds in buttons
  pinMode(led0, OUTPUT);
  pinMode(led1, OUTPUT); 

  //buttons
  pinMode(butSelector, OUTPUT);
  pinMode(but0, INPUT);
  pinMode(but1, INPUT);
  pinMode(but2, INPUT);
  pinMode(but3, INPUT);
  pinMode(but4, INPUT);
  pinMode(but5, INPUT);

  //big switch
  pinMode(swSelector, OUTPUT);
  pinMode(sw0, INPUT);
  pinMode(sw1, INPUT);
  pinMode(sw2, INPUT);
  pinMode(sw3, INPUT);
  pinMode(sw4, INPUT);
  pinMode(sw5, INPUT);
  pinMode(sw6, INPUT);
  pinMode(sw7, INPUT);
  pinMode(sw8, INPUT);
  pinMode(sw9, INPUT);
  
  // Serial.begin(9600);
  // Serial.setTimeout(5);
}

/*******************************************************************************************/
// custom pins functions
/*******************************************************************************************/
void writeToKeyboard(bool a, bool b, bool c) {
  digitalWrite(col1, a);
  digitalWrite(col2, b);
  digitalWrite(col3, c);
}

int readKeyboard(int col) {
  if (digitalRead(row1)){
    return(1+col);
  } else if (digitalRead(row2)){
    return(4+col);
  } else if (digitalRead(row3)){
    return(7+col);
  } else if (digitalRead(row4)){
    return(10+col);
  } else {
    return(13+col);
  }
}

int lastKey = 0;
char buf[12];
void printIfNotZero(int a){
  if (a != lastKey and (a < 13 or a == 13+(lastKey+2)%3)) {
    lastKey = a;
    if (a != 0 and a < 13) {
      // Serial.println("K"+String(a));
      if (a < 10) {
        snprintf(buf, 12, "INS_BTN_%d", a);
        triggerButton(buf);
      } else if (a==10) {
        triggerButton("INS_CLR_BTN");
      } else if (a==11) {
        triggerButton("INS_BTN_0");
      } else if (a==12) {
        triggerButton("INS_ENTER_BTN");
      }
    }
  }
}

void triggerButton(String buttonName) {
  sendDcsBiosMessage(buttonName.c_str(), "1");
  sendDcsBiosMessage(buttonName.c_str(), "0");
}

int lastButton = -1;
int readButtons() {
  if (digitalRead(but0)){
    if (lastButton!=0){
      lastButton = 0;
      // Serial.println("B0");
      triggerButton("INS_PREP_SW");
    }
  } else if (digitalRead(but1)){
    if (lastButton!=1){
      lastButton = 1;
      // Serial.println("B1");
      triggerButton("INS_DEST_SW");
    }
  } else if (digitalRead(but2)){
    if (lastButton!=2){
      lastButton = 2;
      // Serial.println("B2");
    }
  } else if (digitalRead(but3)){
    if (lastButton!=3){
      lastButton = 3;
      // Serial.println("B3");
    }
  } else if (digitalRead(but4)){
    if (lastButton!=4){
      lastButton = 4;
      // Serial.println("B4");
    }
  } else if (digitalRead(but5)){
    if (lastButton!=5){
      lastButton = 5;
      // Serial.println("B5");
    }
  } else {
    lastButton = -1;
  }
}

int lastPot = 0;
int potTreshold = 200;
int readPot() {
  int potValue = analogRead(pot);
  if (abs(potValue-lastPot) > potTreshold) {
    // Serial.println("L"+String(int(potValue/10.24)));
    lastPot = potValue;
  }
}

int lastSwitch = -1;
int readSwitch() {
  if (digitalRead(sw0)){
    if (lastSwitch!=0){
      lastSwitch = 0;
      // Serial.println("S0");
      sendDcsBiosMessage("INS_PARAM_SEL", "9");
    }
  } else if (digitalRead(sw1)){
    if (lastSwitch!=1){
      lastSwitch = 1;
      // Serial.println("S1");
      sendDcsBiosMessage("INS_PARAM_SEL", "8");
    }
  } else if (digitalRead(sw2)){
    if (lastSwitch!=2){
      lastSwitch = 2;
      // Serial.println("S2");
      sendDcsBiosMessage("INS_PARAM_SEL", "7");
    }
  } else if (digitalRead(sw3)){
    if (lastSwitch!=3){
      lastSwitch = 3;
      // Serial.println("S3");
      sendDcsBiosMessage("INS_PARAM_SEL", "6");
    }
  } else if (digitalRead(sw4)){
    if (lastSwitch!=4){
      lastSwitch = 4;
      // Serial.println("S4");
      sendDcsBiosMessage("INS_PARAM_SEL", "5");
    }
  } else if (digitalRead(sw5)){
    if (lastSwitch!=5){
      lastSwitch = 5;
      // Serial.println("S5");
      sendDcsBiosMessage("INS_PARAM_SEL", "4");
    }
  } else if (digitalRead(sw6)){
    if (lastSwitch!=6){
      lastSwitch = 6;
      // Serial.println("S6");
      sendDcsBiosMessage("INS_PARAM_SEL", "3");
    }
  } else if (digitalRead(sw7)){
    if (lastSwitch!=7){
      lastSwitch = 7;
      // Serial.println("S7");
      sendDcsBiosMessage("INS_PARAM_SEL", "2");
    }
  } else if (digitalRead(sw8)){
    if (lastSwitch!=8){
      lastSwitch = 8;
      // Serial.println("S8");
      sendDcsBiosMessage("INS_PARAM_SEL", "1");
    }
  } else if (digitalRead(sw9)){
    if (lastSwitch!=9){
      lastSwitch = 9;
      // Serial.println("S9");
      sendDcsBiosMessage("INS_PARAM_SEL", "0");
    }
  } else {
    lastSwitch = -1;
  }
}


// Trigger LEDs
void onInsDestSwLightChange(unsigned int newValue) {
  digitalWrite(led0, newValue);
}
DcsBios::IntegerBuffer insDestSwLightBuffer(0x72d4, 0x0200, 9, onInsDestSwLightChange);

void onInsPrepSwLightChange(unsigned int newValue) {
  digitalWrite(led1, newValue);
}
DcsBios::IntegerBuffer insPrepSwLightBuffer(0x72d4, 0x0100, 8, onInsPrepSwLightChange);



/*******************************************************************************************/
// main loop
/*******************************************************************************************/
void loop() {
  DcsBios::loop();
  
  writeToKeyboard(HIGH, LOW, LOW);
  printIfNotZero(readKeyboard(0));
  delay(10);
  writeToKeyboard(LOW, HIGH, LOW);
  printIfNotZero(readKeyboard(1));
  delay(10);
  writeToKeyboard(LOW, LOW, HIGH);
  printIfNotZero(readKeyboard(2));
  delay(10);
  writeToKeyboard(LOW, LOW, LOW);

  digitalWrite(butSelector, HIGH);
  readButtons();
  delay(10);
  digitalWrite(butSelector, LOW);

  digitalWrite(swSelector, HIGH);
  readSwitch();
  delay(10);
  digitalWrite(swSelector, LOW);

  // not available in dcs bios
  // readPot();
}
