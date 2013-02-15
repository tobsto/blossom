// enable motor pin
int enablePin = 3;
// input 1 pin
int inputPin1 = 6;
// input 2 pin
int inputPin2 = 9;
// analog input pin on the arduino for the proximity sensor 
int sensePin=0;
// maximal sensor value
int sense_max=410;
// minimal sensor value
int sense_min=20;
// threshold sensor value for people detection
int sense_boundary=100;
// check if someone is there
bool check=true;

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
	run=true;
}

bool someonethere()
{
	int distance=constrain(analogRead(sensePin), sense_min, sense_max);
	if (distance>sense_boundary)
	{
		Serial.println("Nobody there :-(");
		Serial.println(distance);
		return false;
	}
	else
	{
		Serial.println("Someone there!");
		Serial.println(distance);
		return true;
	}
}

void loop()
{
	if (check)
	{
		run=someonethere();
	}
	if (run)
	{
		runleft(5000);
		hold(1000);
		runright(5000);
		hold(1000);
	}
	else
	{
		delay(1000);
	}
}
