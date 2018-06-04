
#define blueToothSerial Serial2 // using bluetooth as serial 2

#define XCHAN1  0         // TC2 channel 0
#define XID    ID_TC6     // Instance ID of the channel 0
#define XCHAN2 1          // TC2 channel 1
#define XTC TC2           // Timer counter 2
#define XID1 ID_TC7       // Instance ID of the channel 1
#define TC_SYNC1 (*(WoReg*) 0x400880C0)   // SYNC register address
#define PINCHAN1  25      // Digital pin 3 
#define PINCHAN2  28      // Digital pin 5
#define VARIANT_MCK 41999026      // MCK/2 which is 42 MHz

// list of library required for the LED matrix
#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

// servo library
#include <Servo.h>


Adafruit_8x8matrix matrix = Adafruit_8x8matrix(); // matrix object for controlling the LED

int potpin=0; // potentiometer pin
const int buzzer = 39;  //buzzer pin



volatile int up_calls[4]={0,0,0,0}; //index 0 is a boolean for the up routine, 1 represents a call from level 1, and 2 for
//a call from level 2 and index 3 represent a call from lvl 3

volatile int down_calls[4]={0,0,0,0}; //same as up_calls, index 0 is routine for down boolean, 1 is level 1, 2 is level 2,3 is lvl 3

volatile int current_floor = 0;  // current floor at the start of the program is unknown need calibration
bool in_motion = 0;     // tells whether the lift is moving or not
volatile bool is_open=0;  //boolean variable for checking if the door should be open

Servo servo;  //servo object
const int servo_pin=35;   // servo pin

int floors[3];  //potentiometer value for each floor


int servo_close = 1050;  //the value to write to the servo in order to close the door
int servo_open = 1900;//the value to write to the servo in order to open the door

int len=849; // length of the array 
int opening[849]; //all value to open the door in a smooth transistion
int closing[849];//all value to close the door in a smooth transistion


// down button from lvl 3
void func0(){

  // open the door if the lift is at lvl 3
  if (current_floor == 3 && in_motion == 0)
      is_open=1;
  // else mark it as an up call and change the routine to up if it is not going down
  else{
    up_calls[3] = 1;
    if (down_calls[0] == 0) {
        up_calls[0] = 1;
      }
   }


   
}

//up button from lvl 1
void func3(){
  //open the door if the lift is at lvl 1
  if (current_floor == 1 && in_motion == 0) {
      is_open=1;

  //else mark it as a dwn call and change the routine to down if it is not going up
  }else {
    down_calls[1] = 1;
    if (up_calls[0]==0) {
        down_calls[0] = 1;
    }
  }
}

//up button from lvl 2
void func1(){

  // open the door if the lift is at lvl 2
  if (current_floor == 2 && in_motion == 0) {
    is_open=1;

  // else check if the current floor is greater than 2
  }else if (current_floor > 2) {

    // if it is greater than 2 check the routine, if lift is going down make it an up call else make it a down call to pick
    // up passenger to go up
    if (down_calls[0]==1){
        up_calls[2]=1;
        
    }else{
        down_calls[2]=1;
        
     }

     // if it is not going down then change the routine of the lift to come down
    if (up_calls[0] == 0) {
      down_calls[0] = 1;
      
    }    
    
  }else {

    // if the current floor is less than 2 then check if the routine is going up
    // if it is not going down then change the routine to go up and make it an up call at lvl 2
    if (down_calls[0]==0){
        up_calls[2]=1;
        up_calls[0]=1;
        
    }

     
  }
}

//down button from lvl 2
void func2(){

  // same functionality as up button from lvl 2 but reverse
  
  if (current_floor == 2 && in_motion == 0) {
    is_open=1;
    
  }else if (current_floor > 2) {

    if (up_calls[0] == 0) {
      down_calls[0] = 1;
      
    }
    
    if(down_calls[0]==1){
      down_calls[2] = 1;
      
     }

    
    
  }else {
    
    if(up_calls[0]==1){
      down_calls[2] = 1;
     }else{
      up_calls[2]=1;
      }
      
    if (down_calls[0] == 0) {
      up_calls[0] = 1;
    }
  }
  
}


