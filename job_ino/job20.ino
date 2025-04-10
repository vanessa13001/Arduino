const int triggerPin = 12;
const int echoPin = 11;

void setup() {
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  Serial.println("Initialisation...");
}

void loop() {
  long duration;
  float distance;

  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2.0) / 29.1;

  Serial.print("Distance : ");
  Serial.print(distance, 2); // 2 chiffres après la virgule
  Serial.println(" cm");

  delay(500);
}