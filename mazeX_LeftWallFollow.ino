// Motor A connections
int enA = 3;
int in1 = 2;
int in2 = 4;
// Motor B connections
int enB = 6;
int in3 = 7;
int in4 = 8;

int noOfIR 5;
int motorSpeed 100;

int IRArr[noOfIR] = {0}, LFSens[noOfIR];

LFSensor[0] = 9;
LFSensor[1] = 10;
LFSensor[2] = 11;
LFSensor[3] = 12;
LFSensor[4] = 13;

//Path setup

String path;

int dryRun = 0;

int pathLength = 0;
int pathIndex = 0;


void setup() {

  Serial.begin(9600);

  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

  for(int i = 0; i < noOfIR; i++){
    pinMode(LFSensor[i], INPUT);
  }
}

//------------------------------//

void loop() {

  analogWrite(enA, motorSpeed);
  analogWrite(enB, motorSpeed);

  for(int i = 0; i < noOfIR; i++){
    IRArr[i] = digitalRead(LFSensor[i]);
  }

  if(dryRun == 0) checkPathRightWallFollow();

  else if (dryRun == 1)
  {
    finalRun();
  }


}

//------------------------//

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
      stop1();
    }
    else{
      reverse1();
      left();
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
      reverse1();
      right();
      path += 'R';
    }
    else{
      front();
      path += 'S';
    }
  }

  //Dead End(V1)
  if (!IRArr[0] && !IRArr[1] && !IRArr[2] && !IRArr[3] && !IRArr[4])
  {
    Serial.println("Dead end/REVERSE");
    path += 'B';
    reverse2();
  }

}

void front(){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(100);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void right(){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  delay(100);     //ye abhi pata nahi ki kitna delay rakhna he toh baadme editkarlenge

  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void left(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(100);     //ye abhi pata nahi ki kitna delay rakhna he toh baadme editkarlenge
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void reverse1(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  delay(100);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void reverse2(){
  right();
  right();
}

void stop1(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  shortPath();
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  dryRun = 1;
  Serial.println(path);
  delay(10000);


  //call path.indexOf function 
}

void stop2(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  delay(10000);
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

void finalRun(){
  int i = 0;

  if (!(!IRArr[0] && !IRArr[1] && IRArr[2] && !IRArr[3] && !IRArr[4]))
  {
    if (path.charAt(i)== 'L') {
      // Update the PATH only if there is a change
      // take left turn
      left();
      i++;
    }

    if (path.charAt(i)== 'R') {
      // Update the PATH only if there is a change
      // take right turn
      right();
      i++;
    }

    if (path.charAt(i)== 'S') {
      // Update the PATH only if there is a change
      // move straight
      // moveForward();
      front();
      i++;
    }
  }

  if (!IRArr[0] && !IRArr[1] && IRArr[2] && !IRArr[3] && !IRArr[4])
  {
    front();
  }
  if (IRArr[0] && IRArr[1] && IRArr[2] && IRArr[3] && IRArr[4])
  {
    stop2();
  }
}
