#define RX_PIN 3

#define RED_LED 8
#define YELLOW_LED 9
#define GREEN_LED 10

void setup() {
  pinMode(RX_PIN, INPUT);

  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  Serial.begin(9600);
  Serial.println("Receiver ready");

  // Initial normal state
  digitalWrite(RED_LED, HIGH);
}

void loop() {
  if (digitalRead(RX_PIN) == HIGH) {
    // Ambulance detected
    Serial.println("AMBULANCE DETECTED");

    // RED → YELLOW
    digitalWrite(RED_LED, LOW);
    digitalWrite(YELLOW_LED, HIGH);
    delay(2000);

    // YELLOW → GREEN
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);
    delay(10000); // ambulance pass time

    // GREEN → YELLOW
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(YELLOW_LED, HIGH);
    delay(2000);

    // Back to RED
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(RED_LED, HIGH);
  }
}
