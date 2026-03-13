#include <LiquidCrystal.h>

// LCD setup
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// LED pins
const int redPin = 10;
const int yellowPin = 9;
const int greenPin = 8;

// Ultrasonic pins
const int trigPin = 7;
const int echoPin = 6;

// Timing constants (in milliseconds)
const int GREEN_DURATION = 5000;
const int YELLOW_DURATION = 2000;
const int RED_DURATION = 5000;
const int EMERGENCY_CROSSING_TIME = 10000;
const int EMERGENCY_WARNING_TIME = 2000;
const int NORMAL_RESET_TIME = 1500;

// Ultrasonic constants
const int MIN_DETECTION_DISTANCE = 5;   // Minimum distance to ignore noise (cm)
const int MAX_DETECTION_DISTANCE = 50;  // Maximum detection range (cm)
const int CONFIRMATION_READINGS = 3;    // Number of readings to confirm emergency

void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);

  pinMode(redPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(greenPin, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Initial display
  lcd.print("SMART TRAFFIC");
  lcd.setCursor(0, 1);
  lcd.print("SYSTEM READY");
  
  Serial.println("=================================");
  Serial.println("SMART TRAFFIC SYSTEM INITIALIZED");
  Serial.println("=================================");
  Serial.println();
  
  delay(2000);
  lcd.clear();
}

void loop() {
  normalTraffic();
}

// ================= DISTANCE FUNCTION =================
long getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  
  // Calculate distance in cm
  long distance = duration * 0.034 / 2;
  
  return distance;
}

// ================= COUNTDOWN DISPLAY FUNCTION =================
void displayCountdown(String phase, int totalSeconds, int secondsLeft) {
  Serial.print("[");
  Serial.print(phase);
  Serial.print("] Time remaining: ");
  Serial.print(secondsLeft);
  Serial.println(" seconds");
}

// ================= EMERGENCY CHECK WITH CONFIRMATION =================
bool checkEmergency(int duration, String phaseName) {
  unsigned long startTime = millis();
  int totalSeconds = duration / 1000;
  int lastSecond = -1;
  
  Serial.println("---------------------------------");
  Serial.print("STARTING ");
  Serial.print(phaseName);
  Serial.print(" PHASE - Duration: ");
  Serial.print(totalSeconds);
  Serial.println(" seconds");
  Serial.println("---------------------------------");
  
  while (millis() - startTime < duration) {
    // Calculate remaining seconds
    int elapsedSeconds = (millis() - startTime) / 1000;
    int secondsLeft = totalSeconds - elapsedSeconds;
    
    // Display countdown every second
    if (secondsLeft != lastSecond) {
      displayCountdown(phaseName, totalSeconds, secondsLeft);
      lastSecond = secondsLeft;
    }
    
    long distance = getDistance();
    
    // Check if object is within detection range (ignoring noise)
    if (distance > MIN_DETECTION_DISTANCE && distance < MAX_DETECTION_DISTANCE) {
      
      Serial.print("!!! Potential emergency vehicle detected! Distance: ");
      Serial.print(distance);
      Serial.println(" cm");
      Serial.print("Confirming detection...");
      
      // Confirm with multiple readings to avoid false triggers
      int confirmCount = 1;  // Start with 1 for current detection
      
      for (int i = 1; i < CONFIRMATION_READINGS; i++) {
        delay(50);  // Small delay between readings
        long confirmDistance = getDistance();
        
        if (confirmDistance > MIN_DETECTION_DISTANCE && confirmDistance < MAX_DETECTION_DISTANCE) {
          confirmCount++;
        }
      }
      
      Serial.print(" Confirmation count: ");
      Serial.print(confirmCount);
      Serial.print("/");
      Serial.println(CONFIRMATION_READINGS);
      
      // If enough confirmations, trigger emergency mode
      if (confirmCount >= 2) {  // At least 2 out of 3 readings confirm
        Serial.println("!!! EMERGENCY CONFIRMED - Switching to emergency mode !!!");
        emergencyMode();
        return true;
      } else {
        Serial.println("False alarm - continuing normal operation");
      }
    }
    
    delay(50);  // Small delay between detection attempts
  }
  
  Serial.print(phaseName);
  Serial.println(" PHASE COMPLETED");
  Serial.println();
  
  return false;
}

