const byte POT = 4; //Pin Definitions
const byte WATCHDOG = 5;
const byte BUTTON = 19; 
const byte ERROR = 18;
const byte SIG = 17;
volatile int count = 0;
volatile int avecount = 0;
volatile int POTval[4] = {0, 0, 0, 0};
volatile int POTvalave = 0;

void setup() 
{
  pinMode(POT, INPUT);
  pinMode(WATCHDOG, OUTPUT);
  pinMode(BUTTON, INPUT);
  pinMode(ERROR, OUTPUT);
  pinMode(SIG, INPUT);
  ledcSetup(0, 58, 16);
  ledcAttachPin(WATCHDOG, 0);
  ledcWrite(0, 190);
}



void loop() 
{
  if((count % 42)) == 0)
  {
    ADC();
    ADCAVE();
  }
  if((count % 200)) == 0)
  {
    BUTTONREAD();
  }
  if((count % 100)) == 0)
  {
    ASM();
  }
  if((count % 1000)) == 0)
  {
    SIGREAD();
  }
  if((count % 333)) == 0)
  {
    ERRORCALC();
    ERRORLED();
  }
  if((count % 5000)) == 0)
  {
    SERIAL()
  }
  delayMicroseconds(1):
  count++;
}

ADC()
{
  POTval[avecount] = analogRead(POT);
}

ADCAVE()
{
  int loop;
  int TOT = 0;
  avecount++;
  if(avecount >= 4) 
  {
    avecount = 0;
  }
  for(loop = 0; loop < 4; loop++) //add up last 4 readings
  {
      TOT = TOT + POTval[loop];
  }
  POTvalave = avep / 4; //find average of readings and save to global variable 
} 
