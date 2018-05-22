// include the library code:
#include <LiquidCrystal.h>
#include <Arduino.h>

// initialize the library with the numbers of the interface pins
//LiquidCrystal(rs, rw, d4, d5, d6, d7) 

LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);


void lcdSetup() {
  // set up the LCD's number of columns and rows:
  pinMode(LCD_RS, OUTPUT);
  pinMode(LCD_EN, OUTPUT);
  pinMode(LCD_D4, OUTPUT);
  pinMode(LCD_D5, OUTPUT);
  pinMode(LCD_D6, OUTPUT);
  pinMode(LCD_D7, OUTPUT);
  lcd.begin(16, 2);
}

void lcdPrintInstruction(byte instruction){
  lcd.setCursor(1, 0);  
  if(instruction == 0) lcd.print("STOP");  
  if(instruction == 1) lcd.print("GO");  
  if(instruction == 2) lcd.print("TURN LEFT");  
  if(instruction == 4) lcd.print("TURN RIGHT");  
}

void lcdPrintCommand(String cmd){
  lcd.clear();
  lcd.setCursor(0, 1);  
  lcd.print(cmd);  
}

void lcdPrintStatus(byte status) {  

  lcd.setCursor(0, 0);  
  
  if(status == B00000000) lcd.print("----");  

  if(status == B00000001) lcd.print("---x");  
  if(status == B00000010) lcd.print("--x-");  
  if(status == B00000011) lcd.print("--xx");  
  if(status == B00000100) lcd.print("-x--");  

  if(status == B00000101) lcd.print("-x-x");  
  if(status == B00000110) lcd.print("-xx-");  
  if(status == B00000111) lcd.print("-xxx");  
  if(status == B00001000) lcd.print("x---");  

  if(status == B00001001) lcd.print("x--x");  
  if(status == B00001010) lcd.print("x-x-");  
  if(status == B00001011) lcd.print("x-xx");  
  if(status == B00001100) lcd.print("xx--");  

  if(status == B00001101) lcd.print("xx-x");  
  if(status == B00001110) lcd.print("xxx-");  
  if(status == B00001111) lcd.print("xxxx");  
  

  // char * b;

  // for(int i =0 ; i < 8 ; i++)
  // {
  //     b[i] = 48 + (status & (B10000000 >> i));
  // }
     
}
