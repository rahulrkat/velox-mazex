
#define enA 9
#define enB 10
#define in1 6 //left motor
#define in3 7 //right motor
#define noOfIR 5
#define motorSpeed 100

int IRArr[noOfIR] = {0}, LFSens[noOfIR];

LFSensor[0] = A0;
LFSensor[1] = A1;
LFSensor[2] = A2;
LFSensor[3] = A3;
LFSensor[4] = A4;


void setup() {
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in3, OUTPUT);

  for(int i = 0; i < noOfIR; i++){
    pinMode(LFSensor[i], INPUT);
  }
}

void loop() {

  analogWrite(enA, motorSpeed);
  analogWrite(enB, motorSpeed);

  for(int i = 0; i < noOfIR; i++){
    IRArr[i] = digitalRead(LFSensor[i]);
  }


}

//Functions for the robot to turn;

void front(){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, HIGH);
  delay(100);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
}

void right(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  delay(100);     //ye abhi pata nahi ki kitna delay rakhna he toh baadme editkarlenge
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
}

void left(){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  delay(100);     //ye abhi pata nahi ki kitna delay rakhna he toh baadme editkarlenge
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
}

void reverse(){
  right();
  right();
}

void stop(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  delay(10000);
}
