
// Date and time functions using a DS1307 RTC connected via I2C and Wire lib
#include <SPI.h>
#include <SD.h>
int count =0;
const int chipSelect = 4;

#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>

int getFingerprintIDez();

// pin #2 is IN from sensor (GREEN wire)
// pin #3 is OUT from arduino  (WHITE wire)
SoftwareSerial mySerial(2, 3);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

// On Leonardo/Micro or others with hardware serial, use those! #0 is green wire, #1 is white
//Adafruit_Fingerprint finger = Adafruit_Fingerprint(&Serial1);

void setup()  
{
  
   Serial.begin(9600);
   
    Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
   // return;
  }
  Serial.println("card initialized.");
 
 // while (!Serial);  // For Yun/Leo/Micro/Zero/...
  
 
  Serial.println("Adafruit finger detect test");

  // set the data rate for the sensor serial port
  finger.begin(57600);
  
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1);
  }
  Serial.println("Waiting for valid finger...");
   pinMode(5, OUTPUT);
  digitalWrite(5, LOW);
    pinMode(6, OUTPUT);
  digitalWrite(6, LOW);

}

void loop()                     // run over and over again
{
  
  getFingerprintID();
 
    
   
    
  delay(50);            //don't ned to run this at full speed.
}

uint8_t getFingerprintID() {
   
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No finger detected");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK success!

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
  
  // OK converted!
  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Found a print match!");
      digitalWrite(5, HIGH);
      //to mega open door
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("Did not find a match to node mcu");
     digitalWrite(6, HIGH); //to node mcu
     delay(2000);
      digitalWrite(6, LOW);
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   
  
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence); 
  if(finger.fingerID == 12)
  {
    count++;
    String str = String(count);
    String datastr = ". Vikrant Gupta";
str += String(datastr);

      Serial.println("Vikrant data loaded");
      delay(2000);
      digitalWrite(5, LOW); 
       File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
   dataFile.println(str);
  Serial.println("closed file");
    dataFile.close();
    // print to the serial port too:
      
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }
  }
  if(finger.fingerID == 13)
  {
    count++;
    String str = String(count);
    String datastr = ". Neha Gupta";
str += String(datastr);

    Serial.println("Piyush data loaded");
    delay(2000);
      digitalWrite(5, LOW); 
      File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
   dataFile.println(str);
  
  
    dataFile.close();
    // print to the serial port too:
      digitalWrite(10, LOW); //reset
    delay(2000);
    digitalWrite(10, HIGH); //reset
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }
  }
  if(finger.fingerID == 14)
  {
    count++;
    String str = String(count);
    String datastr = ". Mrs. Sanju Gupta";
str += String(datastr);


    Serial.println("Neha data loaded");
    delay(2000);
      digitalWrite(5, LOW); 
      File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(str);
  
  
    dataFile.close();
    // print to the serial port too:
      digitalWrite(10, LOW); //reset
    delay(2000);
    digitalWrite(10, HIGH); //reset
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }
  }
  if(finger.fingerID == 15)
  {
    count++;
    String str = String(count);
    String datastr = ". Mr. U.K. Gupta";
str += String(datastr);


    Serial.println("Shreya data loaded");
    delay(2000);
      digitalWrite(5, LOW); 
      File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
  dataFile.println(str);
  
    dataFile.close();
   
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }
  }
}

// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;
  
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  return finger.fingerID; 
}
