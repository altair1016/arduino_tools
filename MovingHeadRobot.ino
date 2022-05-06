#include <Servo.h>
#define trigPin 13
#define echoPin 12
#define FORWARD 1
#define LEFT 2
#define RIGHT 3
int ledRed = 7, ledBlu = 6, ledBianco = 5;
Servo myServo;
void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  myServo.attach(9);
  pinMode(ledRed, OUTPUT);
  //pinMode(ledBlu, OUTPUT);
 // pinMode(ledBianco, OUTPUT);
 
}

void loop() {
  long duration1, distance1, duration2, distance2, duration3, distance3;
  duration1=look(FORWARD);
  distance1 = (duration1/2) / 29.1;
  //
  Serial.print("Distanza Dritto: ");
  Serial.print(distance1);
  Serial.print("\n");
  delay(1500);
  //
  //
  duration2=look(LEFT);
  distance2 = (duration2/2) / 29.1;
  Serial.print("Distanza Sinistra: ");
  Serial.print(distance2);
  Serial.print("\n");
  delay(1500);
   //
   //
  duration3=look(RIGHT);
  distance3 = (duration3/2) / 29.1;
  Serial.print("Distanza Destra: ");
  Serial.print(distance3);
  Serial.print("\n");
  delay(1500);
   //

  //serie di if per verificare quale delle distanze misurate è quella maggiore
  if (distance1 > distance2 && distance1 > distance3) {  // This is where the LED On/Off happens
    while(distance1 > 10){
      Serial.print("cammino....\n");
      digitalWrite(ledBlu,HIGH);
      duration1=look(FORWARD);
      distance1 = (duration1/2) / 29.1;   
    }
    digitalWrite(ledBlu,LOW);
  }else if(distance2 > distance1 && distance2 > distance3){ 
    while(distance2 > 10){
      duration2=look(FORWARD);
      Serial.print("cammino....\n");
      digitalWrite(ledBianco,HIGH);
      distance2 = (duration2/2) / 29.1;  
    }
    digitalWrite(ledBianco,LOW);
  }else if(distance3 > distance1 && distance3 > distance2){
    while(distance3 > 10){
      duration3=look(FORWARD);
      Serial.print("cammino....\n");
      digitalWrite(ledRed,HIGH);
      distance3 = (duration3/2) / 29.1;  
    }
    digitalWrite(ledRed,LOW);
  }

  //Serial.print(distance);
  //Serial.println(" cm"); 
}



int look(int dir){
  //funzione che sposta il sensore e ritorna la distanza
  int dist;
  switch(dir){
     case LEFT:
        myServo.write(170);
       // digitalWrite(ledRed,HIGH);
        break;
     case RIGHT:
        myServo.write(30);

        //digitalWrite(ledBianco,HIGH);
        break;
     default:
        myServo.write(90);
        
        //digitalWrite(ledBlu,HIGH);
        break;
      
  }
  delay(1000);
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  dist =  pulseIn(echoPin, HIGH);
  Serial.print("Dist ");
  Serial.print(dist);
  Serial.print("\n");
  return dist;
}


