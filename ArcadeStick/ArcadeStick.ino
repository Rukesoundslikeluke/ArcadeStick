#include<Music.h>
#include<IRcommands.h>
#include<FButtons.h>
#include<FScreen.h>
#include<MegaJoy.h>
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);
SoftwareSerial mp3(ARDUINO_RX, ARDUINO_TX);
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup() {
  //Buttons
  startbuttons();
  //LCD
  lcd = startlcd(lcd,STARTVOLUME);
  //activate pull-up resistor on the push-button pin
  pinMode(lightpunch, INPUT_PULLUP);
  //Activate IR reciever
  startIR(irrecv);
  //Music board init
  mp3 = startmp3(mp3);
  
  setupMegaJoy();
  delay(1000);
}

bool sound = false;//true if sound is being or has played for press
bool song = false;
bool updatemenu = false;
bool updatevol = false;
int menu = 1;
int volume = STARTVOLUME;
bool lock = false;
int songchoice = 0;
bool playing = false;
bool startsong = false;

megaJoyControllerData_t getControllerData(void){
  
  // Set up a place for our controller data
  //  Use the getBlankDataForController() function, since
  //  just declaring a fresh dataForController_t tends
  //  to get you one filled with junk from other, random
  //  values that were in those memory locations before
  megaJoyControllerData_t controllerData = getBlankDataForMegaController();
  // Since our buttons are all held high and
  //  pulled low when pressed, we use the "!"
  //  operator to invert the readings from the pins
  controllerData.buttonArray[0] = digitalRead(mediumpunch);
  controllerData.buttonArray[1] = digitalRead(mediumkick);
  controllerData.buttonArray[2] = digitalRead(lightpunch);
  controllerData.buttonArray[3] = digitalRead(lightkick);
  
  controllerData.buttonArray[4] = digitalRead(heavypunch);
  controllerData.buttonArray[5] = digitalRead(heavykick);
  controllerData.buttonArray[6] = digitalRead(allpunch);
  controllerData.buttonArray[7] = digitalRead(allkick);
  
  controllerData.dpad0UpOn = digitalRead(moveup);
  controllerData.dpad0DownOn = digitalRead(movedown);
  controllerData.dpad0LeftOn = digitalRead(moveleft);
  controllerData.dpad0RightOn = digitalRead(moveright);
  // And return the data!
  return controllerData;
}

void loop() {
    
    megaJoyControllerData_t controllerData = getControllerData();
    setControllerData(controllerData);
    int input = digitalRead(lightpunch);
    if(input == 0 && sound == false && song == false){
      sound = true;
      mp3playlp(mp3);
    }
    else if(input == 1 && sound == true && song == false){
      sound = false;
    }

    if (irrecv.decode(&results)){//REMOTE COMMANDS
      if(lock == false){//ALL MODE COMMANDS
        if(results.value == SKIPFORWARD || results.value == SKIPBACK){//Change menu
          menu = (menu + 1) % 2;
          mp3stopsong(mp3);
          songchoice = 0;
          updatemenu = true;
        }
        if(results.value == VOLUP){ //Volume up
          mp3volumeup(mp3);
          volume += 1;
          if(volume > 30){
            volume = 30;
          }
          updatevol = true;
        }
        else if(results.value == VOLDOWN){ // Volume down
          mp3volumedown(mp3);
          volume -= 1;
          if(volume < 0){
            volume = 0;
          }
          updatevol = true;
        } 
      }
      
      if(song == true && lock == false){//IN SONG MODE
        if(results.value == PLAY){
          mp3pauseplay(mp3,playing);
          playing = !playing;
        }
        if(results.value == N1){
          songchoice = 1;
          startsong = true;
          updatemenu = true;
        }
        else if(results.value == N2){
          songchoice = 2;
          startsong = true;
          updatemenu = true;
        }
        else if(results.value == N3){
          songchoice = 3;
          startsong = true;
          updatemenu = true;
        }
        else if(results.value == N4){
          songchoice = 4;
          startsong = true;
          updatemenu = true;
        }
        else if(results.value == N5){
          songchoice = 5;
          startsong = true;
          updatemenu = true;
        }
        else if(results.value == N6){
          songchoice = 6;
          startsong = true;
          updatemenu = true;
        }
        if(startsong == true){
          mp3playsong(mp3,songchoice);
          startsong = false;
          playing = true;
        }
      }
      if(results.value == POWER){//LOCK
        lock = !lock;
        if(song == false){//dont want to interrupt songs
          mp3lockset(mp3,lock);
        }
        updatemenu = true;
      }
        irrecv.resume();
    }//END OF REMOTE COMMANDS
    
    if(updatemenu == true || updatevol == true){//LCD SECTION
      if(menu == 0 && updatevol == false){
        lcdprintsong(lcd);
        song = true;
      }
      else if(menu == 1){
        lcdprintbox(lcd);
        song = false;
      }
      if(updatevol == true){
        lcdprintvolume(lcd,volume);
        updatevol = false;
      }
      if(lock == true){
        lcdprintlock(lcd);
      }
      if(songchoice != 0 && song == true){
        lcdprintsongname(lcd,songchoice);
      }
      updatemenu = false;
    }//END OF LCD SECTION
    
}
