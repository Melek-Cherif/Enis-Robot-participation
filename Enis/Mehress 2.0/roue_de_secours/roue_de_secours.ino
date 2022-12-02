$#define Enable_A  6
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

const int offset = 20;
int mode, blackBande;
int sensorReadingR1,sensorReadingR2,sensorReadingL1,sensorReadingL2, sensorReadingM; 
bool switcher;

void setup() 
{
  // put your setup code here, to run once:
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT);
  pinMode(Enable_A, OUTPUT);
  pinMode(Enable_B, OUTPUT);
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  mode = 1;
  blackBande = 0;
  switcher = true;
}

void Forward (int speed){
  analogWrite(Enable_A, speed);
  analogWrite(Enable_B, speed + offset);
  digitalWrite(In1,HIGH);
  digitalWrite(In2,LOW);
  digitalWrite(In3,LOW);
  digitalWrite(In4,HIGH);
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

void lineFollower1()
{
    if(sensorReadingL2 == BLACK && sensorReadingL1 == BLACK && sensorReadingM == BLACK && sensorReadingR2 == WHITE)
  {
    Left1(NORMAL_SPEED);
    delay(20);
  }
  
  else if(sensorReadingR2 == BLACK && sensorReadingL2 == WHITE)
  {
    Right1(NORMAL_SPEED);
    delay(4);
  } 
  else if(sensorReadingR2 == WHITE && sensorReadingL2 == BLACK)
  {
    Left1(NORMAL_SPEED);
    delay(4);
  }
  else if (sensorReadingR2 == BLACK && sensorReadingL2 == BLACK) 
  {
    Right1(NORMAL_SPEED);
    delay(30);
    Forward(NORMAL_SPEED);
    delay(15);
  }
  else 
  {
    Forward(NORMAL_SPEED);
  }
}

void lineFollower2()
{
    if (sensorReadingL2 == BLACK && sensorReadingL1 == BLACK && sensorReadingR1 == BLACK &&
  sensorReadingR2 == BLACK) 
  {
    if (blackBande < 2)
    {
      Forward(NORMAL_SPEED);
      delay(350);
      blackBande ++;
      Stop(10);
      delay(1500);
    }
    else 
    {
      if (switcher == false)
      {
        Right1(NORMAL_SPEED);
        delay(400);
        switcher = true;
      }
      else 
      {
        Forward(NORMAL_SPEED);
        delay(50);
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
      delay(5);
    }
    else if (blackBande == 2) 
    {
      Left1(NORMAL_SPEED);
      delay(150);
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
    delay(150);
  }
  else if(sensorReadingR2 == BLACK && sensorReadingL1 == WHITE && sensorReadingL2 == WHITE)
  {
    Right1(NORMAL_SPEED);
    delay(2);
  }
  
  else if(sensorReadingR2 == WHITE && sensorReadingR1 == WHITE  && sensorReadingL2 == BLACK)
  {
    Left1(NORMAL_SPEED);
    delay(2);
  }
  else 
  {
    Forward(NORMAL_SPEED);
  }
}
void loop() 
{
  // put your main code here, to run repeatedly:
  SensorReading();

  if (millis() >= 60000 && millis() < 70000 && mode == 1)
  {
    Stop(10);
    delay(10000);
    mode ++;
  }
  else if(millis() >= 125000 && mode == 2)
  {
    Stop(10);
    delay(500);
    mode ++;
  }
  
  if (millis()< 3000 && mode == 1)
  {
    Forward(150);
  }
  else if (mode == 1)
  {
    lineFollower1();
  }
  else if (mode == 2)
  {
    lineFollower2();
  }
  else if (mode == 3)
  {
    Stop(15);
  }
}
