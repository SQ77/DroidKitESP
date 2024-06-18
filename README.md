[DroidKitESP assembly manual.pdf](https://github.com/tinkertanker/DroidKitESP/files/15198589/DroidKitESP.assembly.manual.pdf)

Once you had assembled, you could start using the DroidKit.
1. Power the DroidKit with your power bank. (you may refer to page 15 of the assembly manual.
2. From your mobile phone or tablet or laptop, looke for Wifi name (ESP32-Droid). Password is (DroidKitESP)
3. From the web browser (eg Chrome), go to 192.168.4.1
(Note: Please tune of your mobile data if your are using Chrome browser from mobile phone.)

If you are a maker and want to tinker DroidKit, you could modify the firmware of DroidKit as below. Please let us know if you had done so.

May the froce be with you!

### Setup
1. Install Arduino
2. Install ESP32 Boards
https://github.com/espressif/arduino-esp32 (by espressif, not arduino!)
3. Install libraries
- [Arduino_JSON](https://github.com/arduino-libraries/Arduino_JSON) by Arduino
- [AsyncTCP](https://github.com/dvarrel/AsyncTCP) by dvarrel, forked from me-no-dev
- [ESPAsyncWebServer](https://github.com/lacamera/ESPAsyncWebServer) by lacamera 
- [ESP32Servo](https://github.com/madhephaestus/ESP32Servo) by Kevin Harrington,John K. Bennett
- [Adafruit_NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel)by Adafruit
5. Choose the correct board and COM PORT
- The board we are using is the DOIT ESP32 DEVKIT V1
5. Config your network SSID and Password, and copy `config.h` to the `robot-webserver` folder.
6. Run, and go to whatever IP is printed to control the bot. Your device must be connected to the same wifi network.
7. Enjoy!
