/*Output only - GPIO expander*/
//Pin connected to ST_CP of 74HC595
int latchPin = 7;
//Pin connected to SH_CP of 74HC595
int clockPin = 8;
////Pin connected to DS of 74HC595
int dataPin = 9;

typedef enum
{
  Led0 = 0,
  Led1,
  Led2,
  Led3,
  Led4,
  Led5,
  Led6,
  Led7,
  Led8,
  Led9,
  Led10,
  Led11,
  Led12,
  Led13,
  Led14,
  Led15,
}en_FuntionLeds;

typedef union 
{
  uint16_t Val;
  uint8_t ShiftVal[2];
}ShiftReg;
ShiftReg uShiftReg;

void DisplayLedVal(en_FuntionLeds enLed , uint8_t LedStatus);
void ResetLedShiftReg(void);
void setup() 
{
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  Serial.begin(9600);
  
  ResetLedShiftReg();
}
void loop()
{
  DisplayLedVal(Led1 , 1);
  DisplayLedVal(Led15 , 0);
  DisplayLedVal(Led13 , 1);
  delay(1000);
  DisplayLedVal(Led1 , 0);
  DisplayLedVal(Led15 , 1);
  DisplayLedVal(Led13 , 0);
  delay(1000);
}
void ResetLedShiftReg(void)
{
  #define RESET_VALUE (0xFF)
  uShiftReg.Val = 0;
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, RESET_VALUE);
  shiftOut(dataPin, clockPin, MSBFIRST, RESET_VALUE);
  digitalWrite(latchPin, HIGH);
  Serial.println("Led Reset");
}


void DisplayLedVal(en_FuntionLeds enLed , uint8_t LedStatus)
{
  if(LedStatus)
  {
    uShiftReg.Val |= ((0x0001 << (uint16_t)enLed));
  }
  else
  {
   uShiftReg.Val &= ~((0x0001 << (uint16_t)enLed)); 
  }
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, ~(uShiftReg.ShiftVal[0]));
  shiftOut(dataPin, clockPin, MSBFIRST, ~(uShiftReg.ShiftVal[1]));
  digitalWrite(latchPin, HIGH);
  Serial.println("Led : " + String(enLed) + "Status : " + String(LedStatus));
}