//open button inside lift
void func7(){
  
  is_open=1;
}

//close button inside lift
void func8(){
  
  is_open=0;
}

//emergency button
void func9(){
  
  motor_stop();
  
}

// floor 1 button in lift
void func4(){

  // if current floor is at 1 open the door
  if (current_floor == 1 && in_motion == 0) {
    is_open=1;

  // same functionality as the up button from floor 1
  }else {  
    down_calls[1] = 1;
    
    if (up_calls[0] == 0) {
      down_calls[0] = 1;
    }
    
  }
}

// floor 2 button in lift
void func5(){

  // similar functionality as the external buttons from lvl 2
  if (current_floor == 2 && in_motion == 0) {
    is_open=1;
    
  }else if (current_floor > 2) {
    down_calls[2] = 1;
    if (up_calls[0] == 0) {
      down_calls[0] = 1;

    }
  }else {
    
    up_calls[2] = 1;
    
    if (down_calls[0] == 0) {
      up_calls[0] = 1;
    }
    
  }

}


// floor 3 button in lift
void func6(){

  // same functionality as the dwn button from lvl 3
  if (current_floor == 3 && in_motion == 0) {
      is_open=1;
      
  }else {
    up_calls[3] = 1;
    
    if (down_calls[0] == 0) {
      up_calls[0] = 1;
    }
    
  }
}






void setup(){


  // setting up the opening array 
  for(int i=1;i<=len;i++){
    
    opening[i-1]=1051+i;
    
  }


  // setting up the closing array
  for(int i=1;i<=len;i++){
    
    closing[i-1]=1899-i;
    
  }

  // set up bluetooth connection
  //setupBlueToothConnection(); 
  
  unsigned int chanmask = (1 << PINCHAN1)|(1<<PINCHAN2);  // bit mask
  
  // set PIO to chan C
  REG_PIOC_PDR = chanmask;
  REG_PIOC_ABSR = chanmask;
  REG_PIOC_MDDR = chanmask;

  // set up TC
  pmc_set_writeprotect(false);
  pmc_enable_periph_clk(XID1);
  pmc_enable_periph_clk(XID);

  // stopping the motor
  motor_stop();


  // attaching the servo pin
  servo.attach(servo_pin);

  
  Serial.begin(9600);

  
  void(*p[13])()= {&func0,&func1,&func2,&func3,&func4,&func5,&func6,&func7,&func8,&func9}; // function pointers for interrupts
  
  pinMode(buzzer,OUTPUT); // setting the buzzer as an output pin

  // setting all the interrupt pin to low
  for(int i=22;i<=31;i++)
      pinMode(i,OUTPUT);

  // attaching interrupt to all the pin and search for a rising edge
  for(int i = 22;i<=31;i++){

    attachInterrupt(i,p[i-22],RISING);
  }
  
  int i=0; //counter for reading measurement when calibration
  int val;  // value read from potentiometer
  int input;  // input from phone

  //closing the door
  servo.writeMicroseconds(servo_close);
  
  matrix.begin(0x70);  // pass in the address for the matrix


  // calibration loop
  while(i<3){
    
    val = analogRead(potpin);
    
    // check if anything was receive from the bluetooth and set all the floor values to the potentiometer value
    
    if(Serial.available()){
      input = Serial.parseInt();
      if(input==1){
          floors[0]=val;
          i++;
       }else if(input==2){
          floors[1]=val;
          i++;
        }else if(input==3){
          floors[2]=val;
          i++;
        }
      }
     delay(1000);
  }
  
  val = analogRead(potpin);

  // setting the current floor based on the last value read from the potentiometer
  
  if (val>floors[0]-10 && val < floors[0]+10){
    current_floor = 1;
    arr1();
  }else if(val> floors[1]-10 && val< floors[1]+10){
    current_floor = 2;
    arr2();
  }else if(val > floors[2]-10 && val< floors[2]+10){
    current_floor = 3;
    arr3();
  }


  Serial.println("Current floor is now at "+String(current_floor));
  for(int i=0;i<3;i++){
    
    Serial.println("Value saved for floor "+String(i+1)+" is "+String(floors[i]));
    
    }
  delay(3000);

}


