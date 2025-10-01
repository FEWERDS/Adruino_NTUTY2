void setup() {
  // initialize digital pin as an output.
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
}
// the loop function runs over and over again forever
void loop() {
  digitalWrite(3, LOW);// turn the RED LED on
  delay(200);// wait for a second
digitalWrite(4, LOW);// turn the GREEN LED on
  digitalWrite(5, LOW);// turn the GREEN LED on
    delay(200);// wait for a second
  digitalWrite(3, HIGH);// turn the RED LED off
  digitalWrite(5, HIGH);// turn the GREEN LED off
  delay(200);// wait for a second
   digitalWrite(4, HIGH);// turn the GREEN LED off
     digitalWrite(5, LOW);// turn the GREEN LED on

}
