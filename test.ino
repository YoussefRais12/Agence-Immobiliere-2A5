#include <Wire.h>
#include <MFRC522.h>
#include <SPI.h>
#include <LiquidCrystal_I2C.h>
#define SS_PIN 10
#define RST_PIN 9
#define beep_pin 8
LiquidCrystal_I2C lcd(0x27,16,2); 
MFRC522 mfrc522(SS_PIN, RST_PIN);
void setup() {
  Serial.begin(9600);
    pinMode(beep_pin,OUTPUT);
  digitalWrite(beep_pin,LOW);
//lcd.begin();
lcd.init();
lcd.backlight(); 
lcd.print("Welcome!!");
delay(1000);
lcd.clear();
SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Put your card to the reader...");
  Serial.println();
//lcd.init();
}


void loop() {
//lcd.print("welcome"); 
//delay(500);
digitalWrite(beep_pin, LOW);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Put your card ");
  lcd.setCursor(0, 1);
  lcd.print("to the reader...");
  delay(800);
   char data; // tnjmch thez el data lil qt tant que string (hex code) //
     

 // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("UID tag :");
   // 91 D0 43 1B carte  
 // 93 F2 1B 9B cle 
  Serial.print("Message : ");
  content.toUpperCase();
    //lcd.print(content.substring(1));
  Serial.print(content.substring(1));
  if (content.substring(1) == "91 D0 43 1B") 
  {
    
      lcd.setCursor(0,0);
       lcd.print("Access  ");
       lcd.setCursor(0,1); 
 lcd.print("Autorisee ! ");
  
 delay(800);
  


    }

     else if (content.substring(1) == "93 F2 1B 9B") 
  {
         lcd.setCursor(0,0);
       lcd.print("Access  ");
       lcd.setCursor(0,1); 
 lcd.print("Interdit ! ");
  
 delay(800);
  

   
  }
 

}
