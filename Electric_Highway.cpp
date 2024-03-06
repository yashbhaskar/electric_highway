#define BLYNK_TEMPLATE_ID ""
#define BLYNK_TEMPLATE_NAME ""
#define BLYNK_AUTH_TOKEN "" // Replace with your Blynk auth token
#define EXPECTED_V_OUT 12.5      // The intented voltage, 12 V

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SoftwareSerial.h>
#define BLYNK_PRINT Serial
#include <Servo.h>   

const int BatteryPin = A0;
#define ENA D0
#define IN1 D1
#define IN2 D2
#define IN3 D3
#define IN4 D4
#define ENB D5

int Speed = 255;
int adc_read = 0;
float battery_voltage = 0;
int percent = 0;

Servo servo;

char auth[] = ""; // Replace with your Blynk auth token
char ssid[] = "ElectricHighway"; // Replace with your WiFi name
char pass[] = "1234567890"; // Replace with your WiFi password

BlynkTimer timer;

BLYNK_WRITE(V0) {
  int forward = param.asInt();
  if (forward == 1) {
    carforward();
  } else {
    carStop();
  }
}

BLYNK_WRITE(V1) {
  int backward = param.asInt();
  if (backward == 1) {
    carbackward();
  } else {
    carStop();
  }
}

BLYNK_WRITE(V2) {
  int right = param.asInt();
  if (right == 1) {
    carturnright();
  } else {
    carStop();
  }
}

BLYNK_WRITE(V3) {
  int left = param.asInt();
  if (left == 1) {
    carturnleft();
  } else {
    carStop();
  }
}

BLYNK_WRITE(V4) {
  Speed = param.asInt();
}

BLYNK_WRITE(V6) {
  int relayState = param.asInt();
  digitalWrite(15, relayState);
}

BLYNK_WRITE(V13) {
  int servoAngle = param.asInt();
  servo.write(servoAngle);
}

void setup() {
  Serial.begin(9600);
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(15, OUTPUT);

  digitalWrite(13, HIGH);
  digitalWrite(15, HIGH);

  servo.attach(12);
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  timer.setInterval(1000L, updateBattery);
}

void loop() {
  Blynk.run();
  timer.run();
  smartcar();
}

void updateBattery() {
  adc_read = analogRead(BatteryPin);
  battery_voltage = (adc_read * (4.3 / 1023) * (6)) / 2;
  percent = battery_voltage * 100 / EXPECTED_V_OUT;
  Blynk.virtualWrite(V15, percent);
}

void smartcar() {
  // Implement your smartcar logic here
}

void carforward() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void carbackward() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void carturnleft() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void carturnright() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void carStop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
