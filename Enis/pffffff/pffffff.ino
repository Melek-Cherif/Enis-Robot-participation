#define Enable_A  6
#define Enable_B  5
#define In1       3
#define In2       4
#define In3       7
#define In4       8

#define MAX_M 255
#define NORMAL_M 180
#define SLOW_M 120

#define BLACK   0
#define WHITE   1


const int S1_PIN = 12;
const int S2_PIN = 11; 
const int S3_PIN = 2;
const int S4_PIN = 9;
const int S5_PIN = 10;
const int offset = 20;
int blackBande;
int sensorReadingR1,sensorReadingR2,sensorReadingL1,sensorReadingL2, sensorReadingM; 
bool Turn;

void setup() 
{
  // put your setup code here, to run once:
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT);
  pinMode(Enable_A, OUTPUT);
  pinMode(Enable_B, OUTPUT);
  Serial.begin(9600);
  blackBande = 0;
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
  digitalWrite(In2,HIGH);
  digitalWrite(In1,LOW);
  digitalWrite(In4,LOW);
  digitalWrite(In3,HIGH);
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
  sensorReadingM = digitalRead(S3_PIN);
  sensorReadingR1 = digitalRead(S4_PIN);
  sensorReadingR2 = digitalRead(S5_PIN);
}
void loop() {
  // put your main code here, to run repeatedly:
  SensorReading();

  if (sensorReadingL2 == BLACK && sensorReadingL1 == BLACK && sensorReadingR1 == BLACK &&
  sensorReadingR2 == BLACK && sensorReadingM == BLACK && (blackBande < 2)) 
  {
    Forward(180);
    delay(350);
    blackBande ++;
  } 
  else if(sensorReadingR2 == WHITE && sensorReadingR1 == WHITE &&
  sensorReadingM == BLACK && sensorReadingL1 == BLACK && sensorReadingL2 == BLACK)
  {
    Left(180);
    delay(150);
  }
  else if(sensorReadingR2 == BLACK && sensorReadingR1 == BLACK &&
  sensorReadingM == BLACK && sensorReadingL1 == WHITE && sensorReadingL2 == WHITE)
  {
    Right1(180);
    delay(150);
  }
  else if(sensorReadingR2 == WHITE && sensorReadingR1 == BLACK && sensorReadingL1 == WHITE && sensorReadingL2 == WHITE)
  {
    Right1(180);
    delay(2);
  }
  
  else if(sensorReadingR1 == WHITE && sensorReadingR1 == WHITE && sensorReadingL1 == BLACK && sensorReadingL2 == WHITE)
  {
    Left1(180);
    delay(2);
  }

  else 
  {
    Forward(180);
  }
}
