
// Reference tone function: https://forum.arduino.cc/index.php?topic=136500.0

#define TONE_TIMER TC0    // using timer counter 1
#define TONE_CHNL 1       // channel 0 of timer counter 1
#define TONE_IRQ TC1_IRQn   // interrupts 

// variables required for starting the buzzers
volatile static int32_t toggle_count;
static uint8_t pinEnabled[PINS_COUNT];
static uint8_t TCChanEnabled = 0;
static boolean pin_state = false ;
static Tc *chTC = TONE_TIMER;
static uint32_t chNo = TONE_CHNL;

int melody[] = { 800,500};
//melody of the buzz


// note durations
int noteDurations[] = {2,2};



// tone function 
void tone(uint32_t ulPin, uint32_t frequency, int32_t duration)
{
    const uint32_t rc = VARIANT_MCK / 256 / frequency;
    ulPin=buzzer;
    toggle_count = 0;  // strange  wipe out previous duration
    if (duration > 0 ) toggle_count = 2 * frequency * duration / 1000;
     else toggle_count = -1;

    if (!TCChanEnabled) {
      pmc_set_writeprotect(false);
      pmc_enable_periph_clk((uint32_t)TONE_IRQ);
      TC_Configure(chTC, chNo,
        TC_CMR_TCCLKS_TIMER_CLOCK4 |
        TC_CMR_WAVE |         // Waveform mode
        TC_CMR_WAVSEL_UP_RC ); // Counter running up and reset when equals to RC

      chTC->TC_CHANNEL[chNo].TC_IER=TC_IER_CPCS;  // RC compare interrupt
      chTC->TC_CHANNEL[chNo].TC_IDR=~TC_IER_CPCS;
       NVIC_EnableIRQ(TONE_IRQ);
                         TCChanEnabled = 1;
    }
    if (!pinEnabled[ulPin]) {
      pinMode(ulPin, OUTPUT);
      pinEnabled[ulPin] = 1;
    }
    TC_Stop(chTC, chNo);
                TC_SetRC(chTC, chNo, rc);    // set frequency
    TC_Start(chTC, chNo);
}

// turning off the tone function

void noTone(uint32_t ulPin)
{
  TC_Stop(chTC, chNo);  // stop timer
  digitalWrite(ulPin,LOW);  // no signal on pin
}

// timer ISR  TC0 ch 1
void TC1_Handler () {
  TC_GetStatus(TC0, 1);
  if (toggle_count != 0){
    // toggle pin  TODO  better
    digitalWrite(buzzer,pin_state= !pin_state);
    if (toggle_count > 0) toggle_count--;
  } else {
    noTone(buzzer);
  }
}

// buzz function
void buzz(){
    for (int i = 0; i < 2; i++) {
      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000/noteDurations[i];
      tone(buzzer, melody[i],noteDuration);
      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      // stop the tone playing:
      noTone(buzzer);
    }
    delay(1000);
}

