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

String path;

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

void checkPathLeftWallFollow(){

  //Straight path
  if (!IRArr[0] && !IRArr[1] && IRArr[2] && !IRArr[3] && !IRArr[4])
  {
    Serial.println("Move FORWARD");
    path += 'S';
    front();
  }

  //Dead End(V2) or End Of Maze or '+' Instersection
  if (IRArr[0] && IRArr[1] && IRArr[2] && IRArr[3] && IRArr[4])
  {
    // left();
    front();
    if (IRArr[0] && IRArr[1] && IRArr[2] && IRArr[3] && IRArr[4])
    {
      Serial.println("END OF MAZE");
      path += 'E';
    }
    else{
      reverse();
      frontf();
      right();
      path += 'L';
      Serial.println("Intersection : Move LEFT");
    }
  }

  //Left
  if (IRArr[0] && IRArr[1] && IRArr[2] && !IRArr[3] && !IRArr[4])
  {
    Serial.println("Turn LEFT");
    path += 'L';
    left();
  }

  //Right or Right T
  if (!IRArr[0] && !IRArr[1] && IRArr[2] && IRArr[3] && IRArr[4])
  {
    // Serial.println("Turn Right");
    // path += 'R';
    // right();
    front();
    if (!IRArr[0] && !IRArr[1] && !IRArr[2] && !IRArr[3] && !IRArr[4])
    {
      reverse();
      front();
      left();
      path += 'R';
    }
    else path += 'S';
  }

  //Dead End(V1)
  if (!IRArr[0] && !IRArr[1] && !IRArr[2] && !IRArr[3] && !IRArr[4])
  {
    Serial.println("Dead end/REVERSE");
    path += 'B';
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
  //call path.indexOf function 
}


String shortPath(){
  path.replace("LBL","S");
  path.replace("LBS","R");
  path.replace("RBL","B");
  path.replace("SBS","B");
  path.replace("SBL","R");
  path.replace("LBR","B");

  return path;
}