// ================= NORMAL TRAFFIC =================
void normalTraffic() {
  
  // GREEN - Go
  digitalWrite(greenPin, HIGH);
  digitalWrite(yellowPin, LOW);
  digitalWrite(redPin, LOW);

  lcd.clear();
  lcd.print("TRAFFIC : GO");
  lcd.setCursor(0, 1);
  lcd.print("GREEN");

  if (checkEmergency(GREEN_DURATION, "GREEN")) return;

  // YELLOW - Prepare to stop
  digitalWrite(greenPin, LOW);
  digitalWrite(yellowPin, HIGH);

  lcd.clear();
  lcd.print("TRAFFIC : WAIT");
  lcd.setCursor(0, 1);
  lcd.print("YELLOW");

  if (checkEmergency(YELLOW_DURATION, "YELLOW")) return;

  // RED - Stop
  digitalWrite(yellowPin, LOW);
  digitalWrite(redPin, HIGH);

  lcd.clear();
  lcd.print("TRAFFIC : STOP");
  lcd.setCursor(0, 1);
  lcd.print("RED");

  if (checkEmergency(RED_DURATION, "RED")) return;

  // YELLOW - Prepare to go
  digitalWrite(redPin, LOW);
  digitalWrite(yellowPin, HIGH);

  lcd.clear();
  lcd.print("READY TO GO");
  lcd.setCursor(0, 1);
  lcd.print("GET READY");

  if (checkEmergency(YELLOW_DURATION, "YELLOW (PRE-GREEN)")) return;

  digitalWrite(yellowPin, LOW);
}

// ================= EMERGENCY MODE =================
void emergencyMode() {
  
  Serial.println("\n*** EMERGENCY MODE ACTIVATED ***");
  Serial.println("=================================");

  // Log to serial monitor
  Serial.print("Initial detection distance: ");
  Serial.print(getDistance());
  Serial.println(" cm");

  // Update LCD display
  lcd.clear();
  lcd.print("EMERGENCY!");
  lcd.setCursor(0, 1);
  lcd.print("CLEARING ROAD");

  // Turn off green if it was on
  digitalWrite(greenPin, LOW);

  // Yellow warning - alert other drivers
  digitalWrite(yellowPin, HIGH);
  digitalWrite(redPin, LOW);
  
  Serial.println("\n--- WARNING PHASE ---");
  for (int i = EMERGENCY_WARNING_TIME/1000; i > 0; i--) {
    Serial.print("Warning: ");
    Serial.print(i);
    Serial.println(" seconds remaining");
    delay(1000);
  }
  Serial.println("Warning phase complete\n");

  // Priority green for emergency vehicle
  digitalWrite(yellowPin, LOW);
  digitalWrite(greenPin, HIGH);

  lcd.clear();
  lcd.print("PRIORITY GREEN");
  lcd.setCursor(0, 1);
  lcd.print("AMBULANCE GO");

  Serial.println("--- PRIORITY GREEN PHASE (Ambulance Passing) ---");
  for (int i = EMERGENCY_CROSSING_TIME/1000; i > 0; i--) {
    Serial.print("Priority green: ");
    Serial.print(i);
    Serial.println(" seconds remaining");
    delay(1000);
  }
  Serial.println("Priority green phase complete\n");

  // Safe return to normal operation
  digitalWrite(greenPin, LOW);
  digitalWrite(yellowPin, HIGH);

  lcd.clear();
  lcd.print("RETURN TO");
  lcd.setCursor(0, 1);
  lcd.print("NORMAL MODE");

  Serial.println("--- RETURN TO NORMAL PHASE ---");
  for (int i = EMERGENCY_WARNING_TIME/1000; i > 0; i--) {
    Serial.print("Returning to normal: ");
    Serial.print(i);
    Serial.println(" seconds remaining");
    delay(1000);
  }
  Serial.println("Return phase complete\n");

  // Start with red when returning to normal
  digitalWrite(yellowPin, LOW);
  digitalWrite(redPin, HIGH);

  lcd.clear();
  lcd.print("NORMAL MODE");
  lcd.setCursor(0, 1);
  lcd.print("SYSTEM RESET");

  Serial.println("--- SYSTEM RESET PHASE ---");
  for (int i = NORMAL_RESET_TIME/1000; i > 0; i--) {
    Serial.print("System reset: ");
    Serial.print(i);
    Serial.println(" seconds remaining");
    delay(1000);
  }
  
  // Clear LCD for next cycle
  lcd.clear();
  
  Serial.println("=================================");
  Serial.println("EMERGENCY MODE COMPLETED");
  Serial.println("Returning to normal traffic cycle");
  Serial.println("=================================\n");
}

// ================= ADDITIONAL HELPER FUNCTIONS =================

// Function to test ultrasonic sensor
void testSensor() {
  long distance = getDistance();
  
  lcd.clear();
  lcd.print("Distance Test");
  lcd.setCursor(0, 1);
  lcd.print(distance);
  lcd.print(" cm");
  
  Serial.print("Test Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  delay(500);
}
