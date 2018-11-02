#ifndef FSCREEN_H
#define FSCREEN_H
#include<LiquidCrystal.h>

#define RS 2
#define EN 3
#define D4 4
#define D5 5
#define D6 6
#define D7 7

String songname[6] = {
    "All Star      ",
    "Gabe the 90's ",
    "Guiles Theme  ",
    "Titanic Flute ",
    "Wii Shop Music",
    "Fruit Salad   "
};

byte locksym[8] = {
  B01110,
  B10001,
  B11111,
  B10001,
  B10101,
  B10001,
  B11111,
};
void clearrow(LiquidCrystal lcd,int row){
    lcd.setCursor(0,row);
    lcd.print("                ");
}
LiquidCrystal startlcd(LiquidCrystal lcd,int volume){
    lcd.createChar(0,locksym);
    lcd.begin(16, 2);
    lcd.print("Box mode");
    lcd.setCursor(0,1);
    lcd.print("Volume:");
    lcd.setCursor(8,1);
    lcd.print(volume);
    return lcd;
}
void lcdprintbox(LiquidCrystal lcd){
    clearrow(lcd,0);
    lcd.setCursor(0,0);
    lcd.print("Box mode");
}
void lcdprintsong(LiquidCrystal lcd){
    clearrow(lcd,0);
    lcd.setCursor(0,0);
    lcd.print("Song mode");
}
void lcdprintlock(LiquidCrystal lcd){
    lcd.setCursor(14,0);
    lcd.write(byte(0));
}
void lcdprintvolume(LiquidCrystal lcd, int volume){
    clearrow(lcd,1);
    lcd.setCursor(0,1);
    lcd.print("Volume:");
    lcd.setCursor(8,1);
    lcd.print(volume);
}
void lcdprintsongname(LiquidCrystal lcd,int songnum){
    lcd.print("             ");
    lcd.setCursor(0,0);
    lcd.print(songname[songnum-1]);
}
#endif