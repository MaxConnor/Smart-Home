#include <DHT.h>
#include <Wire.h>

#define DHTPIN 2
#define DHTTYPE DHT22



DHT dht(DHTPIN, DHTTYPE);

int Iw_Weather_Station_Temp= 0;
int Iw_Weather_Station_Humidity= 0;

int Mw_Weather_Station_Temp= 0;
int Mw_Weather_Station_Humidity=0;

int Iw_Weather_Station_UV = A0;
int Iw_Outdoor_Light = A1;

int Mw_Outdoor_Light_Unscale;
int Mw_Outdoor_Light_Scale;

void setup() 
{
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);
  Serial3.begin(9600);
  Serial.println("ready");
  dht.begin(); //DHT22 Sensor starten
}

void loop() 
{

    Mw_Outdoor_Light_Unscale = analogRead(Iw_Outdoor_Light);
    Mw_Outdoor_Light_Scale = map(Mw_Outdoor_Light_Unscale, 0, 1023, 100, 0);
    
{//UV
  Iw_Weather_Station_UV = analogRead(A0); // Iw_Weather_Station_UV wird an der Schnittstelle A0 ausgelesen...   
  Serial.print("UV Wert:");
  Serial.println(Iw_Weather_Station_UV);  // ...und anschließend zur Kontrolle im seriellen Monitor ausgegeben.

  if (Iw_Weather_Station_UV < 10 )      // Wenn der Iw_Weather_Station_UV kleiner als 10 ist...
  {
    Serial.println("UV-Index: 0");   // ... soll diese Meldung...
    Serial.println("Kein Schutz erforderlich.");  // ... im seriellen Monitor erscheinen.
  }
  
  if (Iw_Weather_Station_UV < 46 && Iw_Weather_Station_UV > 10 )  // Wenn der Iw_Weather_Station_UV kleiner als 46 und größer als 10 ist...
  {
    Serial.println("UV-Index: 1");    // ...soll diese Meldung...
    Serial.println("Kein Schutz erforderlich.");  // ... im seriellen Monitor erscheinen.
  }
  
  if (Iw_Weather_Station_UV < 65 && Iw_Weather_Station_UV > 46 )
  {
    Serial.println("UV-Index: 2");
    Serial.println("Kein Schutz erforderlich.");
  }
  
  if (Iw_Weather_Station_UV < 83 && Iw_Weather_Station_UV > 65 )
  {
    Serial.println("UV-Index: 3");
    Serial.println("Schutz erforderlich : z.B. Hut, Sonnencreme");
  }
  
  if (Iw_Weather_Station_UV < 103 & Iw_Weather_Station_UV > 83 )
  {
    Serial.println("UV-Index: 4");
    Serial.println("Schutz erforderlich : z.B. Hut, Sonnencreme");
  }
  
  if (Iw_Weather_Station_UV < 124 & Iw_Weather_Station_UV > 103 )
  {
    Serial.println("UV-Index: 5");
    Serial.println("Schutz erforderlich : z.B. Hut, Sonnencreme");
  }
  if (Iw_Weather_Station_UV < 142 & Iw_Weather_Station_UV > 124 )
  {
    Serial.println("UV-Index: 6");
    Serial.println("Schutz erforderlich : z.B. Hut, Sonnencreme. Schatten aufsuchen.");
  }
  
  if (Iw_Weather_Station_UV < 162 & Iw_Weather_Station_UV > 142 )
  {
    Serial.println("UV-Index: 7");
    Serial.println("Schutz erforderlich : z.B. Hut, Sonnencreme. Schatten aufsuchen.");
  }
  
  if (Iw_Weather_Station_UV < 180 & Iw_Weather_Station_UV > 162 )
  {
    Serial.println("UV-Index: 8");
    Serial.println("Aufenthalt im Freien möglichst vermeiden. Schutz erforderlich.");
  }
  
  if (Iw_Weather_Station_UV < 200 & Iw_Weather_Station_UV > 180 )
  {
    Serial.println("UV-Index: 9");
    Serial.println("Aufenthalt im Freien möglichst vermeiden. Schutz erforderlich.");
  }
  
  if (Iw_Weather_Station_UV < 221 & Iw_Weather_Station_UV > 200 ) 
  {
    Serial.println("UV-Index: 10");
    Serial.println("Aufenthalt im Freien möglichst vermeiden. Schutz erforderlich.");
  }

  if (Iw_Weather_Station_UV > 221 )
  {
    Serial.println("UV-Index: 11");
    Serial.println("Aufenthalt im Freien vermeiden. Schutz DRINGEND erforderlich.");
  }
}
{//Wheater
  float Mw_Weather_Station_Humidity = dht.readHumidity();
  float Mw_Weather_Station_Temp = dht.readTemperature();

  Serial.print("Luftfeuchtigkeit: "); //Im seriellen Monitor den Text und 
  Serial.print(Mw_Weather_Station_Humidity); //die Dazugehörigen Werte anzeigen
  Serial.println(" %");
  Serial.print("Temperatur: ");
  Serial.print(Mw_Weather_Station_Temp);
  Serial.println("°C");
  Serial.print ("Helligkeit:");
  Serial.print (Mw_Outdoor_Light_Scale);
  Serial.println ("%");
}
 Serial.println("____________________________________");
  
  Serial2.write(12);
  Serial3.write(21);
}
 
