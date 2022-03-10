#include <Ticker.h>

const byte POT = 4; //Pin Definitions
const byte WATCHDOG = 5;
const byte BUTTON = 22; 
const byte ERROR = 18;
const byte SIG = 17;
const byte TASK3 = 19;
volatile int count = 1;
volatile int avecount = 0;
volatile int POTval[4] = {1, 1, 1, 1};
volatile int POTvalave = 1;
volatile byte BUTTONSTATE = 0;
volatile byte error_code = 0;
volatile int SIGFREQ = 0;
Ticker periodicTicker;

void setup() 
{
  Serial.begin(115200);
  pinMode(POT, INPUT);
  pinMode(WATCHDOG, OUTPUT);
  pinMode(BUTTON, INPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(ERROR, OUTPUT);
  pinMode(SIG, INPUT);
  pinMode(TASK3, OUTPUT);
  periodicTicker.attach_ms(2, TICKER);
}


void TICKER() 
{
  count++;
  if((count % 9) == 0)
  {
    RUNWATCHDOG();
  }
  if((count % 21) == 0)
  {
    ADC();
    ADCAVE();
  }
  if((count % 100) == 0)
  {
    BUTTONREAD();
  }
  if((count % 50) == 0)
  {
    ASM();
  }
  if((count % 500) == 0)
  {
    SIGREAD();
  }
  if((count % 167) == 0)
  {
    ERRORCALC();
    ERRORLED();
  }
  if((count % 2500) == 0)
  {
    SERIALPRINT();
  }
}

void loop()
{
  
}

void RUNWATCHDOG()
{
  digitalWrite(WATCHDOG, HIGH);
  delayMicroseconds(50);
  digitalWrite(WATCHDOG, LOW);
}

void ADC()
{
  POTval[avecount] = analogRead(POT);
  avecount++;
  if(avecount >= 3) 
  {
    avecount = 0;
  }
}

void ADCAVE()
{
  int loop;
  int TOT = 0;
  for(loop = 0; loop < 4; loop++) //add up last 4 readings
  {
      TOT = TOT + POTval[loop];
  }
  POTvalave = TOT / 4; //find average of readings and save to global variable 
} 

void BUTTONREAD()
{
  BUTTONSTATE = !digitalRead(BUTTON); 
}

void ASM()
{
  int i;
  for(i = 0; i < 1000; i++)
  {
    __asm__ __volatile__ ("nop");
  }
}

void SIGREAD()
{
  digitalWrite(TASK3, HIGH);
  int pulsetime = 0;
  pulsetime = (pulseIn(SIG, HIGH, 2500)) * 2;
  if(pulsetime != 0)
  {
    SIGFREQ = (1000000 / pulsetime)* 0.96;
  }
  digitalWrite(TASK3, LOW);
}

void ERRORCALC()
{
  if(POTvalave > 2048)
  {
    error_code = 1;
  }
  else
  {
    error_code = 0;
  }
}

void ERRORLED()
{
  digitalWrite(ERROR, error_code);
}

void SERIALPRINT()
{
  Serial.print(BUTTONSTATE);
  Serial.print(",");
  Serial.print(SIGFREQ);
  Serial.print(",");
  Serial.println(POTvalave);
}
