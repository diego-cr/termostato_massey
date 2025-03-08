#include <OneWire.h>                
#include <DallasTemperature.h>
 
OneWire tsensor(A0);
DallasTemperature sensors(&tsensor);

bool cold = 0; // need cool?
bool debug = 1; // debug?

int potvalue[6] = {120, 150, 190, 250, 600, 1000}; // array potenciometer values
int coldtemp[6] = {5, 4, 3, 2, 1, 0};              // array temp values


void setup() {
  pinMode(A1, INPUT);
  pinMode(A5, INPUT);
  pinMode(7, OUTPUT);  
  digitalWrite(7, LOW); // stop cooling
  if (debug == 1){
    Serial.begin(9600);
    sensors.begin();
  }
}
 
void loop() {

sensors.requestTemperatures();
float temp= sensors.getTempCByIndex(0);
int pot = analogRead(A5);

if (debug == 1){
  Serial.println("----");
  Serial.print("Potenciometer: ");
  Serial.println(pot);
  Serial.print("Temperature: ");
  Serial.println(temp);
  Serial.print("cold: ");
  Serial.println(cold);
}

for (int i = 0; i < 6; i++) {
  if (debug == 1){
    Serial.print(i);
    Serial.print(" potvalue: ");
    Serial.print(potvalue[i]);
    Serial.print(" coldtemp: ");
    Serial.println(coldtemp[i]); 
    Serial.println("----");
  }
  if ((temp > coldtemp[i]) && (pot > potvalue[i])){  // test if need more cool
    cold = 1;
    break;  // if need more cool stop!
  }
  else{
    cold = 0;
  } 
}

if (cold == 1)  // start cooling
  digitalWrite(7, HIGH);
else  // stop cooling
  digitalWrite(7, LOW);

delay(2000);

}