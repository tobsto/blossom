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
bool check=false;
// control by keyboard input
bool checkInput=true;
// manual control for testing purposes
bool manualControl=true;
// motor speed (0 to 255)
int motorSpeed=255;

void runleft(int t, int speed)
{
	// start motor in left direction
	digitalWrite(inputPin1, HIGH);
	digitalWrite(inputPin2, LOW);
	// enable motor with certain speed (PWM)
	analogWrite(enablePin, speed);
	delay(t);
}
void runright(int t, int speed)
{
	// start motor in right direction
	digitalWrite(inputPin1, LOW);
	digitalWrite(inputPin2, HIGH);
	// enable motor with certain speed (PWM)
	analogWrite(enablePin, speed);
	delay(t);
}
void hold(int t)
{
	// stop motor
	digitalWrite(enablePin, LOW);
	delay(t);
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

void checkSerialInput(bool & run)
{
	// read input if available
	if (Serial.available()>0)
	{
		int input=Serial.read() - '0';
		if (input%2==0)
		{
			Serial.println("Received hold command");
			run=false;
		}
		else
		{
			Serial.println("Received run command");
			run=true;
		}
	}
}
void readManualInput(int & inp)
{
	if (Serial.available()>0)
	{
		int input=Serial.read() - '0';
		if (input==1)
		{
			Serial.println("Received left run command");
			inp=1;
		}
		else if (input==2)
		{
			Serial.println("Received right run command");
			inp=2;
		}
		else
		{
			Serial.println("Received hold command");
			inp=0;
		}
	}
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

int inp=0;
void loop()
{
	if (manualControl)
	{
		int tstep=500;
		Serial.println("Check");
		readManualInput(inp);
		if (inp==1)
		{
			Serial.println("run left");
			runleft(tstep, motorSpeed);
		}
		else if (inp==2)
		{
			Serial.println("run right");
			runright(tstep, motorSpeed);
		}
		else
		{
			Serial.println("hold");
			hold(tstep);
		}
	}
	else
	{
		if (check)
		{
			run=someonethere();
		}
		if (checkInput)
		{
			checkSerialInput(run);
		}
		if (run)
		{
			Serial.println("Start cycle");
			runleft(25000, motorSpeed);
			hold(5000);
			runright(25000, motorSpeed);
			hold(5000);
		}
		else
		{
			Serial.println("hold");
			delay(1000);
		}
	}
}
