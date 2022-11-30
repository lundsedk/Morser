#include "Morser.h"
#include <iostream>
#include <string>
#include <windows.h>
	//for delay for tester, and cursor movement

//this is just copied from online source...
void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO     cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

int main() {
	//testing addtwobits
	Morser newMorseTest;
		newMorseTest.myX10Mess_.addVibbleChar('a');
		newMorseTest.myX10Mess_.addVibbleChar('-');
		newMorseTest.myX10Mess_.addVibbleChar('.');
		newMorseTest.myX10Mess_.addVibbleNum(0b10000011);
		newMorseTest.myX10Mess_.addTwoBits(true);
		newMorseTest.myX10Mess_.addTwoBits(false);
		newMorseTest.myX10Mess_.addTwoBits(true);
		newMorseTest.myX10Mess_.addTwoBits(false);
		newMorseTest.myX10Mess_.addTwoBits(true);
		newMorseTest.myX10Mess_.addTwoBits(true);
		newMorseTest.myX10Mess_.addTwoBits(true);
		newMorseTest.myX10Mess_.addTwoBits(true);
		newMorseTest.myX10Mess_.addTwoBits(true);
		newMorseTest.myX10Mess_.addTwoBits(true);

		COORD menuCoord = { 0,0 };









	string userMessage;
	int userOn;
	int userOff;
	int userSpeed;
	cout << endl << "Enter message to send: ";
	getline(cin, userMessage);
	cout << "Enter On intensity (PWM signal strength when ON): ";
	cin >> userOn;
	cout << "Enter Off intensity (PWM signal strength when OFF): ";
	cin >> userOff;
	cout << "Enter speed (8 corresponds to 1 second, final speed is 8 seconds / speed entered): ";
	cin >> userSpeed;
	ShowConsoleCursor(false);




	
	//	Sender(string message, uint8_t onInt, uint8_t offInt, unsigned int speed, bool onOffmode, bool repeatmode);
	Morser TestSender_;
	TestSender_.setMessage(userMessage);
	TestSender_.setOnIntensity(userOn);
	TestSender_.setOffIntensity(userOff);
	TestSender_.setSpeed(userSpeed);
	const uint8_t* messPtr = nullptr;
	string tempOnIntensity;
	string tempOffIntensity;


	tempOnIntensity.insert(0, TestSender_.getOnIntensity_(), 178);
	tempOnIntensity.insert(TestSender_.getOnIntensity_(), 255, ' ');
	tempOffIntensity.insert(0, TestSender_.getOffIntensity_(), 178);
	tempOffIntensity.insert(TestSender_.getOffIntensity_(), 255, ' ');

	//run the important functions
	TestSender_.getMessageInMorse(messPtr);
	uint8_t* TestSenderAllAttrPtr;
	TestSender_.getAllAttrPtr(TestSenderAllAttrPtr);

	//*** add some test for nullptr from certain functions...

	menuCoord = { 0,8 };
	cout << endl << endl << "Results of genAllAttr (X10 signal handed off to menuas a pointer to int8_t array): " << endl;
	for (unsigned int i = 0; TestSenderAllAttrPtr[i] != 0; i++) {
		cout << "  0b" ;
		for (uint8_t j = 0; j < 8; j++) {
			cout << ((TestSenderAllAttrPtr[i] & (0b10000000 >> j)) ? '1' : '0');
		}
	}
	cout << "  0b00000000";
	cout << endl << "Note that the first and last bytes are header and footer respectively (padded with 0s)." << endl << "The remaining bytes contain 10s or 01s, corresponding to 1 and 0 of the 3 settings, then the message," << endl;

	//maybe also print the morseBin...

	uint16_t loopSpeed = 8000 / TestSender_.getSpeed();

	
		// Speed is between 0 and 31 as max, default value is 0b00010000 = 16 = 1 second per dit
		// so 31 is max speed - low milisec, and 1 is min speed, high milisec
		// and 16 speed_ should give 1000 millisec
			//	= (1000 / 16) * TestSender_.getSpeed()
		//move comments to speed func - help use
			//or, make a function that saves it or just converts it to milliseconds - future use
	uint32_t messtest18 = TestSender_.GetMessageInMorseLength();
	BBIndex<8> loopIndexEnd = { TestSender_.GetMessageInMorseLength() / 8, 0 };

	menuCoord = { 0,15 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), menuCoord);
	cout << "Results of morseBin (similar code will run on the PSoC):" << endl;
	cout << "Length of bar is current intensity (pwm signal)";
	menuCoord = { 0,18 };

	do {
		for (BBIndex<8> i = {0,0}; i < loopIndexEnd; i = i + BBIndex<8>(0, 1)) {
			//redo above with proper increments
			Sleep(loopSpeed);
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), menuCoord);
			if ( (messPtr[i.ByteIndex] & (0b00000001 << i.BitIndex) ) != 0b00000000) {
				cout << tempOnIntensity;
			} else {
				cout << tempOffIntensity;
			}
		}
	} while (true);

	return 0;
}




// old test

/*
	cout << "Testing morse funct:" << endl;
	for (int i = 'A'; i < 'Z'; i++) {
		cout << "   Char is: " << (char)i << "   In morse:" << CHAR_TO_MORSE[(int)i] << "   Length in morse:" << (int)CHAR_LEN_IN_MORSE[i] << endl << endl;
	}

	BBIndex testindex;
	testindex = { 5,2 };
	cout << "Testing BBIndex:" << endl;
	cout << "   Byteindex: " << testindex.ByteIndex << "   Bitindex:  " << (int) testindex.BitIndex << endl;
	cout << "Adding (0,4):" << endl;
	testindex = testindex + BBIndex(1, 10);
	cout << "   Byteindex: " << testindex.ByteIndex << "   Bitindex:  " << (int)testindex.BitIndex << endl;


	cout << "Non-equality of testindex BBIndex(0,5) and a for loop over BitIndex of another BBIndex" << endl;
	testindex = { 0,5 };
	bool equals = false;
	for (int i = 0; i < 10; i++) {
		equals = (testindex != BBIndex(0, i));
		cout << "Not equal to BBIndex (0," << i << "):   " << equals << endl;
	}
	cout << endl << endl;

	//BBIndex testing
		BBIndex<2> BinBBIndex(0,0);
		BBIndex<5> VibbleBBIndex(0, 1);
		BinBBIndex++;
		cout << "BinBBIndex size, byteindex, bitindex:  " << (int)BinBBIndex.ByteSizeVar << "  " << (int)BinBBIndex.ByteIndex << "  " << (int)BinBBIndex.BitIndex << endl;
		cout << "VibbleBBIndex size, byteindex, bitindex:  " << (int)VibbleBBIndex.ByteSizeVar << "  " << (int)VibbleBBIndex.ByteIndex << "  " << (int)VibbleBBIndex.BitIndex << endl;
		//cout << "compare bin and vibble:  " << ( (VibbleBBIndex == BinBBIndex) ? "True" : "False" ) << endl;
*/
