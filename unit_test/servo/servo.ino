// a piece of code for testing the servo


#include<Servo.h>
const int servo_pin=6;
Servo servo;
int pos=1500;
int input=1;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  servo.attach(servo_pin);
 
}

void loop() {
  
 
  
  
  // put your main code here, to run repeatedly:
//  int counter_clockwise[]={800,900,1000,1100,1200,1300,1400,1500,1600,1700,1800,1900};
//  int clockwise[]={1900,1800,1700,1600,1500,1400,1300,1200,1100,1000,900,800};
//  
//  for(int i=0;i<12;i++){
//  Serial.println("counter_clockwise at "+String(counter_clockwise[i]));
//  servo.writeMicroseconds(counter_clockwise[i]);
//  
//  }
//  
//  for(int i=0;i<12;i++){
//  Serial.println("clockwise at "+String(clockwise[i]));
//  servo.writeMicroseconds(clockwise[i]);
// 
//  }

  servo.writeMicroseconds(1900);
  delay(2000);
  servo.writeMicroseconds(1100);
  delay(2000);

  
}
