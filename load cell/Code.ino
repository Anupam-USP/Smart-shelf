#include "HX711.h"
#include <ESP8266WiFi.h>;
#include <WiFiClient.h>;
#define BLYNK_PRINT Serial;
#include <Blynk.h>;
#include <BlynkSimpleEsp8266.h>;
#include <ThingSpeak.h>;
#include <Wire.h>
//#include "LiquidCrystal_I2C.h"

//LiquidCrystal_I2C lcd(0x27, 16, 2);
WiFiClient client;
const char* ssid = "Trademark"; 
const char* password = "Itsmine12"; 
unsigned long myChannelNumber = 1036823;            
const char * myWriteAPIKey = "2326ZYZTN3YQ4GJI";   
HX711 scale(D5, D6);
float calibration_factor = 888; // this calibration factor is adjusted according to my load cell
int units;

void setup() {
Serial.begin(9600);
Blynk.begin(auth, ssid, pass);
Wire.begin(D2, D1);
//  lcd.begin();
//  lcd.print("IOT PROJECT");
//  lcd.setCursor(0,1);
//  lcd.print("IIIT NAYA RAIPUR");
delay(2000);
//  lcd.clear();
//  lcd.print("Hello to Blynk");
//  lcd.setCursor(0,1);
//  lcd.print("And Thingspeak");
WiFi.begin(ssid, password);
ThingSpeak.begin(client);
delay(3000);
Serial.println("Remove all weight from scale");
scale.set_scale();
scale.tare();  //Reset the scale to 0
long zero_factor = scale.read_average(); //Get a baseline reading
Serial.print("Zero factor: "); //This can be used to remove the need to tear the scale. Useful in permanent scale projects.
Serial.println(zero_factor); }

void loop() {
Blynk.run();
scale.set_scale(calibration_factor); //Adjust to this calibration factor
Serial.print("Reading: ");
//  lcd.clear();
units = scale.get_units(), 10;
if (units < 0){
units = 0; }
if (units == 0){
//       lcd.print("Weight :");
//       lcd.print(units/1000);
//       lcd.print("  kg");
ThingSpeak.writeField(myChannelNumber, 1,units, myWriteAPIKey); //Update in ThingSpeak 
Serial.print(units/1000);
Serial.print(" kilograms"); 
Blynk.virtualWrite(V3, weight);
Serial.print(" calibration_factor: ");
Serial.print(calibration_factor);
Serial.println();
delay(15000); } 
if (units > 0){
//       lcd.print("Weight :");
//       lcd.print(units/1000);
//       lcd.print("  kg");
ThingSpeak.writeField(myChannelNumber, 1,units, myWriteAPIKey); //Update in ThingSpeak 
Serial.print(units/1000);
Serial.print(" kilograms"); 
Serial.print(" calibration_factor: ");
Serial.print(calibration_factor);
Serial.println();
delay(15000); } }
