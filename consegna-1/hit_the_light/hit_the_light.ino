/*
 Consegna 1 - Hit the Light - Programmazione di Sistemi Embdedded
 Created by Giulia Cecchetti, Andrea Colombo

 L'esercizio è stato svolto con meno componenti possibili, in modo da sopperire più facilmente alla mancanza di una breadboard
 Sono stati utilizzate due pcb di recupero per led e switch, provenienti da una tastiera e da una stampante.
*/

#include<TimerOne.h>

// Switches
#define S1 2 // Yellow
#define S2 3 // Purple
#define S3 4 // Gray

// Leds
#define L1 5 // Yellow
#define L2 6 // Orange
#define L3 7 // Brown
#define COFFEE 8 // White

// Potentiometer
#define POT A2

// Initializing the state of the game
volatile boolean isStart = false;
volatile boolean isFinish = false;
volatile boolean nextGame = false;

// A number corrisponding to the pin of the winning led
int currentLed;

// Variable to set the speed of the led animation
unsigned long speedTime = 200;
int potentiometerValue = 0;

// Initial arbitral threshold time to react
unsigned long thresholdTime = 8000;

// Temporary var to track time in milliseconds
unsigned long startingMillis = 0;

// Variable to track the amount of points scored
int points = 0;

void setup() {
  // Starting serial connection
  Serial.begin(9600);
  
  // Configuring all the switches as an input and enable the internal pull-up resistor
  pinMode(S1, INPUT_PULLUP);
  pinMode(S2, INPUT_PULLUP);
  pinMode(S3, INPUT_PULLUP);
  
  // Configuring all the leds as an output
  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(L3, OUTPUT);
  pinMode(COFFEE, OUTPUT);

  // Setting up an interrupt for Switch1 to start the game and stop the amber led to blink
  attachInterrupt(digitalPinToInterrupt(S1), starter, LOW);

  // Generating a random number to set the period of the timer before the led animation stops
  unsigned long rando = random(100000000, 200000000);
  Timer1.initialize(rando);

  // Setting up an interrupt to stop the game and challenge the user when the timer finishes
  Timer1.attachInterrupt(finisher);
}

void loop() {

  if(!isStart || nextGame) { // The game hasn't started yet. The amber led blinks and the user can choose the speed of the game.

    // Stopping the timer before the game starts
    Timer1.stop();
    
    // Setting the speed to the value read by the potentiometer
    potentiometerValue = analogRead(POT);
    speedTime = map(potentiometerValue, 0, 1023, 50, 1000);

    // The amber led is blinking to the speed selected with the potentiometer
    blink(COFFEE, speedTime);
    
  } else if (isStart && !isFinish) { // The user pressed Switch1 and the game starts until the timer interrupts it
    
    // The timer starts to count
    Timer1.resume();
    
    // The game can't be interrupted by the S1 switch anymore
    detachInterrupt(digitalPinToInterrupt(S1));
    
    // Sliding leds animation
    blink(L1, speedTime);
    blink(L2, speedTime);
    blink(L3, speedTime);
    blink(L2, speedTime);
    
  } else if(isStart && isFinish) { // The timer has interrupted the game and the user has to select the correct switch during the threshold time

    if((millis() - startingMillis) <= thresholdTime){ // If the user still has time to make his choice

      // The current led stays on
      digitalWrite(currentLed, HIGH);
      
      // The switch to press is the one corresponding to the current led
      int currentSwitch=digitalRead((currentLed-3));
      
      if(currentSwitch == LOW){ // If the user presses the correct button
        win();
      } else if(digitalRead(S1) == LOW && (currentLed-3)!=S1 || digitalRead(S2) == LOW && (currentLed-3)!=S2 || digitalRead(S3) == LOW && (currentLed-3)!=S3){ // If the user presses the wrong switch
        lose();
      }
    } else { // If the user finishes his time to respond
      lose();
    }
  }
}

// Function called in the start of the round, when the user press the Switch1 to start playing
void starter() {
  
  // Turning off the amber led
  digitalWrite(COFFEE, LOW);

  // Starting the game
  isStart=true;
  nextGame=false;
}

// Function called when finishing round, when the timer finishes and the user has to make his choice
void finisher() {

  // Setting the round to finished, now the user needs to make his choice
  isFinish=true;
  
  // Saving the current time to calculate the time in which the user can respond
  startingMillis=millis();
  
}

// Function called to make leds blink, parameteres are the led to light up and the time it needs to turn off
void blink(int led, unsigned long time){
  
  // This check is just in case the interrupt stops the led blinking loop in half, so the remaining leds after the interrupt finishes will not turn on
  if(!isFinish){
    
    // Led blinking with a delay 
    digitalWrite(led, HIGH);
    delay(time);
    
    // Setting the correct led to press as the current led
    currentLed=led;
    digitalWrite(led, LOW);
    delay(time);
   }
}

// Function called when the user press the correct switch in the correct time frame
void win(){
  
  // The user pressed the correct switch. The correct led will now turn off
  digitalWrite(currentLed, LOW);

  // Calculating points by reaction time
  int reactionTime=(millis() - startingMillis);
  points=(thresholdTime-reactionTime)+points;

  // The time to react is halved for the next round
  thresholdTime=thresholdTime/2;

  // The round is not finished as it will restart
  isFinish = false;

  // The amber led will light up to altert the user to be ready for the next round
  blink(COFFEE, 250);
  
}

// Function called when the user press the wrong switch or just doesn't have time to press any switch
void lose(){
  
  // The user pressed the wrong switch or he didn't press any. The correct led will now turn off
  digitalWrite(currentLed, LOW);

  // Printing to serial the user final score
  Serial.println("GAME OVER | FINAL SCORE : ");
  Serial.println(points);


  // Restart with a little delay before starting a new game
  delay(3000);

  // Reinitialize all variables to their original state
  nextGame = true; 
  isStart = false;
  isFinish = false;
  points=0;
  thresholdTime = 8000;
  

  // Reattaching the interrupt of Switch1 to start the game
  attachInterrupt(digitalPinToInterrupt(S1), starter, LOW);

}

