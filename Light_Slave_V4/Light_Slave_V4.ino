
#include <Wire.h>;

int serial1;


int Qx_Room_1_Lamp = 22;
int Qx_Room_2_Lamp = 23;
int Qx_Room_3_Lamp = 24;


void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);
  pinMode(Qx_Room_1_Lamp, OUTPUT);
  pinMode(Qx_Room_2_Lamp, OUTPUT);
  pinMode(Qx_Room_3_Lamp, OUTPUT);
  Serial.print("__________________");
  Serial.print("Ready");
}

void loop()
{
  if (Serial1.available()) {
serial1  = Serial1.read();
    Serial.println(serial1);
  }
  



if (serial1 == 11){
  digitalWrite(Qx_Room_1_Lamp, HIGH);}
if (serial1 == 10 == LOW){
  digitalWrite(Qx_Room_1_Lamp, LOW);} 

if (serial1 == 111){
  digitalWrite(Qx_Room_2_Lamp, HIGH);}

if (serial1 == 110){
  digitalWrite(Qx_Room_2_Lamp, LOW);} 

if (serial1 == 211){
  digitalWrite(Qx_Room_3_Lamp, HIGH);}

if (serial1 == 210){
  digitalWrite(Qx_Room_3_Lamp, LOW);} 

}


