/*
Junction box
*/

// main code: ArduinoCode.ino
#include "Signal.h"

Signal signal1(2); // create a LED object that attach to pin 2
Signal signal2(3); // create a LED object that attach to pin 3

#include "Sensor.h"


#include "Block.h"


Block block1(2, {2}, {3}); // create a LED object that attach to pin 2
//Block blocks[];

//Block blocks[] = {(2, {1,2,3,4,5,6,7,8,9,10}, {11,12,13})};

//// GPIO PINS ////

// 2 June 2022

#define HALL_1 2
#define HALL_2 3


/*
   Define 'train sensors'
   Pairs of reed switches.
   2+5 Sensor A
   3+6 Sensor B
   4+7 Sensor C

*/
/*

   BLOCK1 - Rattys corner main loop
   BLOCK2 - Figgy Bottom Junction
   BLOCK3 - Tapia Station
   BLOCK4 - Swimming pool loop
*/

//      VARIABLE NAME     PIN   DAD'S DESCRIPTION
#define BLOCK_SENSOR_1_A  1 //  NOT FOUND "A1"
#define BLOCK_SENSOR_1_B  2 //  OK. "B2"

#define BLOCK_SENSOR_2_A  3 //  NOT FOUND
#define BLOCK_SENSOR_2_B  4 //  OK "A3"

#define BLOCK_SENSOR_3_A  5 //  OK "B6 Pin 7
#define BLOCK_SENSOR_3_B  6 //  OK "A5"

#define BLOCK_SENSOR_4_A  7 //  OK A7 Pin 8
#define BLOCK_SENSOR_4_B  8 //  OK B8 Pin 9

#define BLOCK_SENSOR_5_A  9 //  OK A9 Pin 10
#define BLOCK_SENSOR_5_B 10 // OK B10 Pin 11

bool blockSensors[20];

#define RESET_BUTTON 0
bool resetButton;

#define SIGNAL_1_RED A1
#define SIGNAL_1_YELLOW A2
#define SIGNAL_1_GREEN A0

#define SIGNAL_2_RED A5
#define SIGNAL_2_YELLOW A4
#define SIGNAL_2_GREEN A3

#define SIGNAL_3_RED 12
#define SIGNAL_3_YELLOW 13
#define SIGNAL_3_GREEN 11

//// VARIABLES ////
boolean interlocking_state_block_1;
boolean interlocking_state_block_2;
boolean interlocking_state_block_3;
boolean interlocking_state_block_4;
boolean interlocking_state_block_5;

boolean block_sensor_1_a;
boolean block_sensor_1_b;

boolean block_sensor_2_a;
boolean block_sensor_2_b;
boolean block_sensor_3_a;
boolean block_sensor_3_b;
boolean block_sensor_4_a;
boolean block_sensor_4_b;
boolean block_sensor_5_a;
boolean block_sensor_5_b;

int sensor_1_state = 0;
int sensor_2_state = 0;
int sensor_3_state = 0;
int sensor_4_state = 0;
int sensor_5_state = 0;







//int block_1_2_state = 2;

//int block_2_3_state;

int sensor_state_1;
int sensor_state_2;
int sensor_state_3;
int sensor_state_4;
int sensor_state_5;



void setup() {

  // Initiailisatise console logging

  Serial.begin(9600); // open the serial port at 9600 bps:
  // Initialize GPIO

  pinMode(SIGNAL_1_RED, OUTPUT);
  pinMode(SIGNAL_1_YELLOW, OUTPUT);
  pinMode(SIGNAL_1_GREEN, OUTPUT);

  //pinMode(HALL_2, INPUT);
  pinMode(SIGNAL_2_RED, OUTPUT);
  pinMode(SIGNAL_2_YELLOW, OUTPUT);
  pinMode(SIGNAL_2_GREEN, OUTPUT);

  //pinMode(HALL_2, INPUT);
  pinMode(SIGNAL_3_RED, OUTPUT);
  pinMode(SIGNAL_3_YELLOW, OUTPUT);
  pinMode(SIGNAL_3_GREEN, OUTPUT);

  pinMode(RESET_BUTTON,  INPUT_PULLUP);

  pinMode(BLOCK_SENSOR_1_A,  INPUT_PULLUP);
  pinMode(BLOCK_SENSOR_1_B,  INPUT_PULLUP);
  pinMode(BLOCK_SENSOR_2_A,  INPUT_PULLUP);
  pinMode(BLOCK_SENSOR_2_B,  INPUT_PULLUP);
  pinMode(BLOCK_SENSOR_3_A,  INPUT_PULLUP);
  pinMode(BLOCK_SENSOR_3_B,  INPUT_PULLUP);
  pinMode(BLOCK_SENSOR_4_A,  INPUT_PULLUP);
  pinMode(BLOCK_SENSOR_4_B,  INPUT_PULLUP);
  pinMode(BLOCK_SENSOR_5_A,  INPUT_PULLUP);
  pinMode(BLOCK_SENSOR_5_B,  INPUT_PULLUP);  
  
  // On start or reset
  interlocking_state_block_1 = true; // Line free
  digitalWrite(SIGNAL_1_RED, LOW);
  digitalWrite(SIGNAL_1_YELLOW, HIGH);
  digitalWrite(SIGNAL_1_GREEN, HIGH);

  digitalWrite(SIGNAL_2_RED, LOW);
  digitalWrite(SIGNAL_2_YELLOW, HIGH);
  digitalWrite(SIGNAL_2_GREEN, HIGH);

  digitalWrite(SIGNAL_3_RED, LOW);
  digitalWrite(SIGNAL_3_YELLOW, HIGH);
  digitalWrite(SIGNAL_3_GREEN, HIGH);



}



