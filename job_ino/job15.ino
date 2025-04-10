const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;
const int potPin = A0;
const int MAX_BRIGHTNESS = 80; // Limite à ~18mA pour être safe

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW); // Éteint la LED intégrée pour économiser du courant
  
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  
  analogWrite(redPin, 0);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 0);
}

void loop() {
  int potValue = analogRead(potPin);
  int hue = map(potValue, 0, 1023, 0, 359); // 0-359 pour HSV
  
  setSafeRGB(hue);
  delay(20);
}

void setSafeRGB(int hue) {
  float r, g, b;
  
  // Conversion en HSV (Hue, Saturation, Value)
  hue %= 360;
  float s = 1.0, v = MAX_BRIGHTNESS/255.0; // Saturation à 100%, Valeur limitée
  float c = v * s;
  float x = c * (1 - abs(fmod(hue/60.0, 2) - 1));
  float m = v - c;
  
  if(hue < 60)      { r = c; g = x; b = 0; }
  else if(hue < 120){ r = x; g = c; b = 0; }
  else if(hue < 180){ r = 0; g = c; b = x; }
  else if(hue < 240){ r = 0; g = x; b = c; }
  else if(hue < 300){ r = x; g = 0; b = c; }
  else              { r = c; g = 0; b = x; }
  
  // Application de la limitation de courant
  analogWrite(redPin,   (r + m) * 255);
  analogWrite(greenPin, (g + m) * 255);
  analogWrite(bluePin,  (b + m) * 255);
}