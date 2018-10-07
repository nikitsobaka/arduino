#include   <Servo.h>

Servo myservo;  // create servo object to control a servo
// a maximum of eight servo objects can be created

int pos = 70;    // variable to store the servo position
const int maxDeg = 100;
const int minDeg = 50;

const int leftPin = 2;
const int rightPin = 3;

bool center = false;
bool centering = false;
bool lefton = false;
bool righton = false;
bool forwardon = false;
bool backwardon = false;
int p = 13;

int STBY = 10; //standby
int PWMA = 6; //Speed control
int AIN1 = 11; //Direction
int AIN2 = 12; //Direction

const int outputPin = 9; // pwm function will be disabled on pin 9 and 10 if using servo

int leftPressed = 0;
int rightPressed = 0;
int forward = 0;
int backward = 0;
int i=50;
int timer=0;
int btime=0;
void setup()
{
  Serial.begin(9600);
  myservo.attach(outputPin);  // attaches the servo on pin 9 to the servo object
  pinMode(leftPin, INPUT);
  pinMode(rightPin, INPUT);
  pinMode(STBY, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(p, OUTPUT);

}
void move(int motor, int speed, int direction) {
  //Move specific motor at speed and direction
  //motor: 0 for B 1 for A
  //speed: 0 is off, and 255 is full speed
  //direction: 0 clockwise, 1 counter-clockwise
  digitalWrite(STBY, HIGH);
  boolean inPin1 = LOW;
  boolean inPin2 = HIGH;

  if (direction == 1) {
    inPin1 = HIGH;
    inPin2 = LOW;
  }


  digitalWrite(AIN1, inPin1);
  digitalWrite(AIN2, inPin2);
  analogWrite(PWMA, speed);

}
void stop() {
  //enable standby
  digitalWrite(STBY, LOW);
}
void loop()
{

 Serial.println(i);
  forward = digitalRead(8);
  backward = digitalRead(7);
  leftPressed = digitalRead(leftPin);
  rightPressed = digitalRead(rightPin);
  
  if (forward) {
    timer=0;
    Serial.println(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>!!!!!");
    forwardon = true;
    if (btime>15){
    tone(p, 600, 500);
    btime=0;}
    btime++;
      move(1, i=i+10, 1);
      if (i>=120){
        i=110;
      }
      delay(10);
  }
//  else if (backwardon == false && forwardon == false && i>70)
//  {
//    move(1, i=i-25, 1);
//    forwardon = false;
//  }
  else
  {forwardon = false;}

  if (backward) {
    timer=0;
    Serial.println("!!!!<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
    backwardon = true;
    

      move(1, i=i+10, 0);
            if (i>=250){
        i=240;
      }
      delay(10);
  }
//  else if(backwardon == false && forwardon == false && i>70)
//  {
//          move(1, i=i-25, 0);
//    backwardon = false;
//  }
  else
  {backwardon = false;}
if (backwardon == false && forwardon == false){
  Serial.println(timer);
  Serial.println("!!!!!!!!!!!!!!!!!!!!!!!!!!!STOP!!!!!!!!!");
    
    if (timer >= 2 && i>50){
    i=i-20;
    timer--;
    }
    stop();
    timer++;
}

  if (leftPressed ) {
    Serial.println("left");
    lefton = true;
    if (pos < maxDeg) pos += 10;
    myservo.write(pos);              // tell servo to go to position in variable ‘pos’

    center = false;
  } else lefton = false;


  if (rightPressed ) {
    Serial.println("right");
    righton = true;
    if (pos > minDeg) pos -= 10;
    myservo.write(pos);              // tell servo to go to position in variable ‘pos’

    center = false;
  } else righton = false;

  if (pos < 75 && lefton == false && righton == false) {
    Serial.println("centering on");
    centering = true;
    pos += 5;
    myservo.write(pos);              // tell servo to go to position in variable ‘pos’

    delay(5);
  } else if (pos > 75  && lefton == false && righton == false) {
    Serial.println("centering on");
    centering = true;
    pos -= 5;
    myservo.write(pos);              // tell servo to go to position in variable ‘pos’

    delay(5);
  } else
    center = true;
//  Serial.println("center ok");
  centering = false;
//  Serial.println("centering off");

  delay(15);                       // waits 15ms for the servo to reach the position

}


