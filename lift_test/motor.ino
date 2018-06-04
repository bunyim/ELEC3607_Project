// code recycled from the timer counter lab 3 of ELEC3607

int up = 66;    // duty cycle for going up
int down = 49;  // duty cycle for going down
int stopping = 53;  //duty cycle for stopping

// pwmwave for  the motor
void pwmwave1(unsigned int duty, unsigned int freq) {
  unsigned int tcclk= VARIANT_MCK / freq ;
  unsigned int ra = tcclk * (float)duty/100;
  TC_Configure(XTC, XCHAN1, TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | TC_CMR_TCCLKS_TIMER_CLOCK1 | TC_CMR_ACPC_SET | TC_CMR_ACPA_CLEAR);
  TC_SetRC(XTC, XCHAN1, tcclk);
  TC_SetRA(XTC, XCHAN1, ra);
}

// complementary pwm for the motor
void pwmwave2(unsigned int duty, unsigned int freq) {
  unsigned int tcclk= VARIANT_MCK / freq;
  unsigned int ra = tcclk * (float)duty/100;
  TC_Configure(XTC, XCHAN2, TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | TC_CMR_TCCLKS_TIMER_CLOCK1 | TC_CMR_ACPC_CLEAR | TC_CMR_ACPA_SET);
  TC_SetRC(XTC, XCHAN2, tcclk);
  TC_SetRA(XTC, XCHAN2, ra);
}


// setting up the 2 PWM and sync them for going up
void motor_up(){
  //Serial.println("\tGoing up..");
  pwmwave1(up,100000);
  pwmwave2(up,100000);
  TC_Start(XTC, XCHAN1);
  TC_Start(XTC,XCHAN2);
  TC_SYNC1=1;


}


// setting up the 2 PWM and sync them for going down
void motor_down(){
  //Serial.println("\tGoing down..");
  pwmwave1(down,100000);
  pwmwave2(down,100000);
  TC_Start(XTC, XCHAN1);
  TC_Start(XTC,XCHAN2);
  TC_SYNC1=1;
  

}

// setting up the 2 PWM and sync them for stopping
void motor_stop(){
  //Serial.println("\tStopping motor..");
  pwmwave1(stopping,100000);
  pwmwave2(stopping,100000);
  TC_Start(XTC, XCHAN1);
  TC_Start(XTC,XCHAN2);
  TC_SYNC1=1;

}
