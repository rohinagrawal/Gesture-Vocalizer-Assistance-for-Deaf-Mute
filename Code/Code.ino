/*

 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** SCK/CLK - pin 13
 ** CS - pin 4

 created   Mar 2018
 by Rohin Agrawal


 */

 /*
  * specifications of the audio file to be converter to .wav format
  * Samples Rate(per second) (Hz): 16000 
  * Audio Channel: Mono 
  * Bits Resolution (Per Sample): 8
  * PCM format: PCM unsigned 8-bit
  */

 /*
  * 
  * VSS = GND
  * VDD = 5V
  * V0 = 10K-POT/GND
  * RS = PIN 7
  * R/W = GND
  * E = PIN 6
  * D0,D1,D2,D3 = N/A
  * D4 = PIN 5
  * D5 = PIN 8
  * D6 = PIN 3
  * D7 = PIN 2
  * A/LED+ = 5V
  * K/LED- = GND
  */
 //Include LCD library
#include <LiquidCrystal.h>
#include <SD.h>                           //include SD module library
#include <TMRpcm.h>                       //include speaker control library

#define SD_ChipSelectPin 4                //define CS pin

TMRpcm tmrpcm;                            //crete an object for speaker library
int v1, v2, v3, v4, v5;
int a1, a2, a3, a4, a5;

const int f1=A0;
const int f2=A1;
const int f3=A2;
const int f4=A3;
const int f5=A4;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 6, 5, 8, 3, 2);

void setup(){
  
  tmrpcm.speakerPin = 9;                  //define speaker pin. 
                                          //you must use pin 9 of the Arduino Uno and Nano
                                          //the library is using this pin
    // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

// set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Chutiya");
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print("Init SD crd...");
  Serial.print("Initializing SD card...");
  delay(500);

  
  if (!SD.begin(SD_ChipSelectPin)) {      //see if the card is present and can be initialized
//    lcd.clearLine(1);
    lcd.setCursor(0, 1);
    lcd.print("Init fail!");
    Serial.println("initialization failed!");
    return;                               //don't do anything more if not
  }
// lcd.clearLine(1);
  lcd.setCursor(0, 1);
  lcd.print("Init done!");
  Serial.println("initialization done."); 
  tmrpcm.setVolume(5);                    //0 to 7. Set volume level
  delay (1000);
}

void loop()
{
  delay(500);
  v1=analogRead(f1);
  v2=analogRead(f2);
  v3=analogRead(f3);
  v4=analogRead(f4);
  v5=analogRead(f5);
  
//  v1=map(v1,700,900,0,255);
 
  Serial.print("Flex 1 = ");
  Serial.println(v1);
    Serial.print("Flex 2 = ");
  Serial.println(v2);
    Serial.print("Flex 3 = ");
  Serial.println(v3);
    Serial.print("Flex 4 = ");
  Serial.println(v4);
    Serial.print("Flex 5 = ");
  Serial.println(v5);
  delay(100);
    
  if (v1<800)
  a1=0;
  else if (v1>900)
  a1=1;
  if (v2<900)
  a2=0;
  else if (v2>900)
  a2=1;
  if (v3<800)
  a3=0;
  else if (v3>850)
  a3=1;
  if (v4<820)
  a4=0;
  else if (v4>900)
  a4=1;
  if (v5<800)
  a5=0;
  else if (v5>900)
  a5=1;

  // 1 = Finger Bent
  // 0 = Finger Straight

  if (a1==0 && a2==0 && a3==0 && a4==0 && a5==0)
  {
   
  Serial.println("Playing....Stop(Change Needed)");
  tmrpcm.play("Z.wav"); //the sound file "Z" will play each time the arduino powers up, or is reset
  lcd.clear();
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  //Print a message to second line of LCD
  lcd.print("Stop.(CN)");
  delay(1000);
  Serial.println("Done Playing");
  }
  else if (a1==1 && a2==0 && a3==0 && a4==0 && a5==0)
  {
      Serial.println("Playing....A");
  tmrpcm.play("A.wav");         //the sound file "A" will play each time the arduino powers up, or is reset
    lcd.clear();
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  //Print a message to second line of LCD
  lcd.print("A.......");
  delay(1000);
  Serial.println("Done Playing");
  }
  else if (a1==1 && a2==1 && a3==0 && a4==1 && a5==1)
  {
      Serial.println("Playing....B");
  tmrpcm.play("B.wav");         //the sound file "A" will play each time the arduino powers up, or is reset
    lcd.clear();
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  //Print a message to second line of LCD
  lcd.print("B.......");
  delay(1000);
  Serial.println("Done Playing");
  }
 }
