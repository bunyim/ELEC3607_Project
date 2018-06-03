// a simple terminal based user interface to control the lift based on user input
#define XCHAN1  0         // TC channel
#define XID    ID_TC6    // Instance ID
#define XCHAN2 1
#define XTC TC2
#define XID1 ID_TC7

#define TC_SYNC1 (*(WoReg*) 0x400880C0)

int potpin=0;
#define  PINCHAN  25      // Digital pin 2 which is on PIOB channel 25
#define VARIANT_MCK 41999026




int down=49;


void pwmwave1(unsigned int duty, unsigned int freq) {
  unsigned int tcclk= VARIANT_MCK / freq ;
  unsigned int ra = tcclk * (float)duty/100;
  TC_Configure(XTC, XCHAN1, TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | TC_CMR_TCCLKS_TIMER_CLOCK1 | TC_CMR_ACPC_SET | TC_CMR_ACPA_CLEAR);
  TC_SetRC(XTC, XCHAN1, tcclk);
  TC_SetRA(XTC, XCHAN1, ra);
}


void pwmwave2(unsigned int duty, unsigned int freq) {
  unsigned int tcclk= VARIANT_MCK / freq;
  unsigned int ra = tcclk * (float)duty/100;
  TC_Configure(XTC, XCHAN2, TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | TC_CMR_TCCLKS_TIMER_CLOCK1 | TC_CMR_ACPC_CLEAR | TC_CMR_ACPA_SET);
  TC_SetRC(XTC, XCHAN2, tcclk);
  TC_SetRA(XTC, XCHAN2, ra);
}
int current_floor = 0;

void setup() {
  unsigned int chanmask = (1 << PINCHAN)|(1<<28);

  Serial.begin(9600);
  // set PIO to chan C
  REG_PIOC_PDR = chanmask;
  REG_PIOC_ABSR = chanmask;
  REG_PIOC_MDDR = chanmask;
  
  // set up TC
  pmc_set_writeprotect(false);
  pmc_enable_periph_clk(XID1);
  pmc_enable_periph_clk(XID);
  pwmwave1(50,100000);
  pwmwave2(50,100000);
  TC_Start(XTC, XCHAN1);
  TC_Start(XTC,XCHAN2);
  TC_SYNC1=1;



  int val = analogRead(potpin);

  if (val>614 && val < 624)
    current_floor = 1;
  else if(val> 505 && val< 515)
    current_floor = 2;
  else if(val > 398 && val< 408)
    current_floor = 3;

  Serial.println("Current floor is now at "+String(current_floor));
  delay(1000);
}



void motor_up(){
  
  pwmwave1(67,100000);
  pwmwave2(67,100000);
  TC_Start(XTC, XCHAN1);
  TC_Start(XTC,XCHAN2);
  TC_SYNC1=1; 
  
}

void motor_stop(){
  
  pwmwave1(53,100000);
  pwmwave2(53,100000);
  TC_Start(XTC, XCHAN1);
  TC_Start(XTC,XCHAN2);
  TC_SYNC1=1; 
  
  
}


void motor_down(){
  
  pwmwave1(down,100000);
  pwmwave2(down,100000);
  TC_Start(XTC, XCHAN1);
  TC_Start(XTC,XCHAN2);
  TC_SYNC1=1; 
  
  
}

// assuming potentiometer value when u reach floor 2 and floor 3 from up routine




//assuming potentiometer value when u reach floor 2 and floor 1 from down routine


//0 for up and 1 for down routine and 2 for stop routine
int routine=2;
void loop() {
 // tcregs();
  int val = analogRead(potpin);


  
  Serial.println("Value receive is "+String(val));
  
  if(Serial.available()){
    
    String command= Serial.readString();
    if(command=="UP"){
      
      motor_up();  
      routine = 0;    
      }else if(command=="DOWN"){
       
      motor_down();  
      routine = 1;
      }else if(command=="STOP"){
        
        
        motor_stop();
        routine = 2;
       }else if(command=="NEW"){
        Serial.println("enter new duty cycle for down: ");
        while(!Serial.available()){
          
          }
        down = Serial.parseInt();
        command="STOP";
        
        }
       
    
    }

}
