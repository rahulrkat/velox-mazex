/* 

      * * * * * --------------> placement of the ir sensors

*/




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

//Path setup

string path;
int pathLength = 0;
int pathIndex = 0;


void setup() {

  Serial.begin(9600);

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

  checkPathRightWallFollow();


}

//Checking path function

void checkPathRightWallFollow(){

  //Straight path
  if (!IRArr[0] && !IRArr[1] && IRArr[2] && !IRArr[3] && !IRArr[4])
  {
    path += 'S';
    front();
  }

  //Dead End or End Of Maze
  if (IRArr[0] && IRArr[1] && IRArr[2] && IRArr[3] && IRArr[4])
  {
    
    front();
    if (IRArr[0] && IRArr[1] && IRArr[2] && IRArr[3] && IRArr[4])
    {
      path += 'E';
      stop(); //abhi isse code karna he
    }
    else{
      path += 'R';
      reverse();
      checkPathRightWallFollow();
    } 
  }

  //Left
  if (IRArr[0] && IRArr[1] && IRArr[2] && !IRArr[3] && !IRArr[4])
  {
    path += 'L';
    left();
  }

  //Right
  if (!IRArr[0] && !IRArr[1] && IRArr[2] && IRArr[3] && IRArr[4])
  {
    path += 'R';
    right();
  }

  //
  if (!IRArr[0] && !IRArr[1] && !IRArr[2] && !IRArr[3] && !IRArr[4])
  {
    reverse();
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
