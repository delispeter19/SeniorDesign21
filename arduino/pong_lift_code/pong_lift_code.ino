#include <Servo.h>

Servo servo;
//Serial port;

int incomingByte = 0;
const int A1A = 3;
const int A1B = 2;
const int B1A = 4;
const int B1B = 5;

void motorA(char c){
  if(c == 'R'){
    digitalWrite(A1A,LOW);
    digitalWrite(A1B,HIGH);
  } else if(c == 'L'){
    digitalWrite(A1A,HIGH);
    digitalWrite(A1B,LOW);
  } else {
    digitalWrite(A1A,LOW);
    digitalWrite(A1B,LOW);
  }
}


void motorB(char c){
  if(c == 'R'){
    digitalWrite(B1A,LOW);
    digitalWrite(B1B,HIGH);
  } else if(c == 'L'){
    digitalWrite(B1A,HIGH);
    digitalWrite(B1B,LOW);
  } else {
    digitalWrite(B1A,LOW);
    digitalWrite(B1B,LOW);
  }
}

void setup() {
  // put your setup code here, to run once:
  servo.attach(9);
  pinMode(A1A, OUTPUT);
  pinMode(A1B, OUTPUT);
  pinMode(B1A, OUTPUT);
  pinMode(B1B, OUTPUT);
//  port = new Serial(this, Serial.list()[0], 9600);
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
}

void loop() {
  // put your main code here, to run repeatedly:
  // send data only when you receive data:
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();
    // ARM UP -- W
    if(incomingByte == 119){
      servo.write(90);
    }
    // ARM DOWN -- S
    if(incomingByte == 115){
      servo.write(5);
    }
    
    // Forward -- T
    if(incomingByte == 116){
      motorA('R');
      motorB('R');
    }
    // Backward -- G
    if(incomingByte == 103){
      motorA('L');
      motorB('L');
    }
    // OFF -- SPACE
    if(incomingByte == 32){
      motorA('o');
      motorB('o');
    }

    // TURN <--- -- F
    if(incomingByte == 32){
      motorA('R');
      motorB('L');
      delay(1000);
      motorA('o');
      motorB('o');
    }
    // TURN ---> -- H
    if(incomingByte == 32){
      motorA('L');
      motorB('R');
      delay(1000);
      motorA('o');
      motorB('o');
    }
     

    // say what you got:
    Serial.print("I received: ");
    Serial.println(incomingByte, DEC);
  }  
}
