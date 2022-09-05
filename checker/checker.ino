
// Script for testing RX TX pins using M5Stack. On selecting a protocol, and baud the M5Stack will launch Serial and send 
// "If I had 6hrs to chop down a tree I'd spend first 4 sharpening the axe" 
// Connect RX<-->TX, TX<-->RX, GND<-->GND

//============================//
//============EDIT============//
//============================//

#define BTN1 39
#define BTN2 38
#define RX 2
#define TX 4
#define SerialNo 1
#define SerialMessageStr "If I had 6hrs to chop down a tree I'd spend the first 4 sharpening the axe"

//============================//
//============================//
//============================//

#include <Wire.h>
#include <TFT_eSPI.h>
#include <HardwareSerial.h>
#include <JC_Button.h>

HardwareSerial SerialPort(SerialNo);

bool btnLoop = false;
bool protocolSelected = false;
bool baudSelected = false;
bool setupLoop = true;

int button1State = LOW;
int button2State = LOW;
int protocolMenuNo = 0;
int baudMenuNo = 0;

byte protocolArray[6] = {SERIAL_7E1, SERIAL_7O1, SERIAL_8N1, SERIAL_8N2, SERIAL_8E1, SERIAL_8O1};
String protocolArrayStr[6] = {"SERIAL_7E1", "SERIAL_7O1", "SERIAL_8N1", "SERIAL_8N2", "SERIAL_8E1", "SERIAL_8O1"};
int baudArray[16] = {600, 1200, 1800, 2400, 4800, 9600, 19200 ,28800 ,38400 , 57600, 76800, 115200, 230400, 460800, 576000, 921600};

TFT_eSPI tft = TFT_eSPI();
Button BTNA(BTN1);
Button BTNB(BTN2);

void setup()  
{  
  BTNA.begin();
  BTNB.begin();
  
  tft.init();
  tft.setRotation(1);
  tft.invertDisplay(true);
  
  printMessage(protocolArrayStr[protocolMenuNo], "", TFT_GREEN, TFT_BLACK);
  
  while(setupLoop){
    btnLoop = true;
    
    // Protocol menu selection
    while(btnLoop && protocolSelected == false){ 
      BTNA.read();
      BTNB.read();
      
      // Menu
      if (BTNA.wasReleased()) {
        protocolMenuNo = protocolMenuNo + 1;
        btnLoop = false;
        printMessage(protocolArrayStr[protocolMenuNo], "", TFT_GREEN, TFT_BLACK);
        if(protocolMenuNo > 5){
          protocolMenuNo = 0;
          printMessage(protocolArrayStr[protocolMenuNo], "", TFT_GREEN, TFT_BLACK);
        }
      }
    
      // Selection
      if (BTNB.wasReleased()) {
        btnLoop = false;
        protocolSelected = true;
        button1State = HIGH;
        button2State = HIGH;
        printMessage(String(baudArray[baudMenuNo]), "", TFT_GREEN, TFT_BLACK);
      }
    }

    // Baud menu selection
    while(btnLoop && protocolSelected == true &&  baudSelected == false){
      BTNA.read();
      BTNB.read();
      
      // Menu
      if (BTNA.wasReleased()) {
        baudMenuNo = baudMenuNo + 1;
        btnLoop = false;
        printMessage(String(baudArray[baudMenuNo]), "", TFT_GREEN, TFT_BLACK);
        if(baudMenuNo > 15){
          baudMenuNo = 0;
          printMessage(String(baudArray[baudMenuNo]), "", TFT_GREEN, TFT_BLACK);
        }
      }
    
      // Selection
      if (BTNB.wasReleased()) {
        btnLoop = false;
        baudSelected = true;
        setupLoop = false;
      }
    }
  }
  printMessage("Config:" + String(protocolArrayStr[protocolMenuNo]), "Baud:" + String(baudArray[baudMenuNo]), TFT_GREEN, TFT_BLACK);
  SerialPort.begin(baudArray[baudMenuNo], protocolArray[protocolMenuNo], TX, RX);
  delay(3000);
}

void loop()
{
  while (SerialPort.available()) {
    printMessage("Sending message", "", TFT_WHITE, TFT_BLACK);
    delay(5000);
    SerialPort.println(SerialMessageStr);
    printMessage(String(SerialPort.read()), "", TFT_WHITE, TFT_BLACK);
    delay(5000);
  }
  
  printMessage("Connection failed", "", TFT_RED, TFT_BLACK);
  delay(5000);
}

void printMessage(String text1, String text2, int ftcolor, int bgcolor)
{
  tft.fillScreen(bgcolor);
  tft.setTextColor(ftcolor, bgcolor);
  tft.setTextSize(3);
  tft.setCursor(0, 40);
  tft.println(text1);
  tft.println("");
  tft.println(text2);
}
