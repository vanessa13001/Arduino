#include <LiquidCrystal.h>

// LCD: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

// Boutons
const int resetButton = A2;
const int startPauseButton = A1;

bool running = false;
unsigned long previousMillis = 0;
int progress = 0; // 0 à 80 (16 colonnes * 5 niveaux)

// États des boutons
int lastStartPauseState = HIGH;
int lastResetState = HIGH;

// Caractères personnalisés (1 à 5 pixels remplis)
byte blocks[5][8] = {
  { B10000, B10000, B10000, B10000, B10000, B10000, B10000, B10000 }, // 1/5
  { B11000, B11000, B11000, B11000, B11000, B11000, B11000, B11000 }, // 2/5
  { B11100, B11100, B11100, B11100, B11100, B11100, B11100, B11100 }, // 3/5
  { B11110, B11110, B11110, B11110, B11110, B11110, B11110, B11110 }, // 4/5
  { B11111, B11111, B11111, B11111, B11111, B11111, B11111, B11111 }  // 5/5 (plein)
};

void setup() {
  pinMode(resetButton, INPUT_PULLUP);
  pinMode(startPauseButton, INPUT_PULLUP);

  lcd.begin(16, 2);

  // Création des caractères spéciaux
  for (int i = 0; i < 5; i++) {
    lcd.createChar(i, blocks[i]);
  }

  lcd.setCursor(0, 0);
  lcd.print("salutation...");
  displayProgressBar();
}

void loop() {
  int currentStartPauseState = digitalRead(startPauseButton);
  int currentResetState = digitalRead(resetButton);

  if (currentStartPauseState == LOW && lastStartPauseState == HIGH) {
    running = !running;
    previousMillis = millis();
    delay(200);
  }
  lastStartPauseState = currentStartPauseState;

  if (currentResetState == LOW && lastResetState == HIGH) {
    running = false;
    progress = 0;
    displayProgressBar();
    delay(200);
  }
  lastResetState = currentResetState;

  if (running && millis() - previousMillis >= 200) { // vitesse de progression
    previousMillis += 200;

    if (progress < 80) { // 16 colonnes * 5 niveaux = 80
      progress++;
      displayProgressBar();
    }
  }
}

void displayProgressBar() {
  lcd.setCursor(0, 1);
  int fullBlocks = progress / 5;         // Nombre de blocs pleins
  int remainder = progress % 5;          // Niveau partiel (0 à 4)

  for (int i = 0; i < 16; i++) {
    if (i < fullBlocks) {
      lcd.write(byte(4)); // bloc plein (5/5)
    } else if (i == fullBlocks && remainder > 0) {
      lcd.write(byte(remainder - 1)); // bloc partiel
    } else {
      lcd.print(" "); // vide
    }
  }