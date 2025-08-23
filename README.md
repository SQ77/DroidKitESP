[DroidKitESP assembly manual.pdf](https://github.com/tinkertanker/DroidKitESP/files/15198589/DroidKitESP.assembly.manual.pdf)

Once you have assembled the bot, you can follow the steps below to control it.
1. Power the DroidKit with your power bank. (you may refer to page 15 of the assembly manual)
2. From your mobile phone or tablet or laptop, look for Wifi name (ESP32-Droid). Password is (DroidKitESP)
3. From the web browser (e.g. Chrome), go to 192.168.4.1
(Note: Please turn off your mobile data if you are using Chrome browser from mobile phone.)
4. You can now control the bot using the joystick on the screen of your device.

If you are a maker and want to tinker DroidKit, you can modify the firmware of DroidKit by following the steps below. Please let us know if you have done so.

May the force be with you!

### Setup to Modify Firmware
1. Install Arduino
2. Install [ESP32 Boards](https://github.com/espressif/arduino-esp32) (by espressif, not arduino!)
3. Install the following libraries:
- [Arduino_JSON](https://github.com/arduino-libraries/Arduino_JSON) by Arduino
- [AsyncTCP](https://github.com/dvarrel/AsyncTCP) by dvarrel, forked from me-no-dev
- [ESPAsyncWebServer](https://github.com/lacamera/ESPAsyncWebServer) by lacamera 
- [ESP32Servo](https://github.com/madhephaestus/ESP32Servo) by Kevin Harrington,John K. Bennett
- [Adafruit_NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel) by Adafruit
4. Choose the correct board and COM PORT
- The board we are using is the DOIT ESP32 DEVKIT V1
5. Config your network SSID and Password, and copy `config.h` to the `robot-webserver` folder.
6. Run, and go to whatever IP is printed to control the bot. Your device must be connected to the same wifi network.
7. Enjoy!
