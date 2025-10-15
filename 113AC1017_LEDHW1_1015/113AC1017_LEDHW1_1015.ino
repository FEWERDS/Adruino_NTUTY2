const int pushButton = 2;
const int RledPin = 3;
const int GledPin = 4;
const int BledPin = 5;

int ledcolor = 0;
bool ButtonPressed = false;

//speed for fading <3
int fadeDelay = 5;   
int fadeStep  = 5;   

void setup() {
  pinMode(RledPin, OUTPUT);
  pinMode(GledPin, OUTPUT);
  pinMode(BledPin, OUTPUT);
  pinMode(pushButton, INPUT_PULLUP);
  Serial.begin(9600);
}

void fadeToColor(int rTarget, int gTarget, int bTarget) {
  static int rCurrent = 0, gCurrent = 0, bCurrent = 0;

  // Gradually move from current color → target color
  while (rCurrent != rTarget || gCurrent != gTarget || bCurrent != bTarget) {
    if (rCurrent < rTarget) rCurrent += fadeStep;
    else if (rCurrent > rTarget) rCurrent -= fadeStep;

    if (gCurrent < gTarget) gCurrent += fadeStep;
    else if (gCurrent > gTarget) gCurrent -= fadeStep;

    if (bCurrent < bTarget) bCurrent += fadeStep;
    else if (bCurrent > bTarget) bCurrent -= fadeStep;

    analogWrite(RledPin, rCurrent);
    analogWrite(GledPin, gCurrent);
    analogWrite(BledPin, bCurrent);

    delay(fadeDelay);
  }
}

void loop() {
  int buttonState = digitalRead(pushButton);

  if (buttonState == LOW && !ButtonPressed) {
    ledcolor++;
    if (ledcolor > 7) ledcolor = 0;
    ButtonPressed = true;
    Serial.print("Color changed to: ");
    Serial.println(ledcolor);
  }
  if (buttonState == HIGH && ButtonPressed) ButtonPressed = false;

  // Dthe color og target
  int r = 0, g = 0, b = 0;

  switch (ledcolor) {
    case 0: r = g = b = 0; break;           // off
    case 1: r = 255; g = b = 0; break;      // red
    case 2: g = 255; r = b = 0; break;      // green
    case 3: b = 255; r = g = 0; break;      // blue
    case 4: r = 255; g = 255; b = 0; break; // yellow
    case 5: r = 255; b = 255; g = 0; break; // purple
    case 6: g = 255; b = 255; r = 0; break; // cyan
    case 7: r = g = b = 255; break;         // white
  }

  fadeToColor(r, g, b);
}
