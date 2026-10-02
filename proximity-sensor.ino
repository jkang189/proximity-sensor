#include <LiquidCrystal.h>

// LCD Setup (RS=12, E=6, D4=5, D5=4, D6=3, D7=2)
LiquidCrystal lcd(12, 6, 5, 4, 3, 2);

// Sensor and Buzzer Pins
const int trigPin = 7;
const int echoPin = 8;
const int buzzerPin = 9;

void setup() {
  lcd.begin(16, 2);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  
  lcd.print("Proximity Alert");
  delay(1000);
  lcd.clear();
}

void loop() {
  // 1. Trigger the ultrasonic pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // 2. Read travel time and calculate distance in cm
  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;

  // 3. Update LCD and Buzzer based on distance
  lcd.setCursor(0, 0);
  lcd.print("Dist: ");
  lcd.print(distance);
  lcd.print("cm   "); // Extra spaces to clear old text

  lcd.setCursor(0, 1);

  if (distance > 0 && distance < 20) {
    // CLOSE ZONE
    lcd.print("Status: CLOSE   ");
    
    // Make beeping speed get faster as distance gets smaller
    // Constrain delay between 20ms (very fast) and 300ms (slow)
    int beepDelay = map(distance, 2, 20, 20, 300);
    beepDelay = constrain(beepDelay, 20, 300);
    
    digitalWrite(buzzerPin, HIGH);
    delay(beepDelay);
    digitalWrite(buzzerPin, LOW);
    delay(beepDelay);
    
  } else {
    // FAR ZONE
    lcd.print("Status: FAR     ");
    digitalWrite(buzzerPin, LOW);
    delay(100); // Standard refresh delay when clear
  }
}