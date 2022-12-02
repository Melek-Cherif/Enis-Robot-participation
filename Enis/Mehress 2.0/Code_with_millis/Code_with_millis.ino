
// all of these ints that will never hold > 255 should be byte variables.

#define Enable_A  6
#define Enable_B  5
#define In1       3
#define In2       4
#define In3       7
#define In4       8

#define MAX_M 255
#define NORMAL_SPEED 180
#define SLOW_M 120

#define BLACK   0
#define WHITE   1

const int S1_PIN = 12;
const int S2_PIN = 11; 
const int S3_PIN = 2;
const int S4_PIN = 9;
const int S5_PIN = 10;
const int TRIG_PIN = A3;
const int ECHO_PIN = A2;
const int offset = 20;
int mode, blackBande, turnRight;
int sensorReadingR1,sensorReadingR2,sensorReadingL1,sensorReadingL2, sensorReadingM; 
int duration, distance, countMaze;
bool calcul, checkMaze;
bool switcher, doubleBlack, Turn, back;

unsigned long startWait,waitWait;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);  //  better to use 115200 or faster to clear the serial output buffer quicker
  
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT);
  pinMode(Enable_A, OUTPUT);
  pinMode(Enable_B, OUTPUT);

  pinMode(S1_PIN, INPUT);
  pinMode(S2_PIN, INPUT);
  pinMode(S3_PIN, INPUT);
  pinMode(S4_PIN, INPUT);
  pinMode(S5_PIN, INPUT);

  pinMode(TRIG_PIN, OUTPUT);
  
  mode = 1;
  Turn = false;
  doubleBlack = true;
  blackBande = 2;
  switcher = true;
  back = false;
  turnRight = 0;
  checkMaze = false;
}
void Forward (int speed){
  analogWrite(Enable_A, speed);
  analogWrite(Enable_B, speed + offset);
  digitalWrite(In1,HIGH);
  digitalWrite(In2,LOW);
  digitalWrite(In3,LOW);
  digitalWrite(In4,HIGH);
}

void Backward (int speed){
  analogWrite(Enable_A, speed);
  analogWrite(Enable_B, speed + offset);
  digitalWrite(In1,LOW);
  digitalWrite(In2,HIGH);
  digitalWrite(In3,HIGH);
  digitalWrite(In4,LOW);
}

void Right (int speed){
  analogWrite(Enable_A, speed);
  analogWrite(Enable_B, speed);
  digitalWrite(In1,HIGH);
  digitalWrite(In2,LOW);
  digitalWrite(In3,LOW);
  digitalWrite(In4,LOW);
}
void Left (int speed){
  analogWrite(Enable_A, speed);
  analogWrite(Enable_B, speed);
  digitalWrite(In1,LOW);
  digitalWrite(In2,LOW);
  digitalWrite(In3,HIGH);
  digitalWrite(In4,LOW);
}
void Right1 (int speed){
  analogWrite(Enable_A, speed);
  analogWrite(Enable_B, speed);
  digitalWrite(In1,HIGH);
  digitalWrite(In2,LOW);
  digitalWrite(In3,HIGH);
  digitalWrite(In4,LOW);
}
void Left1 (int speed){
  analogWrite(Enable_A, speed);
  analogWrite(Enable_B, speed);
  digitalWrite(In1,LOW);
  digitalWrite(In2,HIGH);
  digitalWrite(In3,LOW);
  digitalWrite(In4,HIGH);
}
void Stop (int speed){
  analogWrite(Enable_A, speed);
  analogWrite(Enable_B, speed);
  digitalWrite(In1,LOW);
  digitalWrite(In2,LOW);
  digitalWrite(In3,LOW);
  digitalWrite(In4,LOW);
}

void SensorReading()
{
  sensorReadingL2 = digitalRead(S1_PIN);
  sensorReadingL1 = digitalRead(S2_PIN);
  sensorReadingM  = digitalRead(S3_PIN);
  sensorReadingR1 = digitalRead(S4_PIN);
  sensorReadingR2 = digitalRead(S5_PIN);
}

void CalculDistance()
{
  // clears the trig pin condition
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  //Reads the echo pin
  duration = pulseIn(ECHO_PIN,HIGH);
  // calculating the distance
  distance = duration * 0.034 /2;
}

void LineFollower1()   // first half code
{
  if(sensorReadingL2 == BLACK && sensorReadingL1 == BLACK && sensorReadingM == BLACK && sensorReadingR2 == WHITE)
  {
    Left1(NORMAL_SPEED);
//  delay
    startWait = millis();
    waitWait = 10; // next bunch of times through, wait  
  } 
  else if(sensorReadingR2 == BLACK && sensorReadingL2 == WHITE)
  {
    Right1(NORMAL_SPEED); 
//  delay(dtime);
    startWait = millis();
    waitWait = 4; // next bunch of times through, wait
  }
  else if(sensorReadingR2 == WHITE && sensorReadingL2 == BLACK)
  {
    Left1(180);
//  delay(dtime);
    startWait = millis();
    waitWait = 4; // next bunch of times through, wait
  }
  else if(sensorReadingR2 == BLACK && sensorReadingL2 == BLACK)
  {
    if(doubleBlack == true)
    {
      Right1(NORMAL_SPEED);
//    delay
      startWait = millis();
      waitWait = 30;
      doubleBlack = false;
    }
    else 
    {
      Forward(NORMAL_SPEED);
//    delay
      startWait = millis();
      waitWait = 15;
      doubleBlack = true;
    }
  }
  else   //Go Straight
  {
    Forward(NORMAL_SPEED);
//  delay(dtimer);
  }
}

