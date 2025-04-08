// C++ code
//
int button_state = LOW;
int *button_pointer = &button_state;

int last_button_state = LOW;
unsigned long last_press_time = 0;
unsigned long press_duration = 0;
int led_on = 0;
int click_count = 0;
int blinking_led = false;

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  pinMode(7, OUTPUT);
  pinMode(2, INPUT);
}

void loop()
{
  button_state = digitalRead(2);

  if (button_state == LOW && last_button_state == HIGH)
  {
    long unsigned int current_time = millis();
    press_duration = current_time - last_press_time;
    last_press_time = current_time;
    
    if (press_duration > 3000 && led_on == 1)
    {
      click_count = 0;
      led_on = 0;
      digitalWrite(7, LOW);
    } 
    else
    {
      click_count++;
    }
  }
  else if (button_state == HIGH)
  {
    digitalWrite(7, HIGH);
  }
  else if (led_on == 0)
  {
    digitalWrite(7, LOW);
  }

  last_button_state = button_state;

  if (millis() - last_press_time > 500 && click_count > 0)
  {
    if (click_count == 2)
    {
      led_on = 1;
      digitalWrite(7, HIGH);
    } 
    else if (click_count == 3)
    {
      for (int i = 0; i < 5; i++)
      {
        digitalWrite(7, HIGH);
        delay(500);
        digitalWrite(7, LOW);
        delay(500);
      }
    }
    click_count = 0;
  }
}