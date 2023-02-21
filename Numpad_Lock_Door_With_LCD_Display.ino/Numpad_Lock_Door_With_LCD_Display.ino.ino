#include <Password.h>         //library for passwords
#include <Keypad.h>           //library for Keypad
#include <LiquidCrystal.h>    //library for LCD


const int rs = 13, e = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8;
LiquidCrystal lcd(rs, e, d4, d5, d6, d7);

Password password = Password("0000");   //our passwords

int ledGreen = 18;    //initialize pinout for green
int ledRed = 19;    //initialize pinout for red

const byte Row = 4;   //constant row number on keypad
const byte Collumn = 3;   //constant collumn number on keypad
char keys[Row][Collumn] =   //mapping Row dan Collumn to character
{
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte rowPin[Row] = { 3, 2, 1, 0 };    //initialize pinout for row keypad
byte collumnPin[Collumn] = { 4, 5, 6 };       //initialize pinout for collumn keypad

//membuat objek keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPin, collumnPin, Row, Collumn );

void login()
{
  if (password.evaluate())    
  {
    // if password is correct then solenoid door value will LOW and the door is opened
    digitalWrite(ledRed, LOW);    //led red off
    digitalWrite(ledGreen, HIGH);   //led green on 
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Password correct");    //LCD Display when the password is correct
    lcd.setCursor(0,1);
    lcd.print("Door Opened");     //LCD Display when the password is correct
    delay(3000);
    // after 3 second solenoid door value back to HIGH value and the door is lock
    digitalWrite(ledRed, HIGH);   //led red on
    digitalWrite(ledGreen, LOW);    //led green off
    lcd.clear();
    lcd.print("Password:");
    password.reset();   // password will be reset automatically
  }else{
    // if password is incorrect then solenoid door value will be HIGH and the door is remains lock
    digitalWrite(ledRed, HIGH);   //led red on
    digitalWrite(ledGreen, LOW);    //led green off
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Password Incorrect");    // Lcd Display when the password is incorrect
    delay(3000);

    // after 3 second solenoid door value back to HIGH value and the door is lock
    lcd.clear();
    lcd.print("Password:");
    password.reset();
  }
}

void keypadEvent(KeypadEvent eKey)
{
  switch (keypad.getState())
  {
    case PRESSED:
    Serial.println(eKey);
    delay(10);

    switch (eKey)
    {
      case '*': login(); delay(1); break;   // asteriks button as the enter button
  
      case '#': password.reset(); delay(1); break;    // hastag button as to delete the input value as well to resetting passwords

      default: password.append(eKey); delay(1);
    }
  }
}
void setup()
{
  Serial.begin(9600);          
  lcd.begin(16, 2);               //initialize value number of row and collumn at lcd
  pinMode(ledGreen, OUTPUT);      //configure green led as output
  pinMode(ledRed, OUTPUT);      //configure red led as output
  digitalWrite(ledRed, HIGH);   //first condition of red led value is HIGH

  keypad.addEventListener(keypadEvent);

  //write Password: in beginning of lcd
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Password:");
}


void loop()
{
  char key = keypad.getKey();
  if(key)
  {
    if((key != '*')&&(key != '#'))    //if input not same as asteriks and hastag
    {
      lcd.print("*");   //the input password will printed as astriks
    }

    if(key == '#')    //if input same as hastag it will clear the input
    {
      lcd.clear();
      lcd.print("Password:");
    }
  }
}
