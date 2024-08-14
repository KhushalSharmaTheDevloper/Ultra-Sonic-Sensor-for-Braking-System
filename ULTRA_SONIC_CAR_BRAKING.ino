#define trigpin 8
#define echopin 9
#define LED 13
bool sensorActive = false;  // Flag to control the sensor's activity

void setup() {
  Serial.begin(9600);
  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);
  pinMode(LED, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    int command = Serial.read();  // Read the incoming data

    if (command == '1') {  // Check if the command is '1'
      sensorActive = !sensorActive;  // Toggle the sensor's active state
      if (sensorActive) {
        Serial.println("Sensor Activated");
        digitalWrite(LED, HIGH);
      } else {
        Serial.println("Sensor Deactivated");
        digitalWrite(LED, LOW);
      }
      delay(500);  // Delay to prevent bouncing issues
    }
  }

  if (sensorActive) {
    long distance, duration;
    digitalWrite(trigpin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigpin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigpin, LOW);

    duration = pulseIn(echopin, HIGH);
    distance = (duration / 2) / 29.1;

    if (distance >= 100) {
      Serial.println("Driving");
    } else if (distance >= 50 && distance < 100) {
      Serial.println("Braking Lightly");
    } else if (distance < 50) {
      Serial.println("Braked.");
      delay(5000);  // Wait for 5 seconds before continuing
    }
    
    delay(500);
  }
}
