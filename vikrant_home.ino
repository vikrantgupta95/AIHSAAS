#include<LiquidCrystal.h>
#include <dht.h>
LiquidCrystal lcd(7,8,9,10,11,12);
int history = 0;
int i, j;
int sem = 0;
dht DHT;
int h=0, d=0;
#include <Servo.h>
#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 rtc;

#define dht_dpin A5 
Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
void setup() {
  // put your setup code here, to run once:
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
  lcd.begin(20, 4);
  lcd.setCursor(0,0);
  lcd.print("AIHSAAS");
  lcd.setCursor(0,1);
  lcd.print("by Vikrant Gupta");
  lcd.setCursor(0,2);
  lcd.print("Guide: ");
   lcd.setCursor(0,3);
  lcd.print("Ms. Mahima Goel");
  delay(3000);
  lcd.clear();
Serial.begin(9600);
Serial.println("Device is ready!");
myservo.attach(6);  // attaches the servo on pin 9 to the servo object

  pinMode(2, INPUT); //door from node mcu
   digitalWrite(2, LOW);
     pinMode(3, INPUT); //relay1 from node mcu
   digitalWrite(3, LOW);
     pinMode(4, INPUT); //relay2 from node mcu
   digitalWrite(4, LOW);
     pinMode(5, INPUT); //relay3 from node mcu
   digitalWrite(5, LOW);
     pinMode(22, INPUT); //relay4 from node mcu
   digitalWrite(22, LOW);
   pinMode(24, OUTPUT); //relay1 
   digitalWrite(24, HIGH);
   pinMode(26, OUTPUT); //relay2 
   digitalWrite(26, HIGH);
   pinMode(28, OUTPUT); //relay3 
   digitalWrite(28, HIGH);
   pinMode(30, OUTPUT); //relay4 
   digitalWrite(30, HIGH);
     pinMode(32, OUTPUT); //motor
   digitalWrite(32, LOW);
      pinMode(36, INPUT); //from Nano door fingerprint
   digitalWrite(36, LOW);
    pinMode(A0, INPUT); //ldr
    pinMode(22, INPUT); //relay4 from node mcu
   digitalWrite(22, LOW);
     pinMode(A1, INPUT); //gas
     
      pinMode(A2, INPUT); //pir
        pinMode(A3, INPUT);  //ir 1
       pinMode(A4, INPUT); //ir 2
       pinMode(A6, INPUT); //ir 2
       digitalWrite(A6, HIGH); //watel level
 lcd.setCursor(0,0);
  lcd.print("H:");
   lcd.setCursor(10,0);
  lcd.print("T:");
   lcd.setCursor(0,1);
  lcd.print("LPG:");
   lcd.setCursor(10,1);
  lcd.print("LDR:");
     lcd.setCursor(0,2);
  lcd.print("Door: ");
  
}

