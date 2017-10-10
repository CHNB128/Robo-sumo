#include <string.h>
  
  int wheel_l[2] = {10,12};
  int wheel_r[2] = {11,13};
  
void setup() {
  pinMode(wheel_l[0],OUTPUT);
  pinMode(wheel_l[1],OUTPUT);
  pinMode(wheel_r[0],OUTPUT);
  pinMode(wheel_r[1],OUTPUT);
}

void go(String doing,int speed,int msec) {
  switch(position) {
    case 'forward':
        int core[4] = {1,1,1,1};
        break;
    case 'back':
        int core[4] = {1,1,1,1};
        break;
    case 'left':
        int core[4] = {1,1,1,1};
        break;
    case 'right':
        int core[4] = {1,1,1,1};
        break;
  }
  analogWrite(whee_l[0], core[0]);
  analogWrite(whee_l[1], core[1]);
  analogWrite(whee_r[0], core[2]);
  analogWrite(whee_r[1], core[3]);
  delay(msec);
}

void go(String doing,int msec) {
  switch(position) {
    case 'forward':
        int core[4] = {1,1,1,1};
        break;
    case 'back':
        int core[4] = {1,1,1,1};
        break;
    case 'left':
        int core[4] = {1,1,1,1};
        break;
    case 'right':
        int core[4] = {1,1,1,1};
        break;
  }
  digitalWrite(whee_l[0], core[0]);
  digitalWrite(whee_l[1], core[1]);
  digitalWrite(whee_r[0], core[2]);
  digitalWrite(whee_r[1], core[3]);
  delay(msec);
}

void loop() {
  for(int i=0;i<=4;i++) {
    go('forward');
    go('left'); 
  }
}