# ESP32 Serial Checker
For testing serial connections from devices to ESP32 microcontrollers.

Connect a device over serial and test incoming/outgoing data.

Configured for M5Stack, change <a href="https://github.com/arcbtc/SerialChecker/blob/main/checker/libraries/TFT_eSPI/User_Setup.h">tft_espi</a> library setup and the <a href="https://github.com/arcbtc/SerialChecker/blob/07a44435f14ee4e592a038760dc42695c9ece556/checker/checker.ino#L6">edit</a> section in the header for other screens/kits. 

To make device more useful Baud and Config can be set via a menu (BTNA to choose, BTNB or wait 5 secs to select)

Always:
`RX<--->TX`
`TX<--->RX`
`GND<--->GND`

Example WT32-SC01 conected to M5Stack. The message being displayed is evidence the serial connection is working.


<img src="https://user-images.githubusercontent.com/33088785/188520980-5dffa9c4-d3a3-4717-89b2-c9fc5efc1e71.png" style="width:300px;">
