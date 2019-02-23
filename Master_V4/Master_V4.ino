//Include
#include <Wire.h>;
#include <MOVIShield.h>

//Movi
#if defined(ARDUINO_ARCH_AVR) || defined(ARDUINO_ARCH_PIC32)
#include <SoftwareSerial.h>
#endif

#include <avr/power.h>

MOVI recognizer(true);

int Simulation = 0;
//Timer
unsigned long lastMillis1;
int seconds = 0;
int hours2 = 0;
int hours =0;
int seconds2=0;

//Comm
int serial1 = 0;
int serial2 = 0;
int serial3 = 0;

//Temp
int Iw_Room_1_Temp = A13;
int Iw_Room_2_Temp = A14;
int Iw_Room_3_Temp = A15;

int Mx_Room_1_heater;
int Mx_Room_2_heater;
int Mx_Room_3_heater;



int Mw_Room_1_Temp_Unscale;
int Mw_Room_1_Temp_Scale = 0;
int Mw_Room_2_Temp_Unscale;
int Mw_Room_2_Temp_Scale = 0;
int Mw_Room_3_Temp_Unscale;
int Mw_Room_3_Temp_Scale = 0;


//Light
int Iw_Room_1_Light = A10;
int Iw_Room_2_Light = A11;
int Iw_Room_3_Light = A12;


int Mw_Room_1_Light_Unscale = 0;
int Mw_Room_1_Light_Scale = 0;
int Mw_Room_2_Light_Unscale;
int Mw_Room_2_Light_Scale = 0;
int Mw_Room_3_Light_Unscale;
int Mw_Room_3_Light_Scale = 0;

int Ix_Room_1_Light =22;
int Ix_Room_2_Light =24;
int Ix_Room_3_Light =26;

int Mx_Room_1_Light=0;
int Mx_Room_2_Light=0;
int Mx_Room_3_Light=0;

int Mx_Room_1_Lamp = 0;
int Mx_Room_2_Lamp = 0;
int Mx_Room_3_Lamp = 0;

int Mx_Room_1_Blinders = 0;
int Mx_Room_2_Blinders = 0;
int Mx_Room_3_Blinders = 0;


//Wheater
int Mw_Outdoor_UV = 0;
int Mw_Outdoor_Temp_Scale = 0;
int Mw_Outdoor_Humitidy = 0;
int Mw_Outdoor_Windspeed= 0;
int Mw_Outdoor_Light_Scale =0;


//Movi
String value = "";

int Bedroom = 0;
int Kitchen = 0;
int Commonroom = 0;

int Armed = 0;

char Search = 0;
char Found = 0;

int Joke =0;


void setup(){
  
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);
  Serial3.begin(9600);
  Serial.println("ready");


  { //Movi

    String value = "";
    recognizer.init();
    recognizer.setVoiceGender(FEMALE_VOICE);
    recognizer.callSign("Tess");
    recognizer.addSentence("Bedroom"); //1
    recognizer.addSentence("Kitchen");
    recognizer.addSentence("Commonroom");
    recognizer.addSentence("How warm is it");
    recognizer.addSentence("How bright is it");
    recognizer.addSentence("No");
    recognizer.addSentence("Yes");
    recognizer.addSentence("Stop");
    recognizer.addSentence("Turn on the Light");
    recognizer.addSentence("Turn off the Light");//10
    recognizer.addSentence("Blinders Down");
    recognizer.addSentence("Blinders Up");
    recognizer.addSentence("What is the Windspeed");
    recognizer.addSentence("What is the UV-Rating");
    recognizer.addSentence("What is the Humidity");  //15
    recognizer.addSentence("Play Music");
    recognizer.addSentence("Turn on the Lamp");
    recognizer.addSentence("Turn off the Lamp");
    recognizer.addSentence("What is the Temperature");    
    recognizer.addSentence("Turn up the Heater");//20
    recognizer.addSentence("Turn down the Heater");
    recognizer.addSentence("Turn on the Sim Mode");
    recognizer.addSentence("Turn off the Sim Mode");//23
    recognizer.addSentence("Who make the Introduction");


    recognizer.train();
  }
  { //Temp
    pinMode (Iw_Room_1_Temp, INPUT);
    pinMode (Iw_Room_2_Temp, INPUT);
    pinMode (Iw_Room_3_Temp, INPUT);
  }
  { //Light
    pinMode (Iw_Room_1_Light, INPUT);
    pinMode (Iw_Room_2_Light, INPUT);
    pinMode (Iw_Room_3_Light, INPUT);

  }

}

