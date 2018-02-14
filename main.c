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

void go(int wheels, int directionCase) {
    analogWrite(wheels[0][0], directionCase[0]);
    analogWrite(wheels[0][1], directionCase[1]);
    analogWrite(wheels[1][0], directionCase[2]);
    analogWrite(wheels[1][1], directionCase[3]);
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
    go(wheels, directionCases[1]);
    delay(1000); 
    go(wheels, directionCases[3]); 
    delay(1000);     
}