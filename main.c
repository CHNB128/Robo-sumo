#include <thread>

#ifndef TURNSPPED
// value == 1 degr
#define TURNSPPED 10
#endif

int wheels[2][2] = {
    {10,12},    // left wheel
    {11,13}     // right wheel
};

int directionCases[4][4] = {
    {1,1,1,1},  // forward
    {1,0,1,0},  // back
    {0,1,1,1},  // left
    {1,1,0,1}   // right
};

void go (int directionCase) {
    analogWrite(wheels[0][0], directionCase[0]);
    analogWrite(wheels[0][1], directionCase[1]);
    analogWrite(wheels[1][0], directionCase[2]);
    analogWrite(wheels[1][1], directionCase[3]);
}

void turn (bool side, int angle) {
  // side: true -> right, false -> left
  int angle = angle > 0 && angle < 360
    ? angle
    : angle > 360
      ? 360
      : angle;
  bool isRun = true;
  std::thread turn_thread (
    [] (bool isRun, bool side) {
      if (side) {
        while (isRun){
          go(directionCases[4]);
        }
      } else {
        while (isRun){
          go(directionCases[2]);
        }
      }
    }, side, &isRun);
  delay(TURNSPPED * angle)
  isRun = false;
  turn_thread.join()
}

void setup () {
    // setup wheels
    pinMode(wheels[0][0],OUTPUT);
    pinMode(wheels[0][1],OUTPUT);
    pinMode(wheels[1][0],OUTPUT);
    pinMode(wheels[1][1],OUTPUT);
}

void loop () {
    // test case
    go(directionCases[1]);
    delay(1000);
    go(directionCases[3]);
    delay(1000);
}
