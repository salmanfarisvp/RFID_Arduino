#include <RFID.h>

/*
* Read a card using a mfrc522 reader on your SPI interface
* Pin layout should be as follows (on Arduino Uno):
* MOSI: Pin 11 / ICSP-4
* MISO: Pin 12 / ICSP-1
* SCK: Pin 13 / ISCP-3
* SS/SDA: Pin 10
* RST: Pin 9
*/

#include <SPI.h>
#include <RFID.h>

#define SS_PIN 10
#define RST_PIN 9

RFID rfid(SS_PIN,RST_PIN);


int self = 7;
int bat = 8; 
int s = 6;

int serNum[5];
int cards[][5] = {
  {42,249,70,213,64}
  
};

bool access = false;

void setup(){

    Serial.begin(9600);
    SPI.begin();
    rfid.init();

    pinMode(self, OUTPUT);
    pinMode(bat ,OUTPUT);
    pinMode(s,OUTPUT);
    

    digitalWrite(self, LOW);
    digitalWrite(bat , LOW);
   
}

void loop(){
    
    if(rfid.isCard()){
    
        if(rfid.readCardSerial()){
            Serial.print(rfid.serNum[0]);
            Serial.print(" ");
            Serial.print(rfid.serNum[1]);
            Serial.print(" ");
            Serial.print(rfid.serNum[2]);
            Serial.print(" ");
            Serial.print(rfid.serNum[3]);
            Serial.print(" ");
            Serial.print(rfid.serNum[4]);
            Serial.println("");
            
            for(int x = 0; x < sizeof(cards); x++){
              for(int i = 0; i < sizeof(rfid.serNum); i++ ){
                  if(rfid.serNum[i] != cards[x][i]) {
                      access = false;
                      break;
                  } else {
                      access = true;
                  }
              }
              if(access) break;
            }
           
        }
        
       if(access){
          Serial.println("Welcome!");
          digitalWrite(bat,HIGH);
          digitalWrite(self,HIGH);
          delay(1000);
          digitalWrite(self,LOW);
          
      } else {
           Serial.println("Not allowed!");
          digitalWrite(s,HIGH);
          delay(2000);
          digitalWrite(s,LOW); 
          digitalWrite(bat,LOW);
                    
       }        
    }
    
    
    
    rfid.halt();

}

