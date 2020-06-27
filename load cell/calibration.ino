#include "HX711.h"

#define DOUT 8
#define CLK 7

HX711 scale(DOUT, CLK);

float calibration_factor = 8875; //-7050 worked for my 440lb max scale setup

void setup() {
Serial.begin(38400);
Serial.println("HX711 calibration sketch");
Serial.println("Remove all weight from scale");
Serial.println("After readings begin, place known weight on scale");
Serial.println("Press + or a to increase calibration factor");
Serial.println("Press - or z to decrease calibration factor");

scale.set_scale();
scale.tare(); //Reset the scale to 0

long zero_factor = scale.read_average(); //Get a baseline reading
Serial.print("Zero factor: "); //This can be used to remove the need to tare the scale. Useful in permanent scale projects.
Serial.println(zero_factor);
}

void loop() {

scale.set_scale(calibration_factor); //Adjust to this calibration factor

Serial.print("Reading: ");
Serial.print(scale.get_units()*0.453592, 3);
Serial.print(" kg"); //Change this to kg and re-adjust the calibration factor if you follow SI units like a sane person
Serial.print(" calibration_factor: ");
Serial.print(calibration_factor);
Serial.println();
delay(1000);

if(Serial.available())
{
char temp = Serial.read();
if(temp == '+' || temp == 'a')
calibration_factor += 10;
else if(temp == '-' || temp == 'z')
calibration_factor -= 10;
}
}
