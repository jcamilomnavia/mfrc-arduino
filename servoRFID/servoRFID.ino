#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

#define RST_PIN 9
#define SS_PIN 10

//Instancia de la clase MDRC522
MFRC522 mfrc522(SS_PIN, RST_PIN);
//Instancia de la clase Servo para el servomotor
Servo miServo;
int pos = 0; 

byte nuidPICC[4];
byte knownTac[4] = {245,218,230,34};
boolean KNOW = true;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("Lectura UID");
  miServo.attach(4);  // attaches the servo on pin 3 to the servo object
  Serial.println("Servo Attached");
}


void loop() {
  // put your main code here, to run repeatedly:
  if(mfrc522.PICC_IsNewCardPresent()){
    if(mfrc522.PICC_ReadCardSerial()){
      
        for (byte i = 0; i < 4; i++) {
          nuidPICC[i] = mfrc522.uid.uidByte[i];
        }

        for(int i = 0; i < mfrc522.uid.size; i++){                     
          if (knownTac[i] != nuidPICC[i]){
            KNOW = false;
            Serial.println("KNOW is False, exiting cycle");
            break;
          }else{
          Serial.println("KNOW is True");
          KNOW = true;
          }
        }
        
        Serial.println();
        mfrc522.PICC_HaltA();
    }
        if(KNOW){                            
         Serial.print("OPEN THE DOOR");
         for(pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
         // in steps of 1 degree
          miServo.write(pos);              // tell servo to go to position in variable 'pos'
          delay(15);                       // waits 15ms for the servo to reach the position
         }
        for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
          miServo.write(pos);              // tell servo to go to position in variable 'pos'
          delay(15);                       // waits 15ms for the servo to reach the position
        }
      
    }
    //miServo.detach();
}
}
