#include <Servo.h>
Servo myservo;

int redPin = D5;
int bluPin = D6;
int button = D7;
int val;
int buzzerPin = D8;
int ldrPin = A0;

int ldrRead;
int freq;
float multiplier;
int buttonState;
bool lastButtonState = HIGH;
unsigned long debounceTime;
unsigned long adelay;
unsigned long bdelay;
int bounceDelay = 50;

void setup() {
  myservo.attach(D4);
  pinMode(button,INPUT_PULLUP);
}

void loop() {
  checkButton();
  checkLdr();
  doLed();
  doServo();
  doSound(); 
}

void checkButton(){
    buttonState = digitalRead(button);

    if (buttonState == lastButtonState){
      debounceTime = millis();
    }

    if (millis() - bounceDelay > debounceTime){
      lastButtonState = buttonState;
    }
}

void checkLdr(){
  ldrRead = analogRead(A0);
}

void doLed(){
    if (lastButtonState == HIGH){
      analogWrite(bluPin,255);
      analogWrite(redPin,0);
    }
    else{
      analogWrite(redPin,255);
      analogWrite(bluPin,0);
    }
}

void doSound(){
  int frequency = map(ldrRead,0,50,1,2000); 
  if (lastButtonState==HIGH){
    tone(buzzerPin,frequency);
  }
  else if (lastButtonState==LOW){
    noTone(buzzerPin);
  }
}

void doServo(){ 
  freq = adelay - bdelay;
  freq = abs(freq);
  if (lastButtonState == LOW) {
    val = 0;
    adelay= millis();
  }
  else if (lastButtonState == HIGH) {
    val = 180;
    bdelay = millis();
  }
  
  myservo.write(val);
  delay(freq/2);
}
