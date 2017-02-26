#include <LiquidCrystal.h>


LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int bttnPin = 6;
const int bttnPin2 = 7;
int bttnState = 0;
int bttnState2 = 0;
int prevBttnState = 0;
int prevBttnState2 = 0;
unsigned long start = 0;
unsigned long current = 0;
String morseCode = "";
String prevMorseCode = "";
//dots are 1's, dashes are 0's
String mCodes[36] = {"10","0111","0101","011","1","1101","001","1111","11","1000",
                     "010","1011","00","01","000","1001","0010","101","111","0",
                     "110","1110","100","0110","0100","0011","10000","11000",
                     "11100","11110","11111","01111","00111","00011","00001","00000"};
String alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";                     

String alphaToMorse(String alphaPhrase)
{
  for(int i = 0;i<36;i++)
 {
    if (mCodes[i] == alphaPhrase)
    {
      return String(alpha[i]);
    }
  }
}

void setup()
{
  // put your setup code here, to run once:
  lcd.begin(16,2);
  lcd.print("Left:Dot or Dash");
  lcd.setCursor(0,1);
  lcd.print("Right:Decode");
  pinMode(13,OUTPUT);
  digitalWrite(13,0);

  pinMode(bttnPin,INPUT); //sets up pin to get input from bttn 1
  pinMode(bttnPin2,INPUT); //sets up pin to get input from bttn 2
}

void loop() 
{
  bttnState = digitalRead(bttnPin);

  if(bttnState != prevBttnState)
  {
    if(bttnState == HIGH)
    { 
      start = millis();
      //lcd.clear();
      //lcd.print("Decoding..."); 
    }
    else if(bttnState == LOW)
    {
      lcd.clear();
      current = millis();
      //lcd.print(current-start);
      if((current-start) < 250)
      {
         morseCode += "1";
      }
      else if((current-start) >= 250)
      {
        morseCode += "0";  
      }
    }
  }
  else
  {
     bttnState2 = digitalRead(bttnPin2);
     if(prevBttnState2 != bttnState2 && bttnState2 == HIGH)
     {
        lcd.clear();
        lcd.print("Decoded Letter:" + alphaToMorse(morseCode));
        //lcd.setCursor(8,1);
        //lcd.print(alphaToMorse(morseCode));
        morseCode = "";
     }
  }
  prevBttnState2 = bttnState2;
  prevBttnState = bttnState;
  if(prevMorseCode != morseCode)
  {
     lcd.print(morseCode);
  }
  prevMorseCode = morseCode;
}
