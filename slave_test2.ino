#include <SoftwareSerial.h>
SoftwareSerial BTserial(2, 3); // RX | TX

const int hpin = 0;
int heart;
int maped;
String convToChar;
char toBeSent[8];
void setup() 
{
  Serial.begin(38400);
  BTserial.begin(38400);  
}
 
void loop()
{

  readCntrl();
  stringToSend();
  convToChar.toCharArray(toBeSent, 8);
  BTserial.print(toBeSent);
  Serial.write(toBeSent);
  Serial.println(" ");
  delay(250);
}

  void readCntrl() 
  {

  heart = analogRead(hpin);
  maped = map(heart, 0,1000,20,100);
  if (maped<=20){
    maped=0;
    }
  else if (maped >=90) {
    maped=999;}
  
  }
  void stringToSend()
  {
  String startMark = ("[");
  String endMark = ("]");

  convToChar = (startMark + maped  + endMark);
  }
