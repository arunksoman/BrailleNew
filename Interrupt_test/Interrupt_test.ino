#define timeSeconds 5

// Set GPIOs for LED and PIR Motion Sensor
const int send_PIN = 18;
const int FINGER1 = 19;
const int FINGER2 = 21;
const int FINGER3 = 22; 
String left_hand_fingers = "";
// Timer: Auxiliary variables
unsigned long now = millis();
unsigned long lastTrigger = 0;
boolean startTimer = false;

// Checks if motion was detected, sets LED HIGH and starts a timer
void IRAM_ATTR sendClick() {
  Serial.println("I am Here!!!");
  startTimer = true;
  lastTrigger = millis();
  left_hand_fingers = "";
  left_hand_fingers = left_hand_fingers + String(digitalRead(FINGER1));
  left_hand_fingers = left_hand_fingers + digitalRead(FINGER2);
  left_hand_fingers = left_hand_fingers + digitalRead(FINGER3);
  Serial.printf("Readed fingers = %s", left_hand_fingers);
}

void setup() {
  // Serial port for debugging purposes
  Serial.begin(115200);
  
  // PIR Motion Sensor mode INPUT_PULLUP
  pinMode(send_PIN, INPUT_PULLUP);
  pinMode(FINGER1, INPUT);
  pinMode(FINGER2, INPUT);
  pinMode(FINGER3, INPUT);
  // Set motionSensor pin as interrupt, assign interrupt function and set RISING mode
  attachInterrupt(digitalPinToInterrupt(send_PIN), sendClick, FALLING);
}

void loop() {
  // Current time
  now = millis();
  // Turn off the LED after the number of seconds defined in the timeSeconds variable
  if(startTimer && (now - lastTrigger > (timeSeconds*1000))) {
    Serial.println("Not Here");
    startTimer = false;
    left_hand_fingers = "";
  }
}
