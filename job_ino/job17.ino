#include <LiquidCrystal.h>

// Initialisation de l'écran LCD
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

// Variables pour les temps
unsigned int hours = 0;
unsigned int minutes = 0;
unsigned int seconds = 0;

// Boutons
const int resetButton = A2;
const int startPauseButton = A1;

// États
bool running = false;
unsigned long previousMillis = 0;

// Pour gérer les changements d’état du bouton
int lastStartPauseState = HIGH;
int lastResetState = HIGH;

void setup() {
  pinMode(resetButton, INPUT_PULLUP);
  pinMode(startPauseButton, INPUT_PULLUP);

  lcd.begin(16, 2);
  lcd.setCursor(2, 0);
  lcd.print("wsh gros");
  displayTime();
}

void loop() {
  // Lecture des boutons
  int currentStartPauseState = digitalRead(startPauseButton);
  int currentResetState = digitalRead(resetButton);

  // Start / Pause
  if (currentStartPauseState == LOW && lastStartPauseState == HIGH) {
    running = !running;
    previousMillis = millis(); // reset le timer au moment du start
    delay(200);
  }
  lastStartPauseState = currentStartPauseState;

  // Reset
  if (currentResetState == LOW && lastResetState == HIGH) {
    running = false;
    hours = minutes = seconds = 0;
    displayTime();
    delay(200);
  }
  lastResetState = currentResetState;

  // Mise à jour du chrono chaque seconde
  if (running && millis() - previousMillis >= 1000) {
    previousMillis += 1000;
    seconds++;

    if (seconds >= 60) {
      seconds = 0;
      minutes++;
    }
    if (minutes >= 60) {
      minutes = 0;
      hours++;
    }

    displayTime();
  }
}

void displayTime() {
  lcd.setCursor(0, 1);
  if (hours < 10) lcd.print("0");
  lcd.print(hours);
  lcd.print(":");

  if (minutes < 10) lcd.print("0");
  lcd.print(minutes);
  lcd.print(":");

  if (seconds < 10) lcd.print("0");
  lcd.print(seconds);
  lcd.print("  "); // petit padding pour effacer les chiffres restants s'il y en avait
}
