
#define TRI_RED 13
#define TRI_YELLOW 12
#define TRI_GREEN 11
#define BUTTON 6
#define LED_RED 5
#define LED_YELLOW 4
#define LED_GREEN 3
#define POTENTIAL_PIN A0



// Variable to store the values read by the potentiometer and send to the pins
int potVal = 0;
int redVal = 0;
int grnVal = 0;
int yelVal = 0;

void setup() {


  Serial.begin(9600);
  Serial.setTimeout(10);

  // Setting the components as input/output
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(BUTTON, INPUT);
  pinMode(POTENTIAL_PIN, INPUT);
  pinMode(TRI_RED, OUTPUT);
  pinMode(TRI_GREEN, OUTPUT);
  pinMode(TRI_YELLOW, OUTPUT);

  // Showing the user possible combinations of LED they can light up and asking them to input a choice
  Serial.println("Here are combinations of LEDs:");
  Serial.println("Combo 1: RED, GREEN, YELLOW");
  Serial.println("Combo 2: RED, GREEN");
  Serial.println("Type the number of the combination of LEDs you want to light up: ");
}



void loop() {

  // Defining a variable to store the user input (combo number)
  int ledCombo = 0;

  // Prints the user input if a number is typed
  if (Serial.available() > 0) {
    ledCombo = Serial.parseInt();
    Serial.print("Combo: ");
    Serial.println(ledCombo);
  }

  if (ledCombo == 1) {  // If the user chooses combo 1, all three LEDs will light up for 3 seconds
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_YELLOW, HIGH);
    delay(3000);
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_YELLOW, LOW);
    delay(1000);
  } else if (ledCombo == 2) {  // If the user chooses combo 2, only the red and the green LEDs will light up for 3 seconds
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_GREEN, HIGH);
    delay(3000);
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_GREEN, LOW);
    delay(1000);
  }

  // Defining a variable to store the users input (how many times they want the a LED to flash)
  int flashNumber = 0;

  if (digitalRead(BUTTON) == 1) {  // If button is pressed and held, the user is asked to input how many times they want the green LED to flash
    Serial.println("How many times do you want the green LED to flash?");
    delay(3000);
    if (Serial.available() > 0) {
      flashNumber = Serial.parseInt();
      Serial.println("Number of green flashes: ");
      Serial.println(flashNumber);  // Prints the user's input number
      for (int i = 0; i < flashNumber; i++) {
        digitalWrite(LED_GREEN, HIGH);  // The green LED flashes for 0.2 seconds each time
        delay(200);
        digitalWrite(LED_GREEN, LOW);
        delay(200);
      }
    }
  }

  {
    potVal = analogRead(POTENTIAL_PIN);  // read the potentiometer value at the input pin

    if (potVal < 341)  // Lowest third of the potentiometer's range (0-340)
    {
      potVal = (potVal * 3) / 4;  // Normalize to 0-255

      redVal = 256 - potVal;  // Red from full to off
      grnVal = potVal;        // Green from off to full
      yelVal = 1;             // Yellow off
    } else if (potVal < 682)  // Middle third of potentiometer's range (341-681)
    {
      potVal = ((potVal - 341) * 3) / 4;  // Normalize to 0-255

      redVal = 1;             // Red off
      grnVal = 256 - potVal;  // Green from full to off
      yelVal = potVal;        // Yellow from off to full
    } else                    // Upper third of potentiometer"s range (682-1023)
    {
      potVal = ((potVal - 683) * 3) / 4;  // Normalize to 0-255

      redVal = potVal;        // Red from off to full
      grnVal = 1;             // Green off
      yelVal = 256 - potVal;  // Yellow from full to off
    }

    analogWrite(TRI_RED, redVal);  // Write values to LED pins
    analogWrite(TRI_GREEN, grnVal);
    analogWrite(TRI_YELLOW, yelVal);
  }

} 
