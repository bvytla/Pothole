#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <Wire.h> 
#define FIREBASE_HOST "gptgajwel-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "WW68HOzwrGpusMKphOoSElPS6gZq5nQkCZAEIDkA"
#define WIFI_SSID "homeiot"
#define WIFI_PASSWORD "homeiot01"

int buz=D7;

int sen=A0;
int trigPin1=D5;
int echoPin1=D6;

int i,temp_v,k;
long int distance,duration;
void setup() 
{
Serial.begin(9600);
pinMode(trigPin1,OUTPUT);
pinMode(echoPin1,INPUT);
pinMode(sen,INPUT);


pinMode(buz,OUTPUT);
digitalWrite(buz,HIGH);


   WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting");
    while(WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(500);
    }
      
      Serial.println();
      Serial.print("connected: ");
      Serial.println(WiFi.localIP());

      Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);  


delay(1000);

}

void loop() 
{

if(Firebase.failed())
     {
       Serial.print("Firebase error");
       Serial.println(Firebase.error());
     }     
  

  SonarSensor(trigPin1,echoPin1);
  delay(50);
   SonarSensor(trigPin1,echoPin1);
   delay(50);
 Serial.print("DISTANCE:");
Serial.println(distance);
Firebase.setFloat("VEHICLE/DISTANCE",distance);
int sen_v=analogRead(A0);
 Serial.print("sen_v:");
Serial.println(sen_v);
if(sen_v<420 || sen_v>470)
{

Serial.println("POTHOLE IS DETECTED ");
digitalWrite(buz,HIGH);

Firebase.setFloat("VEHICLE/POTHOLE",i);
i++;
}

if(distance <20 && distance >15 && sen_v>420 && sen_v<470) 
{
Serial.println("NORAM ROAD");
digitalWrite(buz,LOW);

Firebase.setFloat("VEHICLE/NORMAL",i);
i++;


}

if(distance >21 ) 
{
Serial.println("POTHOLE IS DETECTED ");
digitalWrite(buz,HIGH);

Firebase.setFloat("VEHICLE/POTHOLE",i);
i++;



}

if(distance<15 ) 
{
Serial.println("HUMPS IS DETECTED ");
digitalWrite(buz,HIGH);

Firebase.setFloat("VEHICLE/YHUMPS",i);
i++;


}
}
void SonarSensor(int trigPin,int echoPin)
{
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance = (duration/2) / 29.1;
}
