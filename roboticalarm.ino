#include <DS3231.h>
#include <SPI.h>
#include <SD.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
LiquidCrystal_I2C lcd(0x27,16,2);
DS3231 rtc(SDA, SCL);



File dosya ;
unsigned long sure;


const int motionpin=A0;
const int ledpin=8;
const int buzzpin=9;
int motionsensvalue=0;

void setup (){

  rtc.begin();
  
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Alarm System");
  delay (1000);
  lcd.clear();

 
 
  
 Serial.begin(9600);
  Wire.begin();
 
  while (!Serial){
  ;
 }

 Serial.println("SD kart başlatılıyor");

 if (!SD.begin(4)){
  Serial.println("SD kart başlatılamadı");
  while(1);
 }
  pinMode(ledpin, OUTPUT);
pinMode(motionpin,INPUT);
pinMode(buzzpin,OUTPUT);
}


void loop () {



 
motionsensvalue=analogRead(motionpin); 
  if (motionsensvalue>=200){
    digitalWrite(ledpin,HIGH);
tone(buzzpin,100);
lcd.setCursor(0,0);
  lcd.print("Motion Detected");
  lcd.setCursor(0,1);
  lcd.print("Time: ");
  lcd.print(rtc.getTimeStr());
  
  
  delay (2000);
  lcd.clear();
  

  }
 else {
  digitalWrite(ledpin,LOW);
  noTone(buzzpin);  
   lcd.setCursor(0,0);
  lcd.print("Alarm System");
 }

  dosya= SD.open("text.txt",FILE_WRITE);
  if (dosya) {
    
    dosya.print(rtc.getTimeStr());
    dosya.println("Hareket Algılandı");
    dosya.close();
     if (motionsensvalue>=200){
    Serial.print("Hareket Algılandı ");
    Serial.println(rtc.getTimeStr());
     }
  }
  else{
    Serial.println("Dosya Açılamadı");
  }

  delay (2000);
}
