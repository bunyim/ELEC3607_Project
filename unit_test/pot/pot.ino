// a simple close to read value from potentiometer

int potpin=0;
int val=0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

// floor 1 : 604 - 635 but actual is 619
// floor 2 : 495 - 525 but actual is 510
// floor 3 : 390 - 415 but actual is 403

// 3.3 V  then GOUND then analogread
void loop() {
  // put your main code here, to run repeatedly:
  val = analogRead(potpin);
  Serial.println("Value from potentiometer is: "+String(val));
  delay(1000);
}
