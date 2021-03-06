// 1-button interface
// 1 momentary switch, 1 breadboard, hook-up wires, 1 10kOhm resistor
// Button connected to 5V & pin 2 with jumpers
// Button connected to GND with 10kOhm resistor
// For a schematic of the wiring visit https://www.arduino.cc/en/Tutorial/Button 

// constants won't change. They're used here to set pin numbers:
const int buttonPin = 2;    // the number of the pushbutton pin

// Variables will change:
boolean moveMe = 0;         // the current state of the output pin
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

void setup() {
  Serial.begin(9600);

  pinMode(buttonPin, INPUT);

}

void loop() {
  // read the state of the switch into a local variable:
  int reading = digitalRead(buttonPin);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle if the new button state is HIGH
      if (buttonState == HIGH) {
        moveMe = !moveMe;
      }
    }
  }

  // send the signal via Serial
  Serial.println(moveMe);

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;
}
