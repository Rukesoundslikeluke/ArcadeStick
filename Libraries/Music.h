#ifndef MUSIC_H
#define MUSIC_H
#include <SoftwareSerial.h>
static int8_t Send_buf[8] = {0} ;
static uint8_t ansbuf[10] = {0};

//MUSIC BOARD
#define ARDUINO_RX 1
#define ARDUINO_TX 0
//MUSIC CONTROLS
#define CMD_NEXT_SONG       0X01  // Play next song.
#define CMD_PREV_SONG       0X02  // Play previous song.
#define CMD_PLAY_W_INDEX    0X03

#define CMD_VOLUME_UP       0X04
#define CMD_VOLUME_DOWN     0X05
#define CMD_SET_VOLUME      0X06

#define CMD_SEL_DEV         0X09
#define DEV_TF              0X02
#define CMD_PLAY            0X0D
#define CMD_PAUSE           0X0E
#define CMD_PLAY_W_FOLDER   0x0F
#define CMD_SINGLE_CYCLE    0X19
#define SINGLE_CYCLE_ON     0X00
#define SINGLE_CYCLE_OFF    0X01
#define CMD_PLAY_W_VOL      0X22
#define CMD_PLAYSONG        0x0300
#define CMD_STOP_SONG       0x16

#define STARTVOLUME 0x000A


void sendCommand(SoftwareSerial mp3,int8_t command, int16_t dat){
    delay(20);
    Send_buf[0] = 0x7e; //starting byte
    Send_buf[1] = 0xff; //version
    Send_buf[2] = 0x06; //the number of bytes of the command without starting byte and ending byte
    Send_buf[3] = command; //
    Send_buf[4] = 0x00;//0x00 = no feedback, 0x01 = feedback
    Send_buf[5] = (int8_t)(dat >> 8);//datah
    Send_buf[6] = (int8_t)(dat); //datal
    Send_buf[7] = 0xef; //ending byte
    for(uint8_t i=0; i<8; i++){
        mp3.write(Send_buf[i]) ;
    }
}

SoftwareSerial startmp3(SoftwareSerial mp3){
    mp3.begin(9600);
    delay(400);
    mp3.write(0x7EFF0609000002EF);//select the TF card
    delay(400);
    sendCommand(mp3,CMD_SET_VOLUME,STARTVOLUME);
    delay(400);
    sendCommand(mp3,CMD_PLAY_W_FOLDER,0x0101);
    return mp3;
}
void mp3lockset(SoftwareSerial mp3, bool lock){
    if(lock == false){
        sendCommand(mp3,CMD_PLAY_W_FOLDER,0x0101);
    }
    else if(lock == true){
        sendCommand(mp3,CMD_PLAY_W_FOLDER,0x0102);
    }
}
void mp3playlp(SoftwareSerial mp3){
    sendCommand(mp3,CMD_PLAY_W_FOLDER,0x0201);
}
void mp3volumeup(SoftwareSerial mp3){
    sendCommand(mp3,CMD_VOLUME_UP,0x0000);
}
void mp3volumedown(SoftwareSerial mp3){
    sendCommand(mp3,CMD_VOLUME_DOWN,0x0000);
}
void mp3playsong(SoftwareSerial mp3, int songnum){
    sendCommand(mp3,CMD_PLAY_W_FOLDER,(CMD_PLAYSONG+songnum));
}
void mp3pauseplay(SoftwareSerial mp3,bool playing){
    if(playing == true){
        sendCommand(mp3,CMD_PAUSE,0x0000);
    }
    else{
        sendCommand(mp3,CMD_PLAY,0x0000);
    }
}
void mp3stopsong(SoftwareSerial mp3){
    sendCommand(mp3,CMD_STOP_SONG,0x0000);
}
#endif