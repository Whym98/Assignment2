const byte POT = 4; //Pin Definitions
const byte WATCHDOG = 5;
const byte BUTTON = 19; 
const byte ERROR = 18;
const byte SIG = 17;
volatile int count = 0;
volatile int avecount = 0;
volatile int POTval[4] = {0, 0, 0, 0};
volatile int POTvalave = 0;
volatile byte BUTTONSTATE = 0;
volatile byte error_code = 0;
volatile double SIGFREQ = 0;

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
  if((count % 42) == 0)
  {
    ADC();
    ADCAVE();
  }
  if((count % 200) == 0)
  {
    BUTTONREAD();
  }
  if((count % 100) == 0)
  {
    ASM();
  }
  if((count % 1000) == 0)
  {
    SIGREAD();
  }
  if((count % 333) == 0)
  {
    ERRORCALC();
    ERRORLED();
  }
  if((count % 5000) == 0)
  {
    SERIALPRINT();
  }
  delayMicroseconds(1);
  count++;
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
  BUTTONSTATE = digitalRead(BUTTON);
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
  int pulsetime = 0;
  pulsetime = pulseIn(SIG, HIGH, 2500);
  SIGFREQ = 1000000 / pulsetime;
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
