#define SPEED_MAX 255
#define SPEED_MIN 0
#define MAX_ECHO_DISTANCE 2900
#define FORWARD 8
#define LEFT 4
#define RIGHT 6
#define BACK 2

struct Echo {
  int resiver;
  int trigger;
} e;

struct FloorSensor {
  int r;
  int c;
  int l;
} fs;

struct Wheel {
  int dir;
  int pwm;
  int b;
  int sns;
} wl, wr;

int get_distance () {
  unsigned long t1, t2, pulse_width;
  float distance;
  
  digitalWrite(e.trigger, LOW);
  delayMicroseconds(2);
  
  digitalWrite(e.trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(e.trigger, LOW);
  
  while ( digitalRead(e.resiver) == 0 );
  t1 = micros();
  while ( digitalRead(e.resiver) == 1);
  t2 = micros();
  
  pulse_width = t2 - t1;
  distance = pulse_width / 58.0;
  
  if ( pulse_width > MAX_ECHO_DISTANCE ) {
    distance = -1;
    Serial.println("Out of range");
    Serial.print("cm ");
    Serial.println(distance);
  } else {
    Serial.print("cm ");
    Serial.println(distance);
  }
  
  return distance;
}

void go (int direction) {
/*
  2 - back
  8 - forward
  4 - left 
  6 - right
*/
  switch (direction) {
    case 2:
      analogWrite(wl.pwm, SPEED_MAX);
      analogWrite(wr.pwm, SPEED_MAX);
      digitalWrite(wl.dir, LOW);      
      digitalWrite(wr.dir, LOW);      
      break;
    case 4:
      analogWrite(wl.pwm, SPEED_MIN);
      analogWrite(wr.pwm, SPEED_MAX);
      digitalWrite(wl.dir, LOW);      
      digitalWrite(wr.dir, HIGH);    
      break;
    case 6:
      digitalWrite(wl.dir, HIGH);      
      digitalWrite(wr.dir, LOW);          
      analogWrite(wl.pwm, SPEED_MAX);
      analogWrite(wr.pwm, SPEED_MIN);
      break;
    case 8:
      analogWrite(wl.pwm, SPEED_MAX);
      analogWrite(wr.pwm, SPEED_MAX);
      digitalWrite(wl.dir, HIGH);      
      digitalWrite(wr.dir, HIGH);    
      break;      
  }
}

boolean is_grouded () {
  int r = digitalRead(fs.r);
  int c = digitalRead(fs.c);
  int l = digitalRead(fs.l);
//  Serial.print("right");
//  Serial.println(r);
//  Serial.print("center");
//  Serial.println(c);
//  Serial.print("left");
//  Serial.println(l);  
//  Serial.println(c == r && c == l && c == 1);
// without left because left sensor is brocken
  return c == r && c == 1;
}

void setup () {
  Serial.begin(9600); // Starts the serial communication
  fs.r = 11;
  fs.c = 10;
  fs.l = 9;
  pinMode(fs.r, INPUT);
  pinMode(fs.c, INPUT);
  pinMode(fs.l, INPUT);
  e.resiver = A2;
  e.trigger = 12;
  pinMode(e.resiver, INPUT);
  pinMode(e.trigger, OUTPUT);
  wl.pwm = 6;
  wl.dir = 7;
  pinMode(wl.dir, OUTPUT);
  wr.pwm = 5;
  wr.dir = 4;
  pinMode(wr.dir, OUTPUT);
}

void loop () {
  int current_distance = get_distance();
  if(current_distance != -1) {
    go(FORWARD);
  } else {
    go(LEFT);
  }
}