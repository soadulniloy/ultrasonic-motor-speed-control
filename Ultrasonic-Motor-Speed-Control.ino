const int trigPin = 7;
const int echoPin = 8;
const int motorPin = 9;

const int safeDistance = 50;
const int slowDistance = 20;
const int stopDistance = 5;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(motorPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  long distance = readDistance();
  int motorSpeed = calculateSpeed(distance);
  analogWrite(motorPin, motorSpeed);
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm | Motor Speed: ");
  Serial.println(motorSpeed);
  delay(100);
}

long readDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  long distance = duration * 0.034 / 2;
  return distance;
}

int calculateSpeed(long distance) {
  if (distance >= safeDistance) {
    return 255;
  } 
  else if (distance <= stopDistance) {
    return 0;
  } 
  else if (distance >= slowDistance) {
    return map(distance, slowDistance, safeDistance, 100, 255);
  } 
  else {
    return map(distance, stopDistance, slowDistance, 0, 100);
  }
}
