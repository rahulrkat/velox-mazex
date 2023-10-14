Consider that we have 3 IR Sensors (can depend on the number of sensors we recieve in the kit but 3 is minimum) and we make a array out of it. 0 represents there given IR sensor senses a white floor, and 1 for a black floor. Code (not exact) :

```cpp
int IRArr[3] = {0}, LFSensor[3];
LFSensor[0] = A0;
LFSensor[1] = A1;
LFSensor[2] = A2;

void setup(){
  for(int i = 0; i < 3; i++){
    pinMode(LFSensor[i], INPUT);
  }
}

void loop(){
  for(int i = 0; i < 3; i++){
    IRArr[i] = digitalRead(LFSensor[i]);  //To constantly update the array from where the bot will get to know which way to turn.
  }
}

```

We now maintain a character array which stores the path. (We can maybe use a vector instead of an array as I feel it could be better?) Let it be:

```cpp
char path[100] = " ";
int pathLength = 0;
```

Possibilities:

  Straight : Only the middle IR sensor will be lit. So the IRArr will be {0, 1, 0}. In this case we can keep moving forward.

  Left : IRArr will be {1, 1, 0}. The bot will move some slight distance before taking a left turn.

  Right : IRArr will be {0, 1, 1}. The bot will move some slight distance before taking a right turn.

  T shaped : IRArr will be {1, 1, 1}. Since we are following the left wall follow approach, we take a left turn here.

  Dead end : IRArr will be {0, 0, 0}. We take a U-Turn.

PseudoCode:

```cpp

if(Left){
  path[pathLength] = 'L';
  pathLength++;
}

if(Right){
  path[pathLength] = 'R';
  pathLength++;
}

if(T Shaped){
  path[pathLength] = 'L';
  pathLength++;
}

if(U Turn){
  path[pathLength] = 'B';
  pathLength++;
}

```

  
