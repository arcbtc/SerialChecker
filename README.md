# ESP32 Serial Checker
For testing serial connections from devices to ESP32 microcontrollers.

Connect a device over serial and test incoming/outgoing data.

Configured for M5Stack, change <a href="https://github.com/arcbtc/SerialChecker/blob/main/checker/libraries/TFT_eSPI/User_Setup.h">tft_espi</a> library setup and BTN1/BTN2 for other screens/kits. 

Always:
`RX<--->TX`
`TX<--->RX`
`GND<--->GND`
