#define TRIG_PIN 9
#define ECHO_PIN 10
#define SIREN_SWITCH 2
#define TX_PIN 8

long duration;
int distance;

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(SIREN_SWITCH, INPUT_PULLUP); // switch to GND
  pinMode(TX_PIN, OUTPUT);

  Serial.begin(9600);
  Serial.println("Transmitter ready");
}

void loop() {
  // Check siren
  if (digitalRead(SIREN_SWITCH) == LOW) { // Siren ON
    // Ultrasonic trigger
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    duration = pulseIn(ECHO_PIN, HIGH);
    distance = duration * 0.034 / 2;

    Serial.print("Distance: ");
    Serial.println(distance);

    // 50 cm ≈ 500 meters (simulation)
    if (distance > 0 && distance <= 50) {
      digitalWrite(TX_PIN, HIGH); // send emergency signal
      Serial.println("AMBULANCE SIGNAL SENT");
    } else {
      digitalWrite(TX_PIN, LOW);
    }
  } else {
    digitalWrite(TX_PIN, LOW); // Siren OFF
  }

  delay(300);
}
