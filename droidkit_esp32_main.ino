// Import required libraries
#include "config.h"
#include "html.h"
#include <WiFi.h>
#include <Arduino_JSON.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ESP32Servo.h>
#include <Adafruit_NeoPixel.h>
#include <Wire.h>

Adafruit_NeoPixel strip = Adafruit_NeoPixel(LEDno, PIN, NEO_GRB + NEO_KHZ800);

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

// Variables for reading messages
String message = "";
int xaxis, yaxis;
int servoState;

// Variables for movement
int finalSpeed;
int finalAngle;
Servo servo_mid;

void servoPos(int x){
    servo_mid.writeMicroseconds(x);
}

void drive(int xaxis, int yaxis){
  if (abs(xaxis)>60)
  {
    if(xaxis>60)
      xaxis = 60;
    else
      xaxis = -60;
  }
  finalAngle = (xaxis* 5);//SERVO_SIDE_RANGE); // /100;
  servoState = SERVO_MID_POS-finalAngle;
  Serial.print("x:"); // debug
  Serial.print(xaxis); // debug
  Serial.print("     y:"); // debug
  Serial.print(yaxis); // debug
  Serial.print("     servoState:"); // debug
  Serial.println(servoState); // debug
  servoPos(servoState);
  finalSpeed = abs(yaxis*255)/100;
  if(abs(yaxis) < 30){

  for(uint16_t i=0; i<LEDno; i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0, 0));
    strip.show();
  }
    // Stall moment
    analogWrite(MOTOR_1_PIN_1, 0);
    analogWrite(MOTOR_1_PIN_2, 0);
  } else if(yaxis > 0){
    fwdlight();
    analogWrite(MOTOR_1_PIN_1, finalSpeed);
    analogWrite(MOTOR_1_PIN_2, 0);
  } else {
    revlight();
    analogWrite(MOTOR_1_PIN_1, 0);
    analogWrite(MOTOR_1_PIN_2, finalSpeed);
  }
}

String getSpeedAngle(){
  JSONVar readings;
  readings["speed"] = String(yaxis > 0 ? finalSpeed : -finalSpeed);
  readings["angle"] = String(finalAngle);
  String jsonString = JSON.stringify(readings);
  return jsonString;
}

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
  AwsFrameInfo *info = (AwsFrameInfo*)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
    data[len] = 0;
    message = (char*)data;
    int idx = 0;
    int vars[3] = {0, 0};
    bool neg = 0;
    xaxis = 0; yaxis = 0;
    for(int i = 0; i < message.length(); i++){
      if(message[i] == '&'){
        if(neg) vars[idx] = -vars[idx];
        idx++; neg = 0;
      } else if(message[i] == '-') neg = 1;
      else {
        vars[idx] *= 10;
        vars[idx] += message[i]-'0';
      }
    }
    if(neg) vars[idx] = -vars[idx];
    xaxis = vars[0];
    yaxis = vars[1];
    Serial.println("xaxis, yaxis ");
    Serial.println(xaxis);
    Serial.println(yaxis);
  }
}

void eventHandler(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
  switch (type) {
    case WS_EVT_CONNECT:
      Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
      break;
    case WS_EVT_DISCONNECT:
      Serial.printf("WebSocket client #%u disconnected\n", client->id());
      break;
    case WS_EVT_DATA:
      handleWebSocketMessage(arg, data, len);
      drive(xaxis, yaxis);
      ws.textAll(getSpeedAngle());
      break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
      break;
  }
}

String processor(const String& var){
  // For HTML preprocessor
  if(var == "ANGLE"){
    return String(finalAngle);
  }
  if(var == "SPEED"){
    return String(yaxis > 0 ? finalSpeed : -finalSpeed);
  }
  return String();
}
// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< LEDno; i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / LEDno) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}
// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
void ledAlloff()
{
  for(uint16_t i=0; i<LEDno; i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0, 0));
    strip.show();
  }
}
void R2D2()
{
    spktone(random(25,250));
}
void spktone(int dly){
  for (int ii=0;ii<250;ii++)
  {
    digitalWrite(SPEAKER_PIN,HIGH);
    delayMicroseconds(dly);
    digitalWrite(SPEAKER_PIN,LOW);
    delayMicroseconds(dly);
  } 
}
void fwdlight(){
  R2D2();
  for(uint16_t i=0; i<LEDno; i++) {
    strip.setPixelColor(i, strip.Color(0, 255, 0, 0));
    strip.show();
  }
}
void revlight(){
  R2D2();
  for(uint16_t i=0; i<LEDno; i++) {
    strip.setPixelColor(i, strip.Color(255, 0, 255, 0));
    strip.show();
  }
}
void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);

  strip.begin();
  strip.setBrightness(50);
  strip.show(); // Initialize all pixels to 'off'

  pinMode(MOTOR_1_PIN_1, OUTPUT);
  pinMode(MOTOR_1_PIN_2, OUTPUT);
  pinMode(SPEAKER_PIN, OUTPUT);

  servo_mid.attach(SERVO_PIN);
  rainbowCycle(2);
  ledAlloff();
  R2D2();

   // Connect to Wi-Fi network with SSID and password
  Serial.print("Setting AP (Access Point)...");
  // Remove the password parameter if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  servo_mid.writeMicroseconds(SERVO_MID_POS);

  ws.onEvent(eventHandler);
  server.addHandler(&ws);

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });

  // Start server
  server.begin();
}

void loop() {
  ws.cleanupClients();
}
