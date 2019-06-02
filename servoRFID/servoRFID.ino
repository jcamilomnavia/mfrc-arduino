//Librerias para el Lector MFRC522
#include <SPI.h>
#include <MFRC522.h>
//Libreria ServoMotor
#include <Servo.h>

#define RST_PIN 9
#define SS_PIN 10

//Instancia de la clase MDRC522
MFRC522 mfrc522(SS_PIN, RST_PIN);
//Instancia de la clase Servo para el servomotor
Servo miServo;
int pos = 0; 

byte nuidPICC[4];                       //Esta variable guardara el ID de algun dispositivo RFID
byte knownTac[4] = {245,218,230,34};    //Esta variable es el ID conocido del dispositivo RFID que obtuvimos anteriormente
boolean KNOW = true;

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  miServo.attach(4);  //Conectamos el servo al pin 4
}

void loop() {
  if(mfrc522.PICC_IsNewCardPresent()){
    if(mfrc522.PICC_ReadCardSerial()){
      //Guardamos el ID del dispositivo RFID que estamos leyendo
      for (byte i = 0; i < 4; i++) {
        nuidPICC[i] = mfrc522.uid.uidByte[i];
      }
      //Verificamos que el ID sea el mismo ID que ya conocemos para luego mover el Servo
      for(int i = 0; i < mfrc522.uid.size; i++){                     
        if (knownTac[i] != nuidPICC[i]){    //Comparamos cada posicion del arreglo de bytes
          KNOW = false;                     //Si el ID no coincide, declaramos KNOW en falso
          Serial.println("KNOW is False, exiting cycle");
          break;                            //y nos salimos del ciclo
        }else{
          Serial.println("KNOW is True");
          KNOW = true;                      //Si cada byte coincide con el ID,KNOW es verdadero y seguiremos el ciclo normal
        }
      }
      Serial.println();
      mfrc522.PICC_HaltA();
    }
    if(KNOW){                             //Si la variable KNOW es verdadera/true
      Serial.print("Abrir la puerta");     //Abriremos la puerta/servomotr
      for(pos = 0; pos <= 180; pos += 1) { //Iremos de 0 a 180 grados en pasos(steps) de 1
        miServo.write(pos);                 //Indicarle al servomotor de ir a la posicion
        delay(15);                          //Esperar 15ms para que el servo alcance la posicion
      }
      for (pos = 180; pos >= 0; pos -= 1) { // Iremos de 180 a 0 grados en pasos(steps) de 1 
        miServo.write(pos);                 //Indicarle al servomotor de ir a la posicion
        delay(15);                          //Esperar 15ms para que el servo alcance la posicion
      }
    }
  }
}
