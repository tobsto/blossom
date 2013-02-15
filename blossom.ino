// enable motor pin
int enablePin = 3;
// input 1 pin
int inputPin1 = 6;
// input 2 pin
int inputPin2 = 9;

int input=0;
void setup()
{
	// Set enable pin to output mode
	pinMode(enablePin, OUTPUT);
	// Set input 1 pin to output mode
	pinMode(inputPin1, OUTPUT);
	// Set input 2 pin to output mode
	pinMode(inputPin2, OUTPUT);
	// set up serial communication
	Serial.begin(9600);
}
void loop()
{
	bool stopped=true;
	if (Serial.available()>0)
	{
		input=Serial.read() - '0';
		Serial.println(input);
		if (input==1)
		{
			// start if necessary
			if (stopped)
			{
				// switch on motor by enable pin
				digitalWrite(enablePin, HIGH);
			}
			// stop motor shortly
			digitalWrite(inputPin1, LOW);
			digitalWrite(inputPin2, LOW);
			delay(10);
			// start motor in one direction
			digitalWrite(inputPin1, LOW);
			digitalWrite(inputPin2, HIGH);
		}
		else if (input==2)
		{
			// start if necessary
			if (stopped)
			{
				// switch on motor by enable pin
				digitalWrite(enablePin, HIGH);
			}
			// stop motor shortly
			digitalWrite(inputPin1, LOW);
			digitalWrite(inputPin2, LOW);
			delay(10);
			// start motor in other direction
			digitalWrite(inputPin1, HIGH);
			digitalWrite(inputPin2, LOW);
		}
		else
		{
			// stop motor by switching og enable pin 
			digitalWrite(enablePin, LOW);
			stopped=true;
		}
	}
	delay(10);
}
