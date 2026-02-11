#include <LiquidCrystal.h>

// LCD Connections
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Pins
const int redPin = 10;
const int yellowPin = 9;
const int greenPin = 8;
const int buttonPin = 6;

void setup() {
  lcd.begin(16, 2);
  
  // *** IDHI NEW LINE (Serial Monitor start cheyadaniki) ***
  Serial.begin(9600); 

  pinMode(redPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  lcd.print("System Ready");
  Serial.println("System Ready"); // Serial Monitor lo chupistundi
  delay(1000);
  lcd.clear();
}

void loop() {
  normalTrafficCycle();
}

void normalTrafficCycle() {
  // GREEN
  digitalWrite(greenPin, HIGH);
  digitalWrite(yellowPin, LOW);
  digitalWrite(redPin, LOW);
  
  lcd.clear();
  lcd.print("Traffic: GO");
  Serial.println("Traffic: GO"); // Serial Monitor Message
  
  if (smartDelay(5000)) return; 

  // YELLOW
  digitalWrite(greenPin, LOW);
  digitalWrite(yellowPin, HIGH);
  digitalWrite(redPin, LOW);
  
  lcd.setCursor(0, 0);
  lcd.print("Traffic: SLOW");
  Serial.println("Traffic: SLOW"); // Serial Monitor Message
  
  if (smartDelay(2000)) return;

  // RED
  digitalWrite(greenPin, LOW);
  digitalWrite(yellowPin, LOW);
  digitalWrite(redPin, HIGH);
  
  lcd.setCursor(0, 0);
  lcd.print("Traffic: STOP");
  Serial.println("Traffic: STOP"); // Serial Monitor Message
  
  if (smartDelay(5000)) return;
}

bool smartDelay(int waitTime) {
  int steps = waitTime / 10;
  for (int i = 0; i < steps; i++) {
    if (digitalRead(buttonPin) == LOW) {
      emergencyMode();
      return true;
    }
    delay(10);
  }
  return false;
}

void emergencyMode() {
  lcd.clear();
  lcd.print("AMBULANCE !!!");
  Serial.println("AMBULANCE !!!"); // Serial Monitor Message
  
  lcd.setCursor(0, 1);
  lcd.print("Clearing Road...");
  
  digitalWrite(redPin, LOW);
  digitalWrite(yellowPin, LOW);
  digitalWrite(greenPin, HIGH);
  
  delay(10000); // 10 Seconds Wait
  
  lcd.clear();
  lcd.print("Resuming...");
  Serial.println("Resuming Normal Traffic...");
  delay(1000);
}
