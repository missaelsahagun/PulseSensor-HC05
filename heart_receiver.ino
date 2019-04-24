#include <SoftwareSerial.h>
SoftwareSerial BTserial(2,3); //RX | TX
const byte numChars = 8;
char receivedChars[numChars];
char tempChars[numChars];
int x_Joy = 0; 

boolean newData = false;

void setup() {
   Serial.begin(38400);        
   BTserial.begin(38400);
}


void loop() {
  recvWithStartEndMarkers();
  if (newData == true) {
    strcpy(tempChars, receivedChars);
    sliceData();
    newData = false;
  }
 runEquipment();
}
//////////////////////////
 void recvWithStartEndMarkers() {
  static boolean recvInProgress = false;
  static byte ndx = 0;
  char startMarker = '[';
  char endMarker = ']';
  char rc;

  while (BTserial.available() > 0 && newData == false) 
  {
    
    rc = BTserial.read();
    //Serial.print(XBee.read());
    if (recvInProgress == true) {
      if (rc != endMarker) {
        receivedChars[ndx] = rc;
        ndx++;
        if (ndx >= numChars) {
          ndx = numChars - 1;
        }
      }
      else {
        receivedChars[ndx] = '\0';      // terminate the string
        recvInProgress = false;
        ndx = 0;
        newData = true;
      }
    }

    else if (rc == startMarker) {
      recvInProgress = true;
    }
  }
}
  void sliceData() 
{
  char * strtokIndx;                       // this is used by strtok() as an index
  strtokIndx = strtok(tempChars, ",");
  x_Joy = atoi(strtokIndx);                // convert this part to an integer
  strtokIndx = strtok(NULL, "]");
    Serial.println(" ");
}
void runEquipment() 
{
  Serial.println(x_Joy);
}
