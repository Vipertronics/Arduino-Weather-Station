// Required Librarys---------------------------------------------
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <RTClib.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <time.h>

// Pin Setup------------------------------------------------------
#define ONE_WIRE_BUS 7
#define RTC_SDA_PIN 2  // RTC SDA on D2
#define RTC_SCL_PIN 3  // RTC SCL on D3

//RTC Setup------------------------------------------------------
RTC_DS3231 RTC;

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// I2C Display Setup----------------------------------------------
LiquidCrystal_I2C lcd(0x27,20,4);

void setup() {

// RTC Setup and Init---------------------------------------------
  RTC.begin();
  //RTC.adjust(DateTime(2025, 7, 26, 12, 44, 30));

// I2C Display Setup and Init-------------------------------------
  lcd.init();
  lcd.clear();
  lcd.backlight();

  lcd.setCursor(3,0);
  lcd.print("GOODMORNING!!!");

// Temp Sensor Init------------------------------------------------
  //Serial.begin(4800);
  Wire.begin(9600);
  sensors.begin();

}
void loop() {

//RTC Output--------------------------------------------------------
  DateTime now = RTC.now();
  Serial.println();
  Serial.print("RTC now.hour        ");
  Serial.println(now.hour());
  Serial.print("RTC now.minute      ");
  Serial.println(now.minute());
  Serial.print("RTC now.second:     ");
  Serial.println(now.second());
  Serial.println();
  Serial.println();

  char dateStr[21];

  char timeStr[21];

  sprintf(dateStr, "Date: %04d:%02d:%02d", now.year(), now.month(), now.day());
  sprintf(timeStr, "Time: %02d:%02d:%02d", now.hour(), now.minute(), now.second());
  
  float tempF = sensors.getTempFByIndex(0);

  lcd.setCursor(0, 2);
  lcd.print(dateStr);

  lcd.setCursor(0, 3);
  lcd.print(timeStr);

  lcd.setCursor(0, 1);
  lcd.print("Curnt temp - ");
  lcd.print(tempF);
  lcd.print("F");

// Temp Sensor Setup-------------------------------------------------
  sensors.requestTemperatures();

  Serial.print(" - Celsius temperature: ");
  Serial.print(sensors.getTempCByIndex(0));
  Serial.print(" - Fahrenheit temperature: ");
  Serial.println(sensors.getTempFByIndex(0));
  delay(20);
}