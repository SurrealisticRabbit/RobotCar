#include <Arduino.h>
#include <BluetoothSerial.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled!
#endif

// Pins for controlling motor direction
const int Ain1 = 27;
const int Ain2 = 26;
const int Bin1 = 25;
const int Bin2 = 33;

// Pins for PWM (Speed Control) and Enable (On/Off)
const int aEN = 12;
const int bEN = 14;

// Extra Variabled for ESP32 PWM
const int freq = 30000; // Setting frequency
const int pwmChannel1 = 0; 
const int pwmChannel2 = 1;

// PWM on ESP32 works by assigning a pin to a channel, then 
// using functions to change the channel parameters.

const int resolution = 8; // 8 bit resolution (0-255)
int dutyCycle = 200; // Default for l298N

// Variables for bluetooth
BluetoothSerial SerialBT;
char BlData;

// A motor is Right
// B motor is Left

void setupMotor(){

  // Assigning all motor outputs as outputs
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
}


// sets all motors to foward
void foward(){
  digitalWrite(Ain1, 1);
  digitalWrite(Ain2, 0); 
  digitalWrite(Bin1, 0);
  digitalWrite(Bin2, 0);
}

void left(){
  digitalWrite(Ain1, 1);
  digitalWrite(Ain2, 0); 
  digitalWrite(Bin1, 0);
  digitalWrite(Bin2, 0);
}

void right(){
  digitalWrite(Ain1, 0);
  digitalWrite(Ain2, 0); 
  digitalWrite(Bin1, 1);
  digitalWrite(Bin2, 0);
}

void stop(){
  digitalWrite(Ain1, 0);
  digitalWrite(Ain2, 0);
  digitalWrite(Bin1, 0);
  digitalWrite(Bin2, 0);
}

void setup() {
  setupMotor();

  Serial.begin(115200);
  SerialBT.begin("ESP32 Car");

}

void loop() {

  // If serial avaliable on either get and then send on the other
  if (Serial.available()){
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()){
    Serial.write(SerialBT.read());

    // Reading char from BT side - if mactches control char then will start
    // action tied to the letter
    
    // W = UP    | w = STOP
    // S = DOWN  | s = STOP
    // A = LEFT  | a = STOP
    // D = RIGHT | d = STOP

    BlData = SerialBT.read();
  }

  if (BlData == 'W'){
    digitalWrite(Ain1, 1);
    digitalWrite(Ain2, 0); 
    digitalWrite(Bin1, 1);
    digitalWrite(Bin2, 0);
  }
  else if (BlData == 'w'){
    stop();
  }

  if (BlData == 'S'){
    digitalWrite(Ain1, 1);
    digitalWrite(Ain2, 0); 
    digitalWrite(Bin1, 1);
    digitalWrite(Bin2, 0);
  }
  else if (BlData == 's'){
    stop();
  }

  if (BlData == 'Q'){
    digitalWrite(Ain1, 1);
    digitalWrite(Ain2, 0); 
    digitalWrite(Bin1, 1);
    digitalWrite(Bin2, 0);
  }
  else if (BlData == 'q'){
    stop();
  }

  if (BlData == 'E'){
    digitalWrite(Ain1, 1);
    digitalWrite(Ain2, 0); 
    digitalWrite(Bin1, 1);
    digitalWrite(Bin2, 0);
  }
  else if (BlData == 'e'){
    stop();
  }

  dutyCycle = 255;

  // tells pwm channels to send pwm
  ledcWrite(pwmChannel1, dutyCycle);
  ledcWrite(pwmChannel2, dutyCycle);
}
