#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <RTClib.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 7
#define RTC_SDA_PIN 2
#define RTC_SCL_PIN 3

RTC_DS3231 RTC;

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

LiquidCrystal_I2C lcd(0x27,20,4);

void setup() 
{
  RTC.begin();
//RTC.adjust(DateTime(2025, 11, 21, 2, 52, 0));

  lcd.init();
  lcd.clear();
  lcd.backlight();

  lcd.setCursor(3,0);
  lcd.print("AWS - By Viper");

  Wire.begin(9600);
  sensors.begin();
}
void loop() 
{
  {
  DateTime now = RTC.now();

  char dateStr[21];

  char timeStr[21];

  sprintf(dateStr, "Date: %04d:%02d:%02d", now.year(), now.month(), now.day());
  sprintf(timeStr, "Time: %02d:%02d:%02d", now.hour(), now.minute(), now.second());

  lcd.setCursor(2, 2);
  lcd.print(dateStr);

  lcd.setCursor(3, 3);
  lcd.print(timeStr);

  delay(20);
  }

  {
  float tempF = sensors.getTempFByIndex(0);

  lcd.setCursor(0, 1);
  lcd.print(F("Temperature: "));
  lcd.print(tempF);
  lcd.print(F("F"));

  sensors.requestTemperatures();
  delay(50);
  }
}