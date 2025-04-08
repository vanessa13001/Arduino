// C++ code
//
const int BUTTON_PIN = 3;
const int MOTOR_PIN = 5;
const int LED_PIN = 6;

int button_state = LOW;
int led_state = LOW;
int motor_state = LOW;
int current_time = 0;

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  pinMode(BUTTON_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(MOTOR_PIN, INPUT);
}

void loop()
{
  button_state = digitalRead(BUTTON_PIN);
  
  if (button_state == HIGH && motor_state == LOW)
  {
    led_state = HIGH;
    current_time = millis();
  }
  else if (button_state == HIGH && motor_state == HIGH)
  {
    led_state = LOW;
    motor_state = LOW;
  }
  if (led_state == HIGH && millis() - current_time >= 5000)
  {
    led_state = LOW;
    motor_state = HIGH;
    
  }
  digitalWrite(LED_PIN, led_state);
  digitalWrite(MOTOR_PIN, motor_state);
}