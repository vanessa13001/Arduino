#include <LiquidCrystal.h>

// Configuration des broches (vérifiez vos branchements)
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Variables pour l'heure
int h = 11, m = 34, s = 0;
unsigned long previousMillis = 0;
const long interval = 1000; // Intervalle d'1 seconde (1000 ms)

void setup() {
  // Initialisation du LCD
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("Initialisation...");
  delay(1000);
  lcd.clear();
  lcd.print("Heure actuelle:");
}

void loop() {
  // Obtenir l'heure actuelle toutes les secondes
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis; // Enregistrer le temps actuel
    s++; // Incrémenter les secondes

    // Gestion du débordement temps
    if (s >= 60) {
      s = 0;
      m++; // Incrémenter les minutes
    }
    if (m >= 60) {
      m = 0;
      h++; // Incrémenter les heures
    }
    if (h >= 24) {
      h = 0; // Réinitialiser à 0 si l'heure atteint 24
    }

    // Affichage du temps sur le LCD (format HH:MM:SS)
    lcd.setCursor(0, 1);
    if (h < 10) lcd.print("0");
    lcd.print(h);
    lcd.print(":");
    if (m < 10) lcd.print("0");
    lcd.print(m);
    lcd.print(":");
    if (s < 10) lcd.print("0");
    lcd.print(s);
  }
}
