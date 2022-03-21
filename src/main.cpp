#include <Arduino.h>

int Ain1 = 27; // +
int Ain2 = 26; // -
int aEN = 14;  // ENABLE (Also PWM channel)

int Bin1 = 25;
int Bin2 = 33;
int bEN = 12;

const int freq = 30000;
const int pwmChannel1 = 0; // Setting separate PWM channels for control
const int pwmChannel2 = 1;
const int resolution = 8; // 8 bit resolution (0-255)
int dutyCycle = 200; // Default for l298N

void setupMotor(){

  pinMode(Ain1, OUTPUT);
  pinMode(Ain2, OUTPUT);
  pinMode(Bin1, OUTPUT);
  pinMode(Bin2, OUTPUT);
  pinMode(aEN, OUTPUT);
  pinMode(bEN, OUTPUT);
  
  // Setup 2 PWM channels with same settings
  ledcSetup(pwmChannel1, freq, resolution);
  ledcSetup(pwmChannel2, freq, resolution);
  
  // Attaching physical pin to PWM channels
  ledcAttachPin(aEN, pwmChannel1);
  ledcAttachPin(bEN, pwmChannel2);

  digitalWrite(Ain1, LOW);
  digitalWrite(Ain2, LOW);
  digitalWrite(Bin1, LOW);
  digitalWrite(Bin2, LOW);
}

void foward(){
  digitalWrite(Ain1, 1);
  digitalWrite(Ain2, 0); 
  digitalWrite(Bin1, 1);
  digitalWrite(Bin2, 0);
  delay(2000);
}

void stop(){
  digitalWrite(Ain1, LOW);
  digitalWrite(Ain2, LOW);
  digitalWrite(Bin1, LOW);
  digitalWrite(Bin2, LOW);
}

// backwards (for one motor)
// digitalWrite(Xin1, HIGH);
// digitalWrite(Xin2, LOW); 

void setSpeed(int pwm){
  if (pwm > 255){
    dutyCycle = dutyCycle;
  } else if (pwm < 0){
    dutyCycle = dutyCycle;
  } else {
    dutyCycle = pwm;
  }
}

void setup() {
  setupMotor();

  Serial.begin(115200);

}

void loop() {
  ledcWrite(pwmChannel1, dutyCycle);
  ledcWrite(pwmChannel2, dutyCycle);
  foward();
}
