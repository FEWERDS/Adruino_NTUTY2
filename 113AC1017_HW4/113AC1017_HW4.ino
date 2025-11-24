// HW: Button control LED on D3 with 3 blink speeds, cycle every press,
// 7th press returns to initial OFF state.

const int ledPin = 3;      // LED on D3
const int buttonPin = 2;   // Button on D2

// blink intervals (ms)
const unsigned long SLOW_INTERVAL = 1000;  // slow blink
const unsigned long MID_INTERVAL  = 500;   // medium blink
const unsigned long FAST_INTERVAL = 200;   // fast blink

// mode mapping for 0~6 presses (7 states total)
// 0: OFF
// 1: SLOW
// 2: MID
// 3: FAST
// 4: SLOW
// 5: MID
// 6: FAST
int mode = 0;  // current mode/state

// for blinking
bool ledState = false;
unsigned long lastBlinkMillis = 0;

// debounce
int lastButtonReading = HIGH;
int stableButtonState = HIGH;
unsigned long lastDebounceMillis = 0;
const unsigned long DEBOUNCE_DELAY = 50;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);  // pressed = LOW

  digitalWrite(ledPin, LOW); // initial OFF
  Serial.begin(9600);
}

unsigned long currentIntervalForMode(int m) {
  // return 0 for OFF, else corresponding interval
  if (m == 0) return 0;
  if (m == 1 || m == 4) return SLOW_INTERVAL;
  if (m == 2 || m == 5) return MID_INTERVAL;
  return FAST_INTERVAL; // m == 3 || m == 6
}

void loop() {
  // -------- Button with debounce --------
  int reading = digitalRead(buttonPin);

  if (reading != lastButtonReading) {
    lastDebounceMillis = millis(); // reset debounce timer
  }

  if ((millis() - lastDebounceMillis) > DEBOUNCE_DELAY) {
    // reading is stable
    if (reading != stableButtonState) {
      stableButtonState = reading;

      // detect press (HIGH -> LOW because pullup)
      if (stableButtonState == LOW) {
        mode = (mode + 1) % 7;  // 7 states cycle back to 0
        Serial.print("Mode = ");
        Serial.println(mode);

        // reset blink timing whenever mode changes
        lastBlinkMillis = millis();
        ledState = false;
        digitalWrite(ledPin, LOW);
      }
    }
  }

  lastButtonReading = reading;

  // -------- LED behavior (non-blocking) --------
  unsigned long interval = currentIntervalForMode(mode);

  if (interval == 0) {
    // OFF mode
    digitalWrite(ledPin, LOW);
    ledState = false;
    return;
  }

  // blink mode
  if (millis() - lastBlinkMillis >= interval) {
    lastBlinkMillis = millis();
    ledState = !ledState;
    digitalWrite(ledPin, ledState ? HIGH : LOW);
  }
}
