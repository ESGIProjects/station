// Digit values to write character/nothing
#define OFF         -1
#define TEMPERATURE 10
#define HUMIDITY    11

// Pins used by the screen
#define d1    13
#define d2    10
#define d3    9
#define d4    7
#define segA  12
#define segB  8
#define segC  5
#define segD  3
#define segE  2
#define segF  11
#define segG  6
#define dot   4

// Digits displayed
int digit1 = OFF;
int digit2 = OFF;
int digit3 = OFF;
int digit4 = OFF;

// Global variables for receiving
char bytes[15];
int index = 0, incomingByte = 0;

void setup() {
  // Setting up pin mode for each
  pinMode(d1, OUTPUT);
  pinMode(d2, OUTPUT);
  pinMode(d3, OUTPUT);
  pinMode(d4, OUTPUT);
  pinMode(segA, OUTPUT);
  pinMode(segB, OUTPUT);
  pinMode(segC, OUTPUT);
  pinMode(segD, OUTPUT);
  pinMode(segE, OUTPUT);
  pinMode(segF, OUTPUT);
  pinMode(segG, OUTPUT);
  pinMode(dot, OUTPUT);

  // Init Serial connection
  Serial.begin(9600);
  Serial1.begin(9600);

  // Needed on Leonardo board
  while (!Serial) { }
  while (!Serial1) { }
}

void loop() {

  // Write digit to screen
  writeDigit(1, digit1, false);
  writeDigit(2, digit2, false);
  writeDigit(3, digit3, false);
  writeDigit(4, digit4, false);

  // Receive new data
  if (Serial1.available() > 0) {

	incomingByte = Serial1.read();
	bytes[index++] = incomingByte;

	// If the sequence is over, display the new data
	if (incomingByte == '\0') {
	  newData();
	  index = 0;
	}
  }
}

void selectScreen(int screen) {

  switch (screen) {
	case 1:
		digitalWrite(d1, LOW);
		digitalWrite(d2, HIGH);
		digitalWrite(d3, HIGH);
		digitalWrite(d4, HIGH);
		break;

	  case 2:
		digitalWrite(d1, HIGH);
		digitalWrite(d2, LOW);
		digitalWrite(d3, HIGH);
		digitalWrite(d4, HIGH);
		break;

	  case 3:
		digitalWrite(d1, HIGH);
		digitalWrite(d2, HIGH);
		digitalWrite(d3, LOW);
		digitalWrite(d4, HIGH);
		break;

	  case 4:
		digitalWrite(d1, HIGH);
		digitalWrite(d2, HIGH);
		digitalWrite(d3, HIGH);
		digitalWrite(d4, LOW);
		break;

	  default:
		break;
   }
}