int pot=0; // value read from potentiometer


void loop(){
  
    service();

    
}

// open door function & close at the same time
void open_door(){

  // open the door when the lift is stationary 
  if(in_motion==0){
    int i=0;
    int j=len;
    while (1){
      
      if(is_open==1){
        
        servo.writeMicroseconds(opening[i]);
        i++;
        j--;
        if(i==len){

          // delay 2 second when fully open
          is_open=0;
          delay(2000);
          }
          
      }else{
        
        if(j==len)
          break;
        
        servo.writeMicroseconds(closing[j]);
        j++;
        i--;
      }
    }
    //delay 1 second before moving up or down 
    delay(1000);
  }
}


int up_down=0;//counter to set the motor to run once only 


// service function 
void service(){

  

  
  // check if the button on the floor arrived is pressed in order to open the door 
  open_door();

  // reading value from potentiometer
  pot = analogRead(potpin);

  // change the motion of the lift
  if(up_calls[0]==1 || down_calls[0]==1)
    in_motion=1;

  // check for up routine
  if(up_calls[0]==1){

    //update current floor value based on value from potentiometer when calibrating
      if(current_floor==2){
          if(pot  == floors[2]-15){
            
            current_floor++;
        
          }
          
      }else if(current_floor==1){
        
          if(pot  ==floors[1]-15){
              
              current_floor++;
          }
         
      }

    // check for any up calls from current if so stop the motor,buzz, display floor number on LED and check for any other routine 
    
    if(up_calls[current_floor]==1){
        motor_stop();
        up_down=0;
        
        if(current_floor==2){
            arr2();
        }else{
            arr3();
        }

        in_motion=0;
        is_open=1;
        buzz();
        open_door();

        up_calls[current_floor]=0;
        bool any_up_calls = 0;
        for(int i=1;i<4;i++){
            if(up_calls[i]==1){
                any_up_calls=1;
                break;
            }
        }
        
        if(any_up_calls && down_calls[0]==0)
              up_calls[0]=1;
        else{
              up_calls[0]=0;
        }

        bool any_down_calls = 0;
        for(int i=1;i<4;i++){
            if(down_calls[i]==1){
                any_down_calls=1;
                break;
              }
         }

        
        if(any_down_calls && up_calls[0]==0)
            down_calls[0]=1;
        else{
            down_calls[0]=0;
        }

    }else{
        up_down++;
        if (up_down==1)
            motor_up();     
    }

  // check for down routine
  }else if(down_calls[0]==1){

    //update floor value like from the up routine
    if(current_floor == 3){
        if(pot ==floors[1]+15){
          
          current_floor--;
        }
        
     }else if(current_floor == 2){
         if(pot==floors[0]+15){
            
            current_floor--;
          }
          
     }

    // check for any down calls from any floors and perform the same task as the up calls
    
    if(down_calls[current_floor]==1  ){
        motor_stop();
        up_down=0;
        
        if(current_floor==2){
            arr2();
        }else{
            arr1();
        }
      
        in_motion=0;
        is_open=1;
        buzz();
        open_door();

        down_calls[current_floor]=0;
        bool any_down_calls = 0;
        for(int i=1;i<4;i++){
            if(down_calls[i]==1){
              any_down_calls=1;
              break;
            }
        }
        if(any_down_calls && up_calls[0]==0)
            down_calls[0]=1;
        else{
            down_calls[0]=0;
        }

        bool any_up_calls = 0;
        for(int i=1;i<4;i++){
            if(up_calls[i]==1){
                any_up_calls=1;
                break;
            }
        }
        
        if(any_up_calls && down_calls[0]==0)
            up_calls[0]=1;
        else{
            up_calls[0]=0;
        }
    }else{
      
      up_down++;
      if(up_down==1)
          motor_down();
    }
  }else{
    // do nothing if none of the routine matches
  }
}