int getSensorState(boolean sensorA, boolean sensorB, int currentState) {
  int block_state = 0;

 // Is train travelling up?
  if ((sensorA == false) && (sensorB == true)) {
    block_state = 1;
//    Serial.println("Train entered Block 2 from Block 1");
  }
  if ((sensorA == true) && (sensorB == false) ) {
    block_state = 1;
  }

  if ((sensorA == true) && (sensorB == false) ) {
    block_state = 2;
 //   Serial.println("Train entered Block 1 from Block 2");
  }
  if ((sensorA == false) && (sensorB == true) ) {
    block_state = 2;
  }
return block_state;
  
  // Is train travelling up?
  if ((sensorA == false) && (sensorB == true) && (currentState == 2)) {
    block_state = 1;
 //   Serial.println("Train entered Block 2 from Block 1");
  }
  if ((sensorA == true) && (sensorB == false) && (currentState == 1)) {
    block_state = 1;
  }

  if ((sensorA == true) && (sensorB == false) && (currentState == 1)) {
    block_state = 2;
 //   Serial.println("Train entered Block 1 from Block 2");
  }
  if ((sensorA == false) && (sensorB == true) && (currentState == 2)) {
    block_state = 2;
  }

  return block_state;
}

void setSignal(int state, int RED, int YELLOW, int GREEN) {

  if (state == 0) {  //true
    digitalWrite(RED, LOW);
    digitalWrite(YELLOW, HIGH);
    digitalWrite(GREEN, LOW);
  } else if (state == 1) {

    digitalWrite(RED, LOW);
    digitalWrite(YELLOW, LOW);
    digitalWrite(GREEN, HIGH);

  } else if (state == 2) {
    digitalWrite(RED, HIGH);
    digitalWrite(YELLOW, LOW);
    digitalWrite(GREEN, LOW);
  } else {
    // error ?
    digitalWrite(RED, LOW);
    digitalWrite(YELLOW, HIGH);
    digitalWrite(GREEN, LOW);

  }



}
void loop() {
  block1.turnON();

  /*
    if (digitalRead(HALL_1) == LOW || digitalRead(HALL_2) == LOW) {
      interlocking_state = !interlocking_state;
      delay(200);
    }
  */

  // Read the pair of reed sensors at the interface between block 1 and 2.
  // Determine the direction of the magnet travel.
  block_sensor_1_a = digitalRead(BLOCK_SENSOR_1_A);
  block_sensor_1_b = digitalRead(BLOCK_SENSOR_1_B);

  block_sensor_2_a = digitalRead(BLOCK_SENSOR_2_A);
  block_sensor_2_b = digitalRead(BLOCK_SENSOR_2_B);

  block_sensor_3_a = digitalRead(BLOCK_SENSOR_3_A);
  block_sensor_3_b = digitalRead(BLOCK_SENSOR_3_B);

  block_sensor_4_a = digitalRead(BLOCK_SENSOR_4_A);
  block_sensor_4_b = digitalRead(BLOCK_SENSOR_4_B);
  
  block_sensor_5_a = digitalRead(BLOCK_SENSOR_5_A);
  block_sensor_5_b = digitalRead(BLOCK_SENSOR_5_B);



sensor_1_state = getSensorState(block_sensor_1_a, block_sensor_1_b, sensor_1_state);
sensor_2_state = getSensorState(block_sensor_2_a, block_sensor_2_b, sensor_2_state);
sensor_3_state = getSensorState(block_sensor_3_a, block_sensor_3_b, sensor_3_state);
sensor_4_state = getSensorState(block_sensor_4_a, block_sensor_4_b, sensor_4_state);
sensor_5_state = getSensorState(block_sensor_5_a, block_sensor_5_b, sensor_5_state);
/*
//Serial.println("");
Serial.print("1---");
Serial.print("block sensors ");
Serial.print(block_sensor_1_a);
Serial.print(block_sensor_1_b);
Serial.print("state ");
Serial.print(sensor_1_state);
Serial.print(" ");

Serial.print("2---");
Serial.print("block sensors ");
Serial.print(block_sensor_2_a);
Serial.print(block_sensor_2_b);
Serial.print("state ");
Serial.print(sensor_2_state);
Serial.print(" ");

Serial.print("3---");
Serial.print("block sensors ");
Serial.print(block_sensor_3_a);
Serial.print(block_sensor_3_b);
Serial.print("state ");
Serial.print(sensor_3_state);
Serial.print(" ");

Serial.print("4---");
Serial.print("block sensors ");
Serial.print(block_sensor_4_a);
Serial.print(block_sensor_4_b);
Serial.print("state ");
Serial.print(sensor_4_state);

Serial.print("5---");
Serial.print("block sensors ");
Serial.print(block_sensor_5_a);
Serial.print(block_sensor_5_b);
Serial.print("state ");
Serial.print(sensor_5_state);
Serial.println("");
*/
Serial.print("First Pair ");
Serial.print(block_sensor_1_a);
Serial.print(" ");
Serial.print(block_sensor_1_b);

Serial.print(" Second Pair ");
Serial.print(block_sensor_2_a);
Serial.print(" ");
Serial.print(block_sensor_2_b);
//Serial.print("state ")1
//Serial.print(sensor_5_state);
Serial.println("");

  //if ((block_1_2_a == true) && (block_1_2_b == true)) {block_1_2_state = 0;}


  //if (block_1_2_a == false) && (block_1_2_b == false) {block_1_2_state = 0;}

// Next step is to take the four sensor states.
// And traanslae that into interlock states for each block.
  if (sensor_1_state == 1)  {

    interlocking_state_block_1 = false;

  }

  if (sensor_1_state == 2)  {

    interlocking_state_block_1 = true;

  }


////
//Moah logic

  if (sensor_2_state == 1)  {

    interlocking_state_block_2 = false;

  }

  if (sensor_2_state == 2)  {

    interlocking_state_block_2 = true;

  }

////
//Moah logic

  if (sensor_3_state == 1)  {

    interlocking_state_block_3 = false;

  }

  if (sensor_3_state == 2)  {

    interlocking_state_block_3 = true;

  }

////
//Moah logic

  if (sensor_4_state == 1)  {

    interlocking_state_block_4 = false;

  }

  if (sensor_4_state == 2)  {

    interlocking_state_block_4 = true;

  }

  if (sensor_5_state == 1)  {

    interlocking_state_block_4 = false;

  }

  if (sensor_5_state == 2)  {

    interlocking_state_block_4 = true;

  }

  
  if (digitalRead(RESET_BUTTON) == LOW)  {
    interlocking_state_block_1 = false;
    interlocking_state_block_2 = false;
        interlocking_state_block_3 = false;
            interlocking_state_block_4 = false;
       interlocking_state_block_5 = false;

                sensor_1_state = 0;
                 sensor_2_state = 0;
                  sensor_3_state = 0;
                   sensor_4_state = 0;
   sensor_5_state = 0;

                
  }

  // Printout variables to console
  /*
    Serial.print("reset button ");
    Serial.println( digitalRead(RESET_BUTTON));

    Serial.print("block 1-2 A ");
    Serial.println( block_1_2_a);

     Serial.print("block 1-2 B ");
    Serial.println( block_1_2_b);

     Serial.print("block 1-2 state ");
    Serial.println( block_1_2_state);

    Serial.print("block 2-3 A ");
    Serial.println( digitalRead(BLOCK_2_3_A));

    Serial.print("block 2-3 B ");
    Serial.println( digitalRead(BLOCK_2_3_B));

     Serial.print("block 3-4 A ");
    Serial.println( digitalRead(BLOCK_3_4_A));

      Serial.print("block 3-4 B ");
    Serial.println( digitalRead(BLOCK_3_4_B));


    Serial.print("interlock state block 1 ");
    Serial.println( interlocking_state_block_1);

    Serial.print("interlock state block 2 ");
    Serial.println( interlocking_state_block_2);
  */
  //interlocking_state = !interlocking_state;
  //delay(5000);


  // This bit here sets the signals to red or green.
  // Depending on the interlocking state.

  /*
    if (interlocking_state_block_1) {  //true
     digitalWrite(RED_SIGNAL, LOW);
     digitalWrite(GREEN_SIGNAL, HIGH);
    } else {

     digitalWrite(RED_SIGNAL, HIGH);
     digitalWrite(GREEN_SIGNAL, LOW);

    }
  */

setSignal(interlocking_state_block_1, SIGNAL_1_RED, SIGNAL_1_YELLOW, SIGNAL_1_GREEN);
setSignal(interlocking_state_block_2, SIGNAL_2_RED, SIGNAL_2_YELLOW, SIGNAL_2_GREEN);
setSignal(interlocking_state_block_4, SIGNAL_3_RED, SIGNAL_3_YELLOW, SIGNAL_3_GREEN);




}
