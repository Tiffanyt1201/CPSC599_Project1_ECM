/**
 * Project 3 - Integration: ECM 
 */

#include <Servo.h>
Servo ser;

// Defining digital pins and variables for servo 
const int serPin = 4;
int pos = 0;
int increment = 1; 
unsigned long servoPrevUpdateTime= 0;

// Defining digital pin and variables for button
const int button = 5; 
int buttonState = 0;
bool buttonPressed = false;

// Defining digital pins DC motor
int motor1 = 2;
int motor2 = 3;

// Initializing variable to store previous time physical output has been updated. 
unsigned long previousTime = 0;

/**
 * Class for all variables and functions for blinking LED light. 
 */
class LedBlink
{
  // Initializing class member variables to control blinking of LED light
  int LED;      
  long onTime;     
  long offTime;

  // These maintain the current state
  int LEDState;                
  unsigned long ledPrevUpdateTime;   

  /**
   * Constructor to initialize all variables for LED light. 
   */
  public:
  LedBlink(int pin, long on, long off){
    LED = pin;
    pinMode(LED, OUTPUT);     
    
    onTime = on;
    offTime = off;
  
    LEDState = LOW; 
    ledPrevUpdateTime = 0;
  }

  /**
   * Checking current state of LED light and updating/changing state of LED light when necessary. 
   */
  void updateLED(){
    //Getting the current time in milliseconds
    unsigned long currentTime = millis();

    /**
     * When LED light has been ON for the declared amount of time, turn LED OFF. When LED light has been OFF for the declared amount of time, turn LED light ON again. 
     */
    if((LEDState == HIGH) && (currentTime - ledPrevUpdateTime >= onTime))
    {
      LEDState = LOW;
      ledPrevUpdateTime = currentTime;  
      digitalWrite(LED, LEDState); 
    }
    else if ((LEDState == LOW) && (currentTime - ledPrevUpdateTime >= offTime))
    {
      LEDState = HIGH;
      ledPrevUpdateTime = currentTime; 
      digitalWrite(LED, LEDState);
    }
  }
  
  /**
   * Function to turn off LED light. 
   */
  void turnOffLED(){
    digitalWrite(LED, LOW);
  }
};


/**
 * Creating instances of the LedBlink class for all 10 LED lights with different pin numbers and on and off times. 
 */
LedBlink LED1(22, 300, 600);
LedBlink LED2(24, 200, 400);
LedBlink LED3(26, 300, 400);
LedBlink LED4(28, 100, 300);
LedBlink LED5(8, 300, 400);
LedBlink LED6(9, 300, 600);
LedBlink LED7(10, 200, 300);
LedBlink LED8(11, 100, 300);
LedBlink LED9(12, 100, 200);
LedBlink LED10(13, 300, 500);

/**
 * Function to set up input and output pins for button, DC motors and servo motor.  
 */
void setup() {
  // Initializing the DC motor pins to be output pins.
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
  // Setting both DC motors to be off
  digitalWrite(motor1, HIGH);
  digitalWrite(motor2, HIGH);

  // Initializing the button to be input pin.
  pinMode(button, INPUT);

  // Attaching servo to pin. 
  ser.attach(serPin);
  ser.write(pos);
}

/**
 * Loop function for user input and output display. 
 */
void loop() {
  // Reading state of the button
  buttonState = digitalRead(button);
  //Getting the current time in milliseconds 
  unsigned long currentTime = millis();

  /**
   * Checking if button is pressed by user. If so set button pressed to true. 
   */ 
  if (buttonState == HIGH && buttonPressed == false) {
    buttonPressed = true; 
  }

  /**
   * Checking if button has been pressed. If button is pressed, begin all physical outputs and start timer for 35 seconds. 
   */ 
  if (buttonPressed == true){
    // Checking if physical outputs have been running for less than 35 seconds. If still less than 35, continue physical outputs.  
    if (currentTime - previousTime <= 35000){
        // Checking if servo sweep position needs to be updated. 
        if((currentTime - servoPrevUpdateTime) > 4) {
          servoPrevUpdateTime= millis();
          pos += increment;
          ser.write(pos);
        // Checking if servo has done a full sweep. If so, reverse the direction of the sweep. 
        if ((pos >= 90) || (pos <= 0)){
          increment = -increment;
        } 
      }

      /** 
       *  Changing which DC motor is spinning at every 5 seconds interval. 
       */
      if ((currentTime - previousTime > 0) && (currentTime - previousTime <= 5000)){
        turnOnBothMotors(); 
      }
      else if ((currentTime - previousTime > 5000) && (currentTime - previousTime <= 10000)){
        onlyMotor1();
      }
      else if ((currentTime - previousTime > 10000) && (currentTime - previousTime <= 15000)){
        onlyMotor2();
      }
      else if ((currentTime - previousTime > 15000) && (currentTime - previousTime <= 20000)){
        onlyMotor1();
      }
      else if ((currentTime - previousTime > 20000) && (currentTime - previousTime <= 25000)){
        onlyMotor2();
      }
      else if ((currentTime - previousTime > 25000) && (currentTime - previousTime <= 30000)){
        onlyMotor1();
      }
      else if ((currentTime - previousTime > 30000) && (currentTime - previousTime <= 35000)){
        onlyMotor2();
      }

      /**
       * Blinking all 10 LED lights at different rates and times. Calling update function in LEDBlink class to update LED states. 
       */
      LED1.updateLED();
      LED2.updateLED();
      LED3.updateLED();
      LED4.updateLED();
      LED5.updateLED();
      LED6.updateLED();
      LED7.updateLED();
      LED8.updateLED();
      LED9.updateLED();
      LED10.updateLED();
    }
    /**
     * Turning off all physical outputs after 35 seconds. 
     */
    else {
      digitalWrite(motor2, HIGH);
      LED1.turnOffLED();
      LED2.turnOffLED();
      LED3.turnOffLED();
      LED4.turnOffLED();
      LED5.turnOffLED();
      LED6.turnOffLED();
      LED7.turnOffLED();
      LED8.turnOffLED();
      LED9.turnOffLED();
      LED10.turnOffLED();
      buttonPressed = false;
      previousTime = millis(); 
    }
  }
}

/**
 * Function to turn on both DC motors together. 
 */
void turnOnBothMotors(){
  digitalWrite(motor1, LOW);
  digitalWrite(motor2, LOW);
}

/**
 * Function to only turn on motor 1. 
 */
void onlyMotor1(){
  digitalWrite(motor2, HIGH);
  digitalWrite(motor1, LOW);
}

/**
 * Function to only turn on motor 2. 
 */
void onlyMotor2(){
  digitalWrite(motor1, HIGH);
  digitalWrite(motor2, LOW);
}