void loop() {
  // put your main code here, to run repeatedly:
  DateTime now = rtc.now();
    
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print("  ");    
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
    
   DHT.read11(dht_dpin);
  i=DHT.humidity;
      j =DHT.temperature;
  Serial.print(i);
  Serial.print(" ");
  Serial.println(j);
         lcd.setCursor (3,0);
                lcd.print(i); 
                lcd.print(" ");
                   lcd.setCursor (15,0);
               lcd.print(j);
                lcd.print(" ");
                 lcd.setCursor (5,1);
               lcd.print(analogRead(A1));
                lcd.print(" ");
               lcd.setCursor (15,1);
               lcd.print(analogRead(A0));
                lcd.print(" ");
                delay(200);
               if(i>60) //humidity relay on
               { 
                Serial.println("Humidity high");
                   digitalWrite(30, LOW);
                  delay(2000);
              digitalWrite(30, HIGH);
                 
               }
               if(j>40 || analogRead(A1) >= 300) //temp motor or gas sensor
               {
                Serial.println("high temp. or gas trigger");
                digitalWrite(30, LOW);
                  delay(2000);
              digitalWrite(30, HIGH);
               }
               if(now.hour() == 7 && now.minute() == 0) //rtc for pump
               {
                Serial.println("Motor pump on");
                if(digitalRead(A6) == 0) //level reached
                {
                  digitalWrite(34, LOW); //off
                  Serial.println("Motor pump off level reached");
                }
                if(digitalRead(A6) == 1) //water level no
                {
                  digitalWrite(34, HIGH); //on
                    Serial.println("Motor pump on level not reached");
                }
               }
  Serial.println(analogRead(A0));
 if(digitalRead(A3) == 1) //going out 
 {
   lcd.setCursor(8,2);
  lcd.print("Open   ");
Serial.println("exit or entry door lock");
   for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  lcd.setCursor(8,2);
  lcd.print("Close  ");
 }
 if(digitalRead(2) == 1)
 {
   lcd.setCursor(8,2);
  lcd.print("Open   ");
  Serial.println("door lock using node mcu");
    for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
 }
  if(digitalRead(36) == 1)
 {
   lcd.setCursor(8,2);
  lcd.print("Open   ");
  Serial.println("door lock using finger");
    for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
   lcd.setCursor(8,2);
  lcd.print("Close   ");
 }
 if(digitalRead(3) == 1)
 {
  Serial.println("relay 1 on");
  digitalWrite(24, LOW);
 }
 if(digitalRead(3) == 0)
 {
   Serial.println("relay 1 off");
  digitalWrite(24, HIGH);
 }
 if(digitalRead(4) == 0)
 {
   Serial.println("relay 2 off");
  digitalWrite(26, HIGH);
 }
 if(digitalRead(4) == 1)
 {
   Serial.println("relay 2 on");
  digitalWrite(26, LOW);
 }


 if(digitalRead(5) == 1)
 {
   Serial.println("relay 3 on");
  digitalWrite(28, LOW);
 }
 if(digitalRead(5) == 0)
 {
   Serial.println("relay 3 off");
  digitalWrite(28, HIGH);
 }
 if(digitalRead(22) == 0 && sem ==1)
 {
  sem = 0;
   Serial.println("relay 4 off ");
  digitalWrite(30, LOW);
 }
 if(digitalRead(22) == 1 && sem ==0)
 {
  history++;
  d = now.day();
  h = now.hour();
   Serial.println("relay 4 on history");
  digitalWrite(30, HIGH);
 }
 if(history >= 10)
 {
  delay(3000);
   digitalWrite(30, LOW);
 }
 /*if(digitalRead(22) == 1 && sem ==0)
 {
  history++;
  d = now.day();
  h = now.hour();
   Serial.println("relay 4 on history");
  digitalWrite(30, LOW);
 }
 if(history >= 3 && now.day() == d+3 && now.hour() == h)
 {
   digitalWrite(30, LOW);
 }*/
 if(digitalRead(A4) == 1 || digitalRead(3) == 1) //table lamp
 {
   Serial.println("Table lamp on ");
   lcd.setCursor(0,3);
  lcd.print("Table Lamp On ");
  digitalWrite(24, LOW);
  delay(3000);
  lcd.setCursor(0,3);
  lcd.print("                   ");
  if(digitalRead(A4) == 1) 
 {
   Serial.println(" still Table lamp on");
  digitalWrite(24, LOW);
  lcd.setCursor(0,3);
  lcd.print("Table Lamp On ");
 
  delay(3000);
  lcd.setCursor(0,3);
  lcd.print("                   ");
  
 }
 if(digitalRead(A4) == 0)
 {
  Serial.println("Table lamp off");
  digitalWrite(24, HIGH);
   lcd.setCursor(0,3);
  lcd.print("Table Lamp Off");
  delay(5000);
  lcd.setCursor(0,3);
  lcd.print("                   ");
 }
 
 }
  if(digitalRead(A4) == 0)
 {
  Serial.println("Table lamp off");
  digitalWrite(24, HIGH);
   lcd.setCursor(0,3);
  lcd.print("Table Lamp Off");
  delay(5000);
  lcd.setCursor(0,3);
  lcd.print("                   ");
 }
 
 
 if(analogRead(A0)<100) //ldr
 {
   Serial.println("no light lamp on");
  digitalWrite(26, LOW);

   lcd.setCursor(0,3);
  lcd.print("Main Lamp On");
  delay(5000);
  lcd.setCursor(0,3);
  lcd.print("                   ");
   if(digitalRead(A2) == 1) //pir
  {
    Serial.println("no light lamp on pir");
     digitalWrite(26, LOW);

   lcd.setCursor(0,3);
  lcd.print("Main Lamp On");
  delay(5000);
  lcd.setCursor(0,3);
  lcd.print("                   ");
  }
  if(digitalRead(A2) == 0) //pir
  {
    Serial.println("no light no movement lamp off");
     digitalWrite(26, HIGH);

   lcd.setCursor(0,3);
  lcd.print("Main Lamp Off");
  delay(5000);
  lcd.setCursor(0,3);
  lcd.print("                   ");
  }
 }
  if(analogRead(A0)>=100) //ldr
 {
  Serial.println("light ");
   digitalWrite(26, HIGH);
 }
}



