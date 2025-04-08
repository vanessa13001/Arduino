// C++ code
//
int potentio_value = 0;
  
int on_time = 0;
int off_time = 100;
int *on_pointer = &on_time;
int *off_pointer = &off_time;

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  pinMode(7, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(A1, INPUT);
}

void loop()
{
  potentio_value = analogRead(A1);
  *on_pointer = map(potentio_value, 0, 1023, 0, 100);

  digitalWrite(7, HIGH);
  digitalWrite(4, LOW);
  delay(*on_pointer);
  
  *off_pointer = 100 - *on_pointer;
  
  digitalWrite(7, LOW);
  digitalWrite(4, HIGH);
  delay(*off_pointer);
}