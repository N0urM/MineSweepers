#include <SoftwareSerial.h> // use the software uart

SoftwareSerial esp01 (6, 7); // RX, TX
#define TIMEOUT 5000 // mS

int in11 = A0 , in12 = A1  ; //motor 1
int in21 = A2 , in22 = A3 ;  //motor 2
int in31 = A4 , in32 = A5 ;  //motor 3
int in41 = A6 , in42 = A7 ;  //motor 4

char data;



void setup() {

  pinMode (in11 , OUTPUT);
  pinMode (in12 , OUTPUT);
  pinMode (in21 , OUTPUT);
  pinMode (in22 , OUTPUT);
  pinMode (in31 , OUTPUT);
  pinMode (in32 , OUTPUT);
  pinMode (in41 , OUTPUT);
  pinMode (in42 , OUTPUT);

  
  esp01.begin(9600);
  Serial.begin(9600);

  SendCommand("AT+RST", "Ready");
  delay(5000);
  SendCommand("AT+CWMODE=1","OK");
  SendCommand("AT+CIFSR", "OK");
  SendCommand("AT+CIPMUX=1","OK");
  SendCommand("AT+CIPSERVER=1,80","OK");



}

void loop() {

  if (esp01.available () ) {
    data = esp01.read();
  }

  if (data == 'f')
    Forward ();
  else if (data == 'b')
    Back ();
  else if (data == 's')
    Stop();
  else if (data == 'r')
    TurnRight();
  else if (data == 'l')
    TurnLeft ();


}



void Forward () {

  analogWrite (in11 , 255);
  analogWrite (in12 , 0);

  analogWrite (in21 , 122);
  analogWrite (in22 , 0);

  analogWrite (in31 , 122);
  analogWrite (in32 , 0);

  analogWrite (in41 , 122);
  analogWrite (in42 , 0);



}

void TurnRight () {

  analogWrite (in11 , 255);
  analogWrite (in12 , 0);

  analogWrite (in21 , 0);
  analogWrite (in22 , 0);

  analogWrite (in31 , 122);
  analogWrite (in32 , 0);

  analogWrite (in41 , 0);
  analogWrite (in42 , 0);



}

void TurnLeft () {

  analogWrite (in11 , 0);
  analogWrite (in12 , 122);

  analogWrite (in21 , 0);
  analogWrite (in22 , 0);

  analogWrite (in31 , 0);
  analogWrite (in32 , 122);

  analogWrite (in41 , 0);
  analogWrite (in42 , 0);



}

void Stop () {

  analogWrite (in11 , 0);
  analogWrite (in12 , 0);

  analogWrite (in21 , 0);
  analogWrite (in22 , 0);

  analogWrite (in31 , 0);
  analogWrite (in32 , 0);

  analogWrite (in41 , 0);
  analogWrite (in42 , 0);


}

void Back () {

  analogWrite (in11 , 0);
  analogWrite (in12 , 70);

  analogWrite (in21 , 0);
  analogWrite (in22 , 70);

  analogWrite (in31 , 0);
  analogWrite (in32 , 70);

  analogWrite (in41 , 0);
  analogWrite (in42 , 70);


}

boolean SendCommand(String cmd, String ack){
  esp01.println(cmd); // Send "AT+" command to module
  if (!echoFind(ack)) // timed out waiting for ack string
    return true; // ack blank or ack found
}


boolean echoFind(String keyword){
   byte current_char = 0;
   byte keyword_length = keyword.length();
   long deadline = millis() + TIMEOUT;
   while(millis() < deadline){
    if (esp01.available()){
      char ch = esp01.read();
      Serial.write(ch);
      if (ch == keyword[current_char])
        if (++current_char == keyword_length){
         Serial.println();
         return true;
      }
     }
    }
   return false; // Timed out
}


