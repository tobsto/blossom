// enable motor pin
int enablePin = 3;
// input 1 pin
int inputPin1 = 6;
// input 2 pin
int inputPin2 = 9;


void runleft(int t)
{
	// start motor in left direction
	digitalWrite(inputPin1, LOW);
	digitalWrite(inputPin2, HIGH);
	// enable motor
	digitalWrite(enablePin, HIGH);
	delay(t);
}
void runright(int t)
{
	// start motor in right direction
	digitalWrite(inputPin1, HIGH);
	digitalWrite(inputPin2, LOW);
	// enable motor
	digitalWrite(enablePin, HIGH);
	delay(t);
}
void hold(int t)
{
	// stop motor
	digitalWrite(enablePin, LOW);
	delay(t);
}

bool run;
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
	// initial state is hold
	run=false;
}

void loop()
{
	// read input if available
	if (Serial.available()>0)
	{
		int input=Serial.read() - '0';
		Serial.println(input);
		if (input%2==0)
		{
			run=true;
		}
		else
		{
			run=false;
		}
	}
	if (run)
	{
		runleft(2000);
		hold(300);
		runright(2000);
		hold(300);
	}
}
