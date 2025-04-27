#include <Servo.h>

Servo l_servo;
Servo r_servo;
Servo m_servo;

int latch = 12;
int clock = 13;
int data = 8;

int l_servo_max = 10;
int l_servo_min = 55;
int l_servo_demo = 30;

int r_servo_max = 170;
int r_servo_min = 110;
int r_servo_demo = 150;

int m_servo_max = 10;
int m_servo_min = 60;
int m_servo_demo = 30;

int button1 = 6;
int button2 = 7;

void setup() {
  // put your setup code here, to run once:
  pinMode(latch, OUTPUT);
  pinMode(clock, OUTPUT);
  pinMode(data, OUTPUT);

  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);

  l_servo.attach(9);
  r_servo.attach(11);
  m_servo.attach(10);

  l_servo.write(l_servo_demo);
  r_servo.write(r_servo_demo);
  m_servo.write(m_servo_demo);

  full_off();
  while(digitalRead(button1) < 1 && digitalRead(button2) < 1) {
    
  }

  // Push each of the arms in individually to test and pull them all back at the end
  l_servo.write(l_servo_max);
  updateLeds(0b1110);
  delay(2000);

  r_servo.write(r_servo_max);
  updateLeds(0b11100001110);
  delay(2000);

  m_servo.write(m_servo_max);
  updateLeds(0b11111111110);
  delay(2000);

  l_servo.write(l_servo_min);
  r_servo.write(r_servo_min);
  m_servo.write(m_servo_min);

  while(digitalRead(button1) < 1 && digitalRead(button2) < 1) {
    circle();
  }

  // Push to the demo position
  full_on();
  l_servo.write(l_servo_demo);
  r_servo.write(r_servo_demo);
  m_servo.write(m_servo_demo);

}

void loop() {
  // put your main code here, to run repeatedly:
  
}

void updateLeds(int output) {
  digitalWrite(latch, LOW);

  // Upper byte
  shiftOut(data, clock, MSBFIRST, ((output&(0xFF00))>>8));

  // Lower byte
  shiftOut(data, clock, MSBFIRST, output&(0xFF));

  digitalWrite(latch, HIGH);
}

void circle() {
  for (int i = 0; i < 11; i++) {
    updateLeds((1<<i));
    delay(50);
  }
}

void full_on(){
  updateLeds(0xFFF);
}

void full_off() {
  updateLeds(0);
}
