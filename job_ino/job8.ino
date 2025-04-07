// C++ code
//
int on_time = 5;
int off_time = 100;
int *on_pointer = &on_time;
int *off_pointer = &off_time;

int on_off = 0;
int *on_off_pointer = &on_off;

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  digitalWrite(6, HIGH);
}

void loop()
{
  analogWrite(7, 255);
  delay(*on_pointer);
  
  if (*on_pointer >= 100)
  {
    *on_off_pointer = 1;
    delay(2000);
  }
  
  *off_pointer = 100 - *on_pointer;
  
  analogWrite(7, 0);
  delay(*off_pointer);
  
  if (*on_pointer <= 0)
  {
    *on_off_pointer = 0;
    delay(2000);
  }
  
  if (*on_pointer < 100 && *on_off_pointer == 0)
  {
    *on_pointer += 5;
  }
  else if (*on_pointer > 0 && *on_off_pointer == 1)
  {
    *on_pointer -= 5;
  }
}