void loop()
{
  {//Timer 
  if (Simulation == 1){
  if ((millis() - lastMillis1) >= 1000) {
    seconds2= seconds2 +1;
    seconds = seconds + 1;
    lastMillis1 = millis();
  if (seconds2 == 240){
    seconds2 = 0;
  }
  
  }
    if (hours == 24){
      hours = 0;
     }  
    if (seconds == 10)
    {
    hours = hours +1;
    seconds = 0;
    }
    if (hours2 != hours){
    Serial.print(hours);
    Serial.println(":00");
    hours2= hours;
    }
  }

} 
    signed int res = recognizer.poll(); 
    if (res == 24){
      recognizer.say("That would be me. Hello Miss Huber, Hello mister Banziger and Hello class.");
      delay(100);
      recognizer.say("Welcome to our Peresentation of our paper of Our Challange, Our Smart Home");
    }

    if (res == 22) {                   
      recognizer.say("Simulation Mode On");
      Simulation= 1;
    }
    if (res == 23) {                   
    recognizer.say("Simulation Mode Off");
    Simulation= 0;
    }
      
  if (Serial2.available()) {
serial2  = Serial2.read();
    Serial.println(serial2);
  }
    if (Serial3.available()) {
serial3  = Serial3.read();
    Serial.println(serial3);
  }
if (Simulation == 0){//Input
  int32_t Mw_House_Alarm_Trans;

  int32_t Mw_Outdoor_UV;
  int32_t Mw_Weather_Station_Humidity_Trans;
  int32_t Mw_Weather_Station_Temp_Trans;


  byte Wheater_Station_UV_a, Wheater_Station_UV_b, Wheater_Station_UV_c, Wheater_Station_UV_d;
  byte Weather_Station_Humidity_a, Weather_Station_Humidity_b, Weather_Station_Humidity_c, Weather_Station_Humidity_d;
  byte Weather_Station_Temp_a, Weather_Station_Temp_b, Weather_Station_Temp_c, Weather_Station_Temp_d;

  byte House_Alarm_a, House_Alarm_b, House_Alarm_c, House_Alarm_d;

  { //Temp
    Mw_Room_1_Temp_Unscale = analogRead(Iw_Room_1_Temp);
    Mw_Room_1_Temp_Scale = map(Mw_Room_1_Temp_Unscale, 0, 410, -50, 150);
    Mw_Room_2_Temp_Unscale = analogRead(Iw_Room_2_Temp);
    Mw_Room_2_Temp_Scale = map(Mw_Room_2_Temp_Unscale, 0, 410, -50, 150);
    Mw_Room_3_Temp_Unscale = analogRead(Iw_Room_3_Temp);
    Mw_Room_3_Temp_Scale = map(Mw_Room_3_Temp_Unscale, 0, 410, -50, 150);



  }

  { //Light
    Mw_Room_1_Light_Unscale = analogRead(Iw_Room_1_Light);
    Mw_Room_1_Light_Scale = map(Mw_Room_1_Light_Unscale, 0, 1023, 0, 600);
    Mw_Room_2_Light_Unscale = analogRead(Iw_Room_2_Light);
    Mw_Room_2_Light_Scale = map(Mw_Room_2_Light_Unscale, 0, 1023, 0, 600);
    Mw_Room_3_Light_Unscale = analogRead(Iw_Room_3_Light);
    Mw_Room_3_Light_Scale = map(Mw_Room_3_Light_Unscale, 0, 1023, 0, 600);

    Mx_Room_1_Light = digitalRead(Ix_Room_1_Light);
    Mx_Room_2_Light = digitalRead(Ix_Room_2_Light);
    Mx_Room_3_Light = digitalRead(Ix_Room_3_Light);




   }

  { //Weather

  }

  { //Alarmed

  }
}
if (Simulation ==1){

Mw_Room_1_Temp_Scale = 20;
Mw_Room_2_Temp_Scale = 20;
Mw_Room_3_Temp_Scale = 20;
Mw_Room_1_Light_Scale = 20;
Mw_Room_2_Light_Scale = 20;
Mw_Room_3_Light_Scale = 20;

if (seconds2 == 0){
Mw_Outdoor_UV = 3;//00:00
Mw_Outdoor_Temp_Scale = 15;  
Mw_Outdoor_Humitidy = 20;
Mw_Outdoor_Windspeed= 0;
Mw_Outdoor_Light_Scale =0;
Serial.println("00:00");
}
if (seconds2 == 60){
Mw_Outdoor_Light_Scale =40;
Serial.println("05:00");
}
if(seconds2 == 70){
Mw_Outdoor_Temp_Scale = 20;
Mw_Outdoor_Light_Scale = 80; 
Serial.println("06:00");
}
if(seconds2 == 80){
  Mw_Outdoor_Light_Scale = 90;
  Serial.println("07:00");
}
if (seconds2 == 90){
  Mw_Outdoor_Temp_Scale = 25;
  Mw_Outdoor_Light_Scale = 100;
  Serial.println("08:00");
}
if (seconds2 == 110){
  Mw_Outdoor_Temp_Scale = 30;
  Mw_Outdoor_Humitidy = 30;
  Serial.println("10:00");
}
if (seconds2 ==120){
  Mw_Outdoor_Windspeed = 10;
  Serial.println("11:00");
}
if (seconds2 == 130){
  Mw_Outdoor_Temp_Scale = 35;
  Mw_Outdoor_Windspeed = 20;
  Serial.println("12:00");
}
if (seconds2 == 140){
  Mw_Outdoor_Temp_Scale = 30;
  Mw_Outdoor_Windspeed = 40;
  Mw_Outdoor_Light_Scale = 30;
  Serial.println("13:00");
}
if (seconds2 == 160){
  Mw_Outdoor_Temp_Scale = 25;
  Serial.println("15:00");
}
if (seconds2 == 180){
  Mw_Outdoor_Temp_Scale = 20;
  Serial.println("17:00");
}
if (seconds2 == 190){
  Mw_Outdoor_Windspeed = 30;
  Mw_Outdoor_Light_Scale = 20;
  Serial.println("18:00");
}
if (seconds2 == 210){
  Mw_Outdoor_Humitidy = 20;
  Mw_Outdoor_Windspeed = 20;
  Mw_Outdoor_Light_Scale = 0;
  Serial.println("20:00");
}
if (seconds2 == 220){
  Mw_Outdoor_Temp_Scale = 15;
  Mw_Outdoor_Windspeed = 10;
  Serial.println("21:00");
}
if (seconds2 == 230){
  Mw_Outdoor_Windspeed = 0;
  Serial.println("22:00");
}
}
{//processing
  if (Mx_Room_1_Light == HIGH and Mx_Room_1_Lamp == LOW){
  Mx_Room_1_Lamp = HIGH;
  serial1 = 11;
  Serial1.write(serial1);
  delay(100);  
}
 else if (Mx_Room_1_Light == HIGH and Mx_Room_1_Lamp == HIGH){
  Mx_Room_1_Lamp = LOW;
  serial1 = 10;
  Serial1.write(serial1);
  delay(100);     
}
if (Mx_Room_2_Light == HIGH and Mx_Room_2_Lamp == LOW){
  serial1 = 111;
  Serial1.write(serial1);
  delay(100);  
}
 else if (Mx_Room_2_Light == HIGH and Mx_Room_2_Lamp == HIGH){
  Mx_Room_2_Lamp = LOW; 
  serial1 = 110;
  Serial1.write(serial1); 
  delay(100);
}
if (Mx_Room_3_Light == HIGH and Mx_Room_3_Lamp == LOW){
  Mx_Room_3_Lamp = HIGH;
  serial1 = 211;
  Serial1.write(serial1);
  delay(100);  
}
 else if (Mx_Room_3_Light == HIGH and Mx_Room_3_Lamp == HIGH){
  Mx_Room_3_Lamp = LOW;
  serial1 = 210;
  Serial1.write(serial1);
  delay(100);   
}
}
  

  { //Movi


{//Room
    if (res == 1) {                   // Bedroom

      recognizer.ask("What can i do for You, in the bedroom");
      Bedroom = 1;
      Kitchen = 0;
      Commonroom = 0;
    }
    else if (res == 2) {                  // Kitchen

      recognizer.ask("What can i do for You, in the Kitchen");
      Bedroom = 0;
      Kitchen = 1;
      Commonroom = 0;
    }
    else if (res == 3) {                  // Commonroom
      recognizer.ask("What can i do for You, in the Commonroom");
      Bedroom = 0;
      Kitchen = 0;
      Commonroom = 1;
    }
  }
  
{//Abort
    if (res == 7) {
      recognizer.ask ("what?");
    }
    else if (res == 6 or res == 8) {
      recognizer.say("Okey, bye");
      Bedroom = 0;
      Kitchen = 0;
      Commonroom = 0;
    }
}
    if (Bedroom == 1)
    {
      if (res == 4 or res == 19) {
        value = Mw_Room_1_Temp_Scale;
        Serial.println (Mw_Room_1_Temp_Scale);
        recognizer.say("It is" + value + "Degres warm");
        value = "";
        recognizer.ask("anything else?");

      }
      else if (res == 5) {
        value = Mw_Room_1_Light_Scale;
        Serial.println (Mw_Room_1_Light_Scale);
        recognizer.say("It has a brightness of" + value + "precent");
        value = "";
        recognizer.ask("anything else?");
      }
      else if (res == 9 or res == 17) {
        if (Mw_Room_1_Light_Scale < 30) {
        recognizer.say("Lights are goin on");
        Mx_Room_1_Lamp = HIGH;
        serial1 = 11;
        Serial1.write(serial1); 
        }
        else if (Mw_Room_1_Light_Scale >= 30) {
          recognizer.say("it is to bright");
        }
        else if (Mx_Room_1_Blinders == 1) {
          recognizer.say("Blinder are going up");
          Serial1.write(130);
        }
      }
      else if (res == 10 or res == 18) {
        if (Mx_Room_1_Lamp == 1)
        {
          recognizer.say("Lights are going off");
        Mx_Room_1_Lamp = LOW;
        serial1 = 10;
        Serial1.write(serial1); 
        }
      }
      else if (res == 11) {
        if (Mx_Room_1_Blinders == 0) {
          recognizer.say("Blinders are going down");
          Serial1.write(131);
          Mx_Room_1_Blinders = 1;
        }
        else {
          recognizer.say ("blinders are allready Down");
        }
      }
      else if (res == 12) {
        if (Mx_Room_1_Blinders == 1) {
          recognizer.say("Blinders are going up");
          Serial1.write(130);
          Mx_Room_1_Blinders = 0;
        }
        else {
          recognizer.say ("blinders are allready Up");
        }
      }
      if  (res == 20){
        if (Mw_Room_1_Temp_Scale <= 20){
        serial1 = 21;
        Serial1.write(serial1);
        recognizer.say ("Heaters are going on");           
        }
        if (Mw_Room_1_Temp_Scale > 20){
        recognizer.say ("It is to warm");
        }
      }
      if (res == 21){
        serial1 = 20;
        Serial1.write(serial1);
        recognizer.say ("Heaters are off");   
      }
    }
    else if (Kitchen == 1)
    {
      if (res == 4 or res == 19) {
        value = Mw_Room_1_Temp_Scale;
        recognizer.say("It is" + value + "Degres warm");
        value = "";
        recognizer.ask("anything else?");

      }
      else if (res == 5) {
        value = Mw_Room_1_Light_Scale;
        recognizer.say("It has a brightness of" + value + "precent");
        value = "";
        recognizer.ask("anything else?");
      }
      else if (res == 9 or res == 17) {
        if (Mw_Room_2_Light_Scale < 90) {
          recognizer.say("Lights are goin on");
        Mx_Room_2_Lamp = HIGH;
        serial1 = 111;
        Serial1.write(serial1); 
        }
        else if (Mw_Room_2_Light_Scale >= 30) {
          recognizer.say("it is to bright");
        }
        else if (Mx_Room_2_Blinders == 1) {
          recognizer.say("Blinder are going up");
          Serial1.write(230);
        }
      }
      else if (res == 10 or res == 18) {
        if (Mx_Room_2_Lamp == 1)
        {
          recognizer.say("Lights are goin off");
        Mx_Room_2_Lamp = LOW;
        serial1 = 110;
        Serial1.write(serial1); 
        }
      }
      else if (res == 11) {
        if (Mx_Room_2_Blinders == 0) {
          recognizer.say("Blinders are going down");
          Serial1.write(231);
          Mx_Room_2_Blinders = 1;
        }
        else {
          recognizer.say ("blinders are allready Down");
        }
      }
      else if (res == 12) {
        if (Mx_Room_2_Blinders == 1) {
          recognizer.say("Blinders are going up");
          Serial1.write(230);
          Mx_Room_2_Blinders = 0;
        }
        else {
          recognizer.say ("blinders are allready Up");
        }
      }
            if  (res == 20){
        if (Mw_Room_2_Temp_Scale <= 20){
        serial1 = 121;
        Serial1.write(serial1);
        recognizer.say ("Heaters are going on");           
        }
        if (Mw_Room_2_Temp_Scale > 20){
        recognizer.say ("It is to warm");
        }
      }
      if (res == 21){
        serial1 = 120;
        Serial1.write(serial1);
        recognizer.say ("Heaters are off");   
      }
    }
    else if (Commonroom == 1)
    {
      if (res == 4 or res == 19) {
        value = Mw_Room_3_Temp_Scale;
        recognizer.say("It is" + value + "Degres warm");
        value = "";
        recognizer.ask("anything else?");

      }
      else if (res == 5) {
        value = Mw_Room_3_Light_Scale;
        recognizer.say("It has a brightness of" + value + "precent");
        value = "";
        recognizer.ask("anything else?");
      }
      else if (res == 9 or res == 17) {
        if (Mw_Room_3_Light_Scale < 30 ) {
          recognizer.say("Lights are goin on");
        Mx_Room_3_Lamp = HIGH;
        serial1 = 211;
        Serial1.write(serial1); 
        }
        else if (Mw_Room_3_Light_Scale >= 30) {
          recognizer.say("it is to bright");
        }
        else if (Mx_Room_3_Blinders == 1) {
          recognizer.say("Blinder are going up");
          Serial1.write(330);
        }
      }
      else if (res == 10 or res == 18) {
        if (Mx_Room_3_Lamp == 1)
        {
          recognizer.say("Lights are goin off");
        Mx_Room_3_Lamp = LOW;
        serial1 = 210;
        Serial1.write(serial1); 
        }
      }
      else if (res == 11) {
        if (Mx_Room_3_Blinders == 0) {
          recognizer.say("Blinders are going down");
          Serial1.write(331);
          Mx_Room_3_Blinders = 1;
        }
        else {
          recognizer.say ("blinders are allready Down");
        }
      }
      else if (res == 12) {
        if (Mx_Room_3_Blinders == 1) {
          recognizer.say("Blinders are going up");
          Serial1.write(330);
          Mx_Room_3_Blinders = 0;
        }
        else {
          recognizer.say ("blinders are allready Up");
        }
      }
      if  (res == 20){
        if (Mw_Room_3_Temp_Scale <= 20){
        serial1 = 221;
        Serial1.write(serial1);
        recognizer.say ("Heaters are going on");           
        }
        if (Mw_Room_1_Temp_Scale > 20){
        recognizer.say ("It is to warm");
        }
      }
      if (res == 21){
        serial1 = 220;
        Serial1.write(serial1);
        recognizer.say ("Heaters are off");   
      }
  }
  {//Outdoor
    if (res == 13){
      value = Mw_Outdoor_Windspeed;
      recognizer.say ("It has a Windspeed of" + value + "kilometer per hour");
      value = "";
    }
    if (res == 14){
      value = Mw_Outdoor_UV;
      recognizer.say ("It has a UV Rating of" + value);
      value = "";
    }
    if (res == 15){
      value = Mw_Outdoor_Humitidy;
      recognizer.say ("It has a Humitidy of" + value + "perccent");
      value = "";
    }
    if (res == 5){
      value = Mw_Outdoor_Light_Scale;
      recognizer.say ("It has a brightness of" + value + "precent");
      value = "";
    }
    if (res == 4){
      value = Mw_Outdoor_Temp_Scale;
      recognizer.say ("It is" + value + "degres warm");
      value = "";
    }
  }
}





  if (Serial.available() > 0) {
    Search = Serial.read();
    Found = Found + Search;
  }

  Serial1.write(serial1);

  { //Print


    if (Found == 748)//Wheater Station
    {
      Serial.println('\n');
      Serial.println("__________________________");
      Serial.println("Wheater Station:");
      Serial.println (Found);
      Serial.print("Luftfeuchtigkeit: "); //Im seriellen Monitor den Text und
      Serial.print(Mw_Outdoor_Humitidy); //die Dazugehörigen Werte anzeigen
      Serial.println(" %");
      Serial.print("Temperatur: ");
      Serial.print(Mw_Outdoor_UV);
      Serial.println("°C");
      { //UV
        Serial.print("UV Wert:");
        Serial.println(Mw_Outdoor_UV);

        if (Mw_Outdoor_UV < 10 )
        {
          Serial.println("UV-Index: 0");
          Serial.println("Kein Schutz erforderlich.");
        }

        if (Mw_Outdoor_UV < 46 && Mw_Outdoor_UV > 10 )
        {
          Serial.println("UV-Index: 1");
          Serial.println("Kein Schutz erforderlich.");
        }

        if (Mw_Outdoor_UV < 65 && Mw_Outdoor_UV > 46 )
        {
          Serial.println("UV-Index: 2");
          Serial.println("Kein Schutz erforderlich.");
        }

        if (Mw_Outdoor_UV < 83 && Mw_Outdoor_UV > 65 )
        {
          Serial.println("UV-Index: 3");
          Serial.println("Schutz erforderlich : z.B. Hut, Sonnencreme");
        }

        if (Mw_Outdoor_UV < 103 & Mw_Outdoor_UV > 83 )
        {
          Serial.println("UV-Index: 4");
          Serial.println("Schutz erforderlich : z.B. Hut, Sonnencreme");
        }

        if (Mw_Outdoor_UV < 124 & Mw_Outdoor_UV > 103 )
        {
          Serial.println("UV-Index: 5");
          Serial.println("Schutz erforderlich : z.B. Hut, Sonnencreme");
        }
        if (Mw_Outdoor_UV < 142 & Mw_Outdoor_UV > 124 )
        {
          Serial.println("UV-Index: 6");
          Serial.println("Schutz erforderlich : z.B. Hut, Sonnencreme. Schatten aufsuchen.");
        }

        if (Mw_Outdoor_UV < 162 & Mw_Outdoor_UV > 142 )
        {
          Serial.println("UV-Index: 7");
          Serial.println("Schutz erforderlich : z.B. Hut, Sonnencreme. Schatten aufsuchen.");
        }

        if (Mw_Outdoor_UV < 180 & Mw_Outdoor_UV > 162 )
        {
          Serial.println("UV-Index: 8");
          Serial.println("Aufenthalt im Freien möglichst vermeiden. Schutz erforderlich.");
        }

        if (Mw_Outdoor_UV < 200 & Mw_Outdoor_UV > 180 )
        {
          Serial.println("UV-Index: 9");
          Serial.println("Aufenthalt im Freien möglichst vermeiden. Schutz erforderlich.");
        }

        if (Mw_Outdoor_UV < 221 & Mw_Outdoor_UV > 200 )
        {
          Serial.println("UV-Index: 10");
          Serial.println("Aufenthalt im Freien möglichst vermeiden. Schutz erforderlich.");
        }

        if (Mw_Outdoor_UV > 221 )
        {
          Serial.println("UV-Index: 11");
          Serial.println("Aufenthalt im Freien vermeiden. Schutz DRINGEND erforderlich.");
        }
      }
      Serial.println("__________________________");
      Found = 0;
    }
    if (Found == 722)//Bedroom
    {
      Serial.println('\n');
      Serial.println("__________________________");
      Serial.println("Bedroom:");
      Serial.println (Found);
      Serial.print("Temperatur: ");
      Serial.print(Mw_Room_1_Temp_Scale);
      Serial.println("°C");
      Serial.print("Licht: ");
      Serial.print(Mw_Room_1_Light_Scale);
      Serial.println("%");
      Serial.println("__________________________");
      Found = 0;
    }
    if (Found == 1072)//Commonroom
    {
      Serial.println('\n');
      Serial.println("__________________________");
      Serial.println("Commonroom");
      Serial.println (Found);
      Serial.print("Temperatur: " );
      Serial.print(Mw_Room_2_Temp_Scale);
      Serial.println("°C");
      Serial.print("Licht: " );
      Serial.print(Mw_Room_2_Light_Scale);
      Serial.println("%");
      Serial.println("__________________________");
      Found = 0;
    }
    if (Found == 720)//Kitchen
    {
      Serial.println('\n');
      Serial.println("__________________________");
      Serial.println("Kitchen");
      Serial.println (Found);
      Serial.print("Temperatur: " );
      Serial.print(Mw_Room_3_Temp_Scale);
      Serial.println("°C");
      Serial.print("Licht: " );
      Serial.print(Mw_Room_3_Light_Scale);
      Serial.println("%");
      Serial.println("__________________________");
      Found = 0;
    }
    if (Found == 516)//Haus
    {
      Serial.println('\n');
      Serial.println("__________________________");
      Serial.print("House: ");
      Serial.print("Alarm: ");
      Serial.println(Armed);
      Serial.println("__________________________");
      Found = 0;
    }
  }

}



