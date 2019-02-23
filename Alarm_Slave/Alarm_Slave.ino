#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 53
#define RST_PIN 5
MFRC522 mfrc522(SS_PIN, RST_PIN);

bool Reed1;
bool Reed2;
bool Reed3;

bool Alarmed = 0;

void setup()
{
    pinMode (9, INPUT);
  pinMode (8, INPUT);
  pinMode (10, INPUT);
Serial.begin(9600);
SPI.begin();
mfrc522.PCD_Init();
  pinMode (2, OUTPUT);

  Serial.println("Ready");
}

void loop()
{
 Reed1= digitalRead (8);
 Reed2= digitalRead (9);
 Reed3= digitalRead (10);
if ( ! mfrc522.PICC_IsNewCardPresent())
{
return;
}

if ( ! mfrc522.PICC_ReadCardSerial())
{
return;
}

long code=0;

for (byte i = 0; i < mfrc522.uid.size; i++)
{
code=((code+mfrc522.uid.uidByte[i])*10);
}


if (code==1421070 and Alarmed == 0) // Wenn der Zahlencode 1031720 lautet...

{

Serial.println("System is armed");
Alarmed = 1;
code = 0;
delay (1000);

} // Programmabschnitt schließen

if (code==1421070 and Alarmed == 1) // Wenn der Zahlencode 1031720 lautet...

{

Serial.println("System is disarmed");
Alarmed = 0;
code = 0;
delay (1000);
}

 

    if  (Reed1 == HIGH or Reed2 == HIGH or Reed3 == HIGH )
  {
    Serial.println("ALARM");
  }  
}