void writeDigit(int screen, int digit, bool point) {

  // Check values before entering the switch
 if (screen < 1 || screen > 4) return;
 if (digit < -1 || digit > 11) return;

  // Select the screen
  selectScreen(screen);

  // Select which segment to turn on for each number
  switch (digit) {
	case -1: // screen off
	  digitalWrite(segA, LOW);
	  digitalWrite(segB, LOW);
	  digitalWrite(segC, LOW);
	  digitalWrite(segD, LOW);
	  digitalWrite(segE, LOW);
	  digitalWrite(segF, LOW);
	  digitalWrite(segG, LOW);
	  break;

	case 0: // A B C D E F
	  digitalWrite(segA, HIGH);
	  digitalWrite(segB, HIGH);
	  digitalWrite(segC, HIGH);
	  digitalWrite(segD, HIGH);
	  digitalWrite(segE, HIGH);
	  digitalWrite(segF, HIGH);
	  digitalWrite(segG, LOW);
	  break;

	case 1: // B C
	  digitalWrite(segA, LOW);
	  digitalWrite(segB, HIGH);
	  digitalWrite(segC, HIGH);
	  digitalWrite(segD, LOW);
	  digitalWrite(segE, LOW);
	  digitalWrite(segF, LOW);
	  digitalWrite(segG, LOW);
	  break;

	case 2: // A B D E G
	  digitalWrite(segA, HIGH);
	  digitalWrite(segB, HIGH);
	  digitalWrite(segC, LOW);
	  digitalWrite(segD, HIGH);
	  digitalWrite(segE, HIGH);
	  digitalWrite(segF, LOW);
	  digitalWrite(segG, HIGH);
	  break;

	case 3: // A B C D G
	  digitalWrite(segA, HIGH);
	  digitalWrite(segB, HIGH);
	  digitalWrite(segC, HIGH);
	  digitalWrite(segD, HIGH);
	  digitalWrite(segE, LOW);
	  digitalWrite(segF, LOW);
	  digitalWrite(segG, HIGH);
	  break;

	case 4: // B C F G
	  digitalWrite(segA, LOW);
	  digitalWrite(segB, HIGH);
	  digitalWrite(segC, HIGH);
	  digitalWrite(segD, LOW);
	  digitalWrite(segE, LOW);
	  digitalWrite(segF, HIGH);
	  digitalWrite(segG, HIGH);
	  break;

	case 5: // A C D F G
	  digitalWrite(segA, HIGH);
	  digitalWrite(segB, LOW);
	  digitalWrite(segC, HIGH);
	  digitalWrite(segD, HIGH);
	  digitalWrite(segE, LOW);
	  digitalWrite(segF, HIGH);
	  digitalWrite(segG, HIGH);
	  break;

	case 6: // A C D E F G
	  digitalWrite(segA, HIGH);
	  digitalWrite(segB, LOW);
	  digitalWrite(segC, HIGH);
	  digitalWrite(segD, HIGH);
	  digitalWrite(segE, HIGH);
	  digitalWrite(segF, HIGH);
	  digitalWrite(segG, HIGH);
	  break;

	case 7: // A B C
	  digitalWrite(segA, HIGH);
	  digitalWrite(segB, HIGH);
	  digitalWrite(segC, HIGH);
	  digitalWrite(segD, LOW);
	  digitalWrite(segE, LOW);
	  digitalWrite(segF, LOW);
	  digitalWrite(segG, LOW);
	  break;

	case 8: // A B C D E F G
	  digitalWrite(segA, HIGH);
	  digitalWrite(segB, HIGH);
	  digitalWrite(segC, HIGH);
	  digitalWrite(segD, HIGH);
	  digitalWrite(segE, HIGH);
	  digitalWrite(segF, HIGH);
	  digitalWrite(segG, HIGH);
	  break;

	case 9: // A B C D F G
	  digitalWrite(segA, HIGH);
	  digitalWrite(segB, HIGH);
	  digitalWrite(segC, HIGH);
	  digitalWrite(segD, HIGH);
	  digitalWrite(segE, LOW);
	  digitalWrite(segF, HIGH);
	  digitalWrite(segG, HIGH);
	  break;

	case TEMPERATURE: // A D E F
	  digitalWrite(segA, HIGH);
	  digitalWrite(segB, LOW);
	  digitalWrite(segC, LOW);
	  digitalWrite(segD, HIGH);
	  digitalWrite(segE, HIGH);
	  digitalWrite(segF, HIGH);
	  digitalWrite(segG, LOW);
	  break;

	  case HUMIDITY: // B C E F G
		digitalWrite(segA, LOW);
		digitalWrite(segB, HIGH);
		digitalWrite(segC, HIGH);
		digitalWrite(segD, LOW);
		digitalWrite(segE, HIGH);
		digitalWrite(segF, HIGH);
		digitalWrite(segG, HIGH);
		break;

	default:
	break;
  }

  // Control the dot for the current screen
  digitalWrite(dot, point ? HIGH : LOW);

  delay(1);
}

void newData() {
	  // Get the type of data received
	  char type = (char)bytes[0];

	  switch (type) {
		case 't':
		  // Display the temperature
		  digit1 = (int)bytes[1] - 48;
		  digit2 = (int)bytes[2] - 48;
		  digit3 = OFF;
		  digit4 = TEMPERATURE;
		  break;

		case 'h':
		 // Display the humidity value
		  digit1 = (int)bytes[1] - 48;
		  digit2 = (int)bytes[2] - 48;
		  digit3 = OFF;
		  digit4 = HUMIDITY;
		  break;

		case 'd':
		  // Display the date (not tested yet)
		  digit1 = (int)bytes[1] - 48;
		  digit2 = (int)bytes[2] - 48;
		  digit3 = (int)bytes[3] - 48;
		  digit4 = (int)bytes[4] - 48;
		  break;

		default:
		  break;
	  }
}
