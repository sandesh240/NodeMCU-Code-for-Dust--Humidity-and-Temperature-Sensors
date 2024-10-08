#include <dummy.h>

// Combined Code For Measurement Of Temprature, Humidity And Dust Density

#include "DHT.h"
#define DHTTYPE DHT11

DHT dht(5, DHTTYPE);
int measurePin = 0; //Connect dust sensor to Arduino A0 pin
int ledPower = 4;   //Connect 3 led driver pins of dust sensor to Arduino D2

int samplingTime = 280;
int deltaTime = 40;
int sleepTime = 9680;

float voMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0;

void setup(){
  dht.begin();
  Serial.begin(9600);
  pinMode(ledPower,OUTPUT);
  Serial.println("Humidity and Temperature\n\n");
  delay(700);
}

void loop(){

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  Serial.print("Current humidity = ");
  Serial.print(h);
  Serial.print(" % ");
  
  Serial.print("temperature = ");
  Serial.print(t);
  Serial.print(" C and   ");

  
  digitalWrite(ledPower,LOW); // power on the LED
  delayMicroseconds(samplingTime);

  voMeasured = analogRead(measurePin); // read the dust value

  delayMicroseconds(deltaTime);
  digitalWrite(ledPower,HIGH); // turn the LED off
  delayMicroseconds(sleepTime);

  // 0 - 5V mapped to 0 - 1023 integer values
  // recover voltage
  calcVoltage = voMeasured * (5.0 / 1024.0);

  // linear eqaution taken from http://www.howmuchsnow.com/arduino/airquality/
  // Chris Nafis (c) 2012
  dustDensity = 170 * calcVoltage - 0.1;

  Serial.print("Current Dust Density Is: ");
  Serial.print(dustDensity); // unit: ug/m3
  Serial.print("ug/m3 \n");
  delay(5000);
}