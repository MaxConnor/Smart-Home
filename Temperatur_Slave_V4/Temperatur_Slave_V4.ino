
#include <Wire.h>;

int serial1;


int Qx_Room_1_Temp = 23;
int Qx_Room_2_Temp = 22;
int Qx_Room_3_Temp = 27;


void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);
  pinMode(Qx_Room_1_Temp, OUTPUT);
  pinMode(Qx_Room_2_Temp, OUTPUT);
  pinMode(Qx_Room_3_Temp, OUTPUT);
  Serial.print("__________________");
  Serial.print("Ready");
}

void loop()
{
  if (Serial1.available()) {
serial1  = Serial1.read();
    Serial.println(serial1);
  }
  


  if (serial1 == 21){
  digitalWrite(Qx_Room_1_Temp, HIGH);}
  if (serial1 == 20){
  digitalWrite(Qx_Room_1_Temp, LOW);} 
  if (serial1 == 121){
  digitalWrite(Qx_Room_2_Temp, HIGH);}
  if (serial1 == 120){
  digitalWrite(Qx_Room_2_Temp, LOW);} 
  
  if (serial1 == 221){
  digitalWrite(Qx_Room_2_Temp, HIGH);}
  if (serial1 == 220){
  digitalWrite(Qx_Room_2_Temp, LOW);} 
  }


