const int servopin = 9;
const int musclePin = A1;
int targetAngle = 0;
int currentAngle = 0;
int stepDelay;
int muscleVal;

void setup() {
  Serial.begin(9600);
  pinMode(servopin, OUTPUT);
}

void loop() {

  muscleVal = analogRead(musclePin);
  targetAngle = map(muscleVal, 300, 1000, 0, 180);

  if (currentAngle < targetAngle) {
    currentAngle++;
  } 
  else if (currentAngle > targetAngle) {
    currentAngle--;
  }

  if (abs(currentAngle - targetAngle) > 20){
    stepDelay = 0;
  }
  else if (abs(currentAngle - targetAngle) <= 8){
    stepDelay = 50;
  }

  writeServo(currentAngle);
  delay(stepDelay);

  Serial.print("MuscleVal: ");
  Serial.print(muscleVal);
  Serial.print("  TargetAngle: ");
  Serial.println(targetAngle);
}

void writeServo(int ang) {
  int pulseWidth = map(ang, 0, 180, 1000, 2000);
  digitalWrite(servopin, HIGH);
  delayMicroseconds(pulseWidth);
  digitalWrite(servopin, LOW);
  delayMicroseconds(20000 - pulseWidth);
}
