#include <Servo.h>
#include <Wire.h>
//#include <ESP8266WiFi.h>

int enA=5;
int en1=6;
int en2=7;
int en3=8;
int en4=9;
int enB=10;
int change=0;
int c=0;
Servo myservo;
String s="";

void setup() {

pinMode(en1,OUTPUT);
pinMode(en2,OUTPUT);
pinMode(en3,OUTPUT);
pinMode(en4,OUTPUT);
pinMode(enA,OUTPUT);
pinMode(enB,OUTPUT);
myservo.attach(11);

 Wire.begin(8);                /* join i2c bus with address 8 */
 Wire.onReceive(receiveEvent); /* register receive event */
 
 
}

void loop()
{
      delay(100);
       if (s=="forward")
    {
     forward();
     s="";
      }
     else if (s=="backward")
    {
     backward();
     s="";
      }
     else if (s=="left")
    {
     left();
     s="";
      }
     else if (s=="right")
    {
     right();
     s="";
      }
      else if (s=="stop")
    {
     stop();
     s="";
      }
  }

void receiveEvent(int howMany)
{s="";
 while (0 <Wire.available()) 
 {  
    char c = Wire.read();      /* receive byte as a character */
    s+=c;
    Serial.begin(9600);
    //Serial.println(c);
  }
Serial.begin(9600);
    //Serial.println(s);
}
void backward()
{
  int var=2;
    Serial.print(var);
  analogWrite(enA,255);
  analogWrite(enB,255);
  digitalWrite(en1,LOW);
  digitalWrite(en2,HIGH);
  digitalWrite(en3,LOW);
  digitalWrite(en4,HIGH);
 
  
}

  void forward()
{
  int var=1;
    Serial.print(var);
    analogWrite(enA,255);
    analogWrite(enB,255);
    digitalWrite(en1,HIGH);
    digitalWrite(en2,LOW);
    digitalWrite(en3,HIGH);
    digitalWrite(en4,LOW);
    
}


 void right()
{
  int var=4;
    Serial.print(var);
  analogWrite(enA,255);
  analogWrite(enB,255);
  digitalWrite(en1,HIGH);
  digitalWrite(en2,LOW);
  digitalWrite(en3,LOW);
  digitalWrite(en4,HIGH);
  delay(1000);
     analogWrite(enA,255);
    analogWrite(enB,255);
    digitalWrite(en1,HIGH);
    digitalWrite(en2,LOW);
    digitalWrite(en3,HIGH);
    digitalWrite(en4,LOW);
   
}

 void left()
{
  int var=3;
    Serial.print(var);
  analogWrite(enA,255);
  analogWrite(enB,255);
  digitalWrite(en1,LOW);
  digitalWrite(en2,HIGH);
  digitalWrite(en3,HIGH);
  digitalWrite(en4,LOW);
  delay(1000);
     analogWrite(enA,255);
    analogWrite(enB,255);
    digitalWrite(en1,HIGH);
    digitalWrite(en2,LOW);
    digitalWrite(en3,HIGH);
    digitalWrite(en4,LOW);
   
}
 void stop()
{
 
    int var=0;
    Serial.print(var);
    analogWrite(enA,255);
    analogWrite(enB,255);
    digitalWrite(en1,LOW);
    digitalWrite(en2,LOW);
    digitalWrite(en3,LOW);
    digitalWrite(en4,LOW);
}

