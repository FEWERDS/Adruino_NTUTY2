const int buttonPin = 2;

const int RLedPin = 9;
const int GLedPin = 10;
const int BLedPin = 11;

int buttonState = 0;
bool buttonPressed = false;
unsigned long pressingTime = 0;
const int longPressInterval = 2000;

int lightNum = 0;
// The Current Light Stick Color
int RLightColor = 0;
int GLightColor = 0;
int BLightColor = 0;

int RCurrentColor = 0;
int GCurrentColor = 0;
int BCurrentColor = 0;

int currentMode = 0;
unsigned long blinkTimer = 0;
const int blinkInterval = 500;
bool blinkOn = true;
const int fadeAmount = 2;
int fadeDirection = 1;

void setup() 
{
  // put your setup code here, to run once:
  pinMode(buttonPin, INPUT);
  pinMode(RLedPin, OUTPUT);
  pinMode(GLedPin, OUTPUT);
  pinMode(BLedPin, OUTPUT);
  Serial.begin(9600);
}

void loop() 
  {
    checkButton();
    updateLEDColor();
    setRGBLEDColor(RCurrentColor, GCurrentColor, BCurrentColor);
  }
  
void checkButton() {
  buttonState = digitalRead(buttonPin);

if(buttonState == LOW && !buttonPressed){
    pressingTime = millis();
    buttonPressed = true;
  }
  
  if(buttonState == HIGH && buttonPressed){
    unsigned long currentTime = millis();
    if(currentTime - pressingTime < longPressInterval){
      //short click
      changeLEDColor();
      //Serial.println("short click");
    }
    else{
      //long press
      changeMode();
      //Serial.println("long click");
    }
    buttonPressed = false;
  }
}

void changeLEDColor(){
  // Increase the light number
  lightNum = lightNum + 1;
  if(lightNum >= 5){
    lightNum = 0;
  }

  // Set the RGB Light Color according to lightNum
  if(lightNum == 0){
    // white
    RLightColor = 0;
    GLightColor = 0;
    BLightColor = 0;
  }

  if(lightNum == 1){
    // red
    RLightColor = 0;
    GLightColor = 255;
    BLightColor = 255;
  }

  if(lightNum == 2){
    // blue
    RLightColor = 255;
    GLightColor = 0;
    BLightColor = 255;
  }

  if(lightNum == 3){
    // green
    RLightColor = 255;
    GLightColor = 255;
    BLightColor = 0;
  }

  if(lightNum == 4){
    // yellow
    RLightColor = 0;
    GLightColor = 0;
    BLightColor = 255;
  }

  RCurrentColor = RLightColor;
  GCurrentColor = GLightColor;
  BCurrentColor = BLightColor;
}

void changeMode(){
  currentMode = currentMode + 1;
  if(currentMode >= 3){
    currentMode = 0;
  }
  if(currentMode == 1){
    blinkTimer = 0;
    blinkOn = true;
  }
  if(currentMode == 2){
    fadeDirection = 1;
  }
}


void updateLEDColor(){
  if(currentMode == 0){
    // Constant Light Mode
    RCurrentColor = RLightColor;
    GCurrentColor = GLightColor;
    BCurrentColor = BLightColor;
  }

  else if(currentMode == 1){
    // Blink Mode
    unsigned long currentTime = millis();
    if(currentTime - blinkTimer > blinkInterval){
      blinkOn = !blinkOn;
      blinkTimer = currentTime;
    }

    if(blinkOn){
      RCurrentColor = RLightColor;
      GCurrentColor = GLightColor;
      BCurrentColor = BLightColor;
    } else {
      RCurrentColor = 255;
      GCurrentColor = 255;
      BCurrentColor = 255;
    }
  }


  else if(currentMode == 2){
      bool negativeDir = false;

    // Red channel
      if(RLightColor == 0){
      RCurrentColor = RCurrentColor + fadeDirection * fadeAmount;
      if((RCurrentColor > 255 - RLightColor) || (RCurrentColor < 0)){
        negativeDir = true;
      }
      if(GCurrentColor < 0) GCurrentColor = 0;
      if(GCurrentColor > 255) GCurrentColor = 255;
      }
    // Green channel
    if(GLightColor == 0){
      GCurrentColor = GCurrentColor + fadeDirection * fadeAmount;
      if((GCurrentColor > 255 - GLightColor) || (GCurrentColor < 0)){
        negativeDir = true;
      }
      if(GCurrentColor < 0) GCurrentColor = 0;
      if(GCurrentColor > 255) GCurrentColor = 255;
    }

    // Blue channel
    if(BLightColor == 0){
      BCurrentColor = BCurrentColor + fadeDirection * fadeAmount;
      if((BCurrentColor > 255 - BLightColor) || (BCurrentColor < 0)){
        negativeDir = true;
      }
      if(BCurrentColor < 0) BCurrentColor = 0;
      if(BCurrentColor > 255) BCurrentColor = 255;
    }

    if(negativeDir)
      fadeDirection = -fadeDirection;

    delay(10);
    // Breathing Light Mode
  }
}

void setRGBLEDColor(int r, int g, int b){
  analogWrite(RLedPin, r);
  analogWrite(GLedPin, g);
  analogWrite(BLedPin, b);
}




