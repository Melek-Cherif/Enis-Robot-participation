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
const int offset = 40;
const int trigPin = 13
;
const int echoPin = A2 ;

int blackBande;
int sensorReadingR1,sensorReadingR2,sensorReadingL1;
int sensorReadingL2, sensorReadingM; 
int turnRight, turnLeft;
int duration, distance;
bool Turn, switcher;

void setup() 
{
  // put your setup code here, to run once:
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
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  Serial.begin(9600);
  turnRight = 0;
  turnLeft = 0;
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

void calculeDistance()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
}
void loop() {
  // put your main code here, to run repeatedly:
  SensorReading();

  calculeDistance();
  Serial.println(distance);
  
  if(distance > 30 && distance < 150)
  {
    Forward(180);
  }
  else if (distance < 25)
  {
    if(turnRight == 0 || turnRight >= 3)
    {
      Right1(150);
      delay(700);
      turnRight++;
    }
    else 
    {
      Left1(150);
      delay(500);
      turnLeft++;
      turnRight ++;
    }
  }  
  else 
  {
    Forward(180);
  }
}
