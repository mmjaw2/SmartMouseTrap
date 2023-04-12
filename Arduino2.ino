//
// Reset System code
//
// Code for the functionality of
// State LEDs and reset trap button
//
// By Mohamed Mjawaz
//

//
// Initalizing device pins
//
int RedLED = 4;
int GreLED = 3;
int Button = 7;

//
// Initalizing variables
//
int ButtonNew = 0;
int ButtonOld = 0;
int mouseCaught = 0;


void setup()
{
  Serial.begin(9600);
  // pinMode setup
  pinMode(RedLED, OUTPUT);
  pinMode(GreLED, OUTPUT);
  pinMode(Button, INPUT);
  digitalWrite(RedLED, HIGH);
}

void sendSignal(char outChar)
{
  Serial.write(outChar);
}

char recieveSignal()
{
  char inChar;

  // Reading in the message
  if(Serial.available() > 0){
    inChar = Serial.read();
  } else {
    inChar = '\0';
  }

  return inChar;
}

void loop()
{
  char inChar = recieveSignal();
  ButtonNew = digitalRead(Button);

  // runs when a signal was recieved
  // only recieves when mouse is caught
  if(inChar == 'a' && mouseCaught == 0){
    mouseCaught = 1;
    digitalWrite(GreLED, HIGH);
    digitalWrite(RedLED, LOW);
  }

  // runs when the button is pressed
  // and when a mouse was caught
  if(ButtonNew && !ButtonOld && mouseCaught){
  	digitalWrite(GreLED, LOW);
  	digitalWrite(RedLED, HIGH);
   	sendSignal('b');
  	mouseCaught = 0;
  }

  ButtonOld = ButtonNew;
}