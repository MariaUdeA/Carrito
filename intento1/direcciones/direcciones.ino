/*********
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp32-dc-motor-l298n-motor-driver-control-speed-direction/
*********/
#include <PS4Controller.h>

// Motor A
int motor1Pin1 = 16; 
int motor1Pin2 = 17; 
int enable1Pin = 4; 
//Motor B
int motor2Pin1 = 18; 
int motor2Pin2 = 5; 
int enable2Pin = 19;


// Setting PWM properties
const int freq = 30000;
const int pwmChannel1 = 0;
const int pwmChannel2 = 0;
const int resolution = 8;
int dutyCycle = 255;
float factor1=1.0;
float factor2=0.85;

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

  // configure LED PWM functionalitites
  ledcSetup(pwmChannel1, freq, resolution);
  ledcSetup(pwmChannel2, freq, resolution);

  // attach the channel to the GPIO to be controlled
  ledcAttachPin(enable1Pin, pwmChannel1);
  ledcAttachPin(enable2Pin, pwmChannel2);
  
  Serial.begin(115200);

  // testing
  Serial.print("Fin del setup");
}

void loop() {
  if(PS4.isConnected()){
    Serial.println("control");
  // Move the DC motor forward at maximum speed
    if     (PS4.Up())     { forward(dutyCycle);  }
    else if(PS4.Down())   { backward(dutyCycle); }
    else if(PS4.Right())  { right(dutyCycle,dutyCycle-20);    }
    else if(PS4.Left())   { left(dutyCycle-20,dutyCycle);     }
    else                  { stop();     }
  }
  delay(10);
}

// funciones de direcciones
void forward(int pwm){
  ledcWrite(pwmChannel1,int(pwm*factor1));
  ledcWrite(pwmChannel2,int(pwm*factor2));
  //digitalWrite(enable1Pin, HIGH);
  //digitalWrite(enable2Pin, HIGH);
  //Serial.println("Moving Forward");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
      
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
}

void backward(int pwm){
  ledcWrite(pwmChannel1,int(pwm*factor1));
  ledcWrite(pwmChannel2,int(pwm*factor2));
  //digitalWrite(enable1Pin, HIGH);
  //digitalWrite(enable2Pin, HIGH);
  //Serial.println("Moving Forward");
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
      
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
}

void right(int pwm1, int pwm2){
  ledcWrite(pwmChannel1,int(pwm1*factor1));
  ledcWrite(pwmChannel2,int(pwm2*factor2));
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
  //motor1 izquierdo
  //el motor 1 sigue hacia adelante    
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
}

void left(int pwm1, int pwm2){
  ledcWrite(pwmChannel1,int(pwm1*factor1));
  ledcWrite(pwmChannel1,int(pwm2*factor2));
  //el motor 2 sigue hacia adelante
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
      
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
}

void stop(){
  ledcWrite(pwmChannel1,0);
  ledcWrite(pwmChannel1,0);
  //digitalWrite(enable1Pin, LOW);
  //digitalWrite(enable2Pin, LOW);
}
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
