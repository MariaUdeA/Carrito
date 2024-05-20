/*********
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp32-dc-motor-l298n-motor-driver-control-speed-direction/
*********/
#include <PS4Controller.h>

// Motor A
int motor1Pin1 = 16; 
int motor1Pin2 = 17; 
int enable1Pin = 4; 
//Motor B-
int motor2Pin1 = 18; 
int motor2Pin2 = 5; 
int enable2Pin = 19;


// Setting PWM properties
const int freq = 30000;
const int pwmChannel = 0;
const int resolution = 8;
int dutyCycle = 200;
char mov ='l'; 


void setup() {
  //conectar con el control
  PS4.begin("80:7D:3A:F1:42:88");

  // sets the pins as outputs:
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);
  
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(enable2Pin, OUTPUT);

  /*
  // configure LED PWM functionalitites
  ledcSetup(pwmChannel, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(enable1Pin, pwmChannel);
  ledcAttachPin(enable2Pin, pwmChannel);
  */
  Serial.begin(115200);

  // testing
  Serial.print("Testing DC Motor...");
}

void loop() {
  if(PS4.isConnected()){
    Serial.println("control");
  // Move the DC motor forward at maximum speed
    if(PS4.Up()){
      digitalWrite(enable1Pin, HIGH);
      digitalWrite(enable2Pin, HIGH);
      //Serial.println("Moving Forward");
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, HIGH);
      
      digitalWrite(motor2Pin1, LOW);
      digitalWrite(motor2Pin2, HIGH);
    }
    else if(PS4.Down()){
      digitalWrite(enable1Pin, HIGH);
      digitalWrite(enable2Pin, HIGH);
      //Serial.println("Moving Backwards");
      digitalWrite(motor1Pin1, HIGH);
      digitalWrite(motor1Pin2, LOW);
      
      digitalWrite(motor2Pin1, HIGH);
      digitalWrite(motor2Pin2, LOW);
    }
    else if(PS4.Right()){
      digitalWrite(enable1Pin, HIGH);
      digitalWrite(enable2Pin, HIGH);
      //Serial.println("Turning Right");
      digitalWrite(motor2Pin1, HIGH);
      digitalWrite(motor2Pin2, LOW);
      
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, HIGH);
    }
    else if(PS4.Left()){
      digitalWrite(enable1Pin, HIGH);
      digitalWrite(enable2Pin, HIGH);
      //Serial.println("Turning Left");
      digitalWrite(motor2Pin1, LOW);
      digitalWrite(motor2Pin2, HIGH);
      
      digitalWrite(motor1Pin1, HIGH);
      digitalWrite(motor1Pin2, LOW);
    }
    else {
      digitalWrite(enable1Pin, LOW);
      digitalWrite(enable2Pin, LOW);
    }
  }
  delay(100);
  /*
  // Move DC motor forward with increasing speed
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  while (dutyCycle <= 255){
    ledcWrite(pwmChannel, dutyCycle);   
    Serial.print("Forward with duty cycle: ");
    Serial.println(dutyCycle);
    dutyCycle = dutyCycle + 5;
    delay(500);
  }
  dutyCycle = 200;*/
  }