void LineFollower2()
{
  if (sensorReadingL2 == BLACK && sensorReadingL1 == BLACK &&
  sensorReadingR1 == BLACK && sensorReadingR2 == BLACK) 
  {
    if (blackBande < 2)
    {
      Forward(NORMAL_SPEED);
      startWait = millis();
      waitWait = 350;
      blackBande ++;
    }
    else 
    {
      if (switcher == false)
      {
        Right1(NORMAL_SPEED);
        startWait = millis();
        waitWait = 100;
        switcher = true;
      }
      else 
      {
        Forward(NORMAL_SPEED);
        startWait = millis();
        waitWait = 50;
        switcher = false;
      }
    }
  }
  else if(sensorReadingR2 == WHITE && sensorReadingR1 == BLACK &&
  sensorReadingM == BLACK && sensorReadingL1 == BLACK && sensorReadingL2 == BLACK)
  {
    if (blackBande < 2)
    {
      Left1(NORMAL_SPEED);
      startWait = millis();
      waitWait = 5;
    }
    else if (blackBande == 2) 
    {
      Left1(NORMAL_SPEED);
      startWait = millis();
      waitWait = 150;
      blackBande ++;
    }
    else 
    {
      Left1(NORMAL_SPEED);
    }
  }
  else if(sensorReadingR2 == BLACK && sensorReadingR1 == BLACK &&
  sensorReadingM == BLACK && sensorReadingL1 == BLACK && sensorReadingL2 == WHITE)
  {
    Right1(NORMAL_SPEED);
//  delay
    startWait = millis();
    waitWait = 150;  
  }
  else if(sensorReadingR2 == BLACK && sensorReadingL1 == WHITE && sensorReadingL2 == WHITE)
  {
    Right1(NORMAL_SPEED);
//  delay  
    startWait = millis();
    waitWait = 4;
  }
  else if(sensorReadingR2 == WHITE && sensorReadingR1 == WHITE  && sensorReadingL2 == BLACK)
  {
    Left1(NORMAL_SPEED);
//  delay
    startWait = millis();
    waitWait = 5;
  }
  else 
  {
    Forward(NORMAL_SPEED);
  }
}

void Maze()
{
  CalculDistance();
  if(distance < 15 && back == false)
  {
    Backward(NORMAL_SPEED);
    startWait = millis();
    waitWait = 500;
    back = true;
  }
  else if(back == true) 
  {
    if(turnRight == 0)
    {
      Right1(NORMAL_SPEED);
      startWait = millis();
      waitWait = 750;
      turnRight ++;
      back = false;
    }
    else 
    {
      Left1(NORMAL_SPEED);
      startWait = millis();
      waitWait = 750;
      turnRight = 0;
      back = false;
    }  
  }
  else 
  {
    Forward(NORMAL_SPEED);
  }
}

void InverseLineFollower()
{
  if(sensorReadingR2 == WHITE && sensorReadingR1 == BLACK &&
  sensorReadingL1 == WHITE && sensorReadingL2 == BLACK)
  {
    if(Turn == false)
    {
      Right1(150);
//    delay      
      startWait = millis();
      waitWait = 200;
      Turn = true;
    }
    else 
    {
      Left(150);
//    delay
      startWait = millis();
      waitWait = 5;
    }
  }
  else if(sensorReadingR2 == WHITE && sensorReadingL2 == BLACK)
  {
    Right1(150);
    startWait = millis();
    waitWait = 5;
  }
  else if(sensorReadingR2 == BLACK && sensorReadingL2 == WHITE)
  {
    Left1(150);
//  delay(4);  
    startWait = millis();
    waitWait = 4;  
  }
  else 
  {
    Forward(150);
  }
}

void CheckMaze()
{
  if(sensorReadingR2 == WHITE && sensorReadingR1 == WHITE && sensorReadingM == WHITE && 
  sensorReadingL1 == WHITE && sensorReadingL2 == WHITE )
  {
    Forward(NORMAL_SPEED);
    delay(100);
    countMaze ++;
  }
  else 
  {
    countMaze = 0;
    checkMaze = false;
  }
  if (countMaze == 100)
  {
    checkMaze = true;
  }
}

void loop() 
{      
  SensorReading();

  if(millis() < 2500 && mode == 1)
  {
    Forward(NORMAL_SPEED);
  }
  else if(millis() >= 60000 && mode == 1)
  {
    Stop(10);
    delay(10000);
    mode ++;
  }
  else if( millis() >= 1000 && mode >= 2)
  {
    CheckMaze();
    if (checkMaze == true)
    {
      mode =3;
    }
    else 
    {
      mode =2;
    }
  }
  /*else if(millis() >= 125000 && mode == 3 && checkMaze == false)
  {
    mode--;
  }*/
  if (waitWait > 0)
  {
    if ( millis() - startWait >= waitWait )
    {
      waitWait = 0; // next time through, read the sensors, etc
    }
  }
  else 
  {
    if(mode == 1)
    {
      LineFollower1();
    }
    else if(mode == 2)
    {
      LineFollower2();
  //  CheckMaze();
    }  
    else if(mode == 3)
    {
      Stop(10);
      delay(1000);
    }
    else if(mode == 4)
    {
      InverseLineFollower();
    }
  }
}
