#ifndef Config_h
#define Config_h

#define MOTOR_1_PIN_1    27
#define MOTOR_1_PIN_2    26
#define SERVO_PIN        25
#define SERVO_MID_POS    1300
#define SERVO_SIDE_RANGE 60

#define SPEAKER_PIN      16

// NeoPixel configuration
#define PIN 12  // NeoPixel data pin
#define LEDno 10  // Number of NeoPixels

// Replace with your network credentials
extern const char* ssid = "ESP32-Droid";
extern const char* password = "DroidKitESP";

#endif