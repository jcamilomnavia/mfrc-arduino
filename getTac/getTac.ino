//Librerias para el Lector MFRC522
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 9
#define SS_PIN 10

//Instancia de la clase MDRC522
MFRC522 mfrc522(SS_PIN, RST_PIN);


void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("Lectura UID");
}


void loop() {
  if(mfrc522.PICC_IsNewCardPresent()){
    if(mfrc522.PICC_ReadCardSerial()){
      Serial.print("Card UID:");
      //Para imprimir la identificacion en hexadecimal
      for(byte i=0; i<mfrc522.uid.size;i++){
          Serial.print(mfrc522.uid.uidByte[i]<0x10 ? "0":" ");
          Serial.print(mfrc522.uid.uidByte[i],HEX);
          
        }
        //Para imprimir la identificacion en Decimal
        //Esta es la usada en el archivo servoRFID.ino
        for(byte i=0; i<mfrc522.uid.size;i++){
          Serial.print(mfrc522.uid.uidByte[i]<0x10 ? "0":" ");
          Serial.print(mfrc522.uid.uidByte[i],DEC);
          
        }
        
        Serial.println();
        mfrc522.PICC_HaltA();
    }
  }
}
