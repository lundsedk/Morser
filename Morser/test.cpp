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

	/*
	char * testchar;
	char testbool;
	char charlen;
	for (int i = 0; i <= 128; ++i) {
		testchar = (char*)CHAR_TO_MORSE_BIN[(int)i];
		charlen = CHAR_LEN_IN_MORSE[i];
		cout << endl << i << " " << (char)i;
		if (testchar != NULL) {
			cout << "  " << ((testchar != NULL) ? testchar : "NULL  ") << endl;
			for (int j = 0; j < charlen; ++j) {
				testbool = testchar[j];
				//cout << testbool;
			}
		}
	}
	*/

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
	char* TestSenderAllAttrPtr;
	TestSender_.getAllAttrPtr(TestSenderAllAttrPtr);
	TestSender_.getAllAttrPtr(TestSenderAllAttrPtr);

	//*** add some test for nullptr from certain functions...

	menuCoord = { 0,8 };

	for (unsigned int i = 0; TestSenderAllAttrPtr[i] != 0; i++) {
		cout << "  0b" ;
		for (uint8_t j = 0; j < 8; j++) {
			cout << ((TestSenderAllAttrPtr[i] & (0b10000000 >> j)) ? '1' : '0');
		}
	}
	cout << "  0b00000000";

	cout << endl << endl << endl << "clear-test" <<endl;
	TestSender_.setMessage("test");
	TestSender_.getAllAttrPtr(TestSenderAllAttrPtr);

				for (unsigned int i = 0; i<50; i++) {
					cout << "  0b";
					for (uint8_t j = 0; j < 8; j++) {
						cout << ((TestSenderAllAttrPtr[i] & (0b10000000 >> j)) ? '1' : '0');
					}
				}
				cout << "  0b00000000";



	cout << endl << "Note that the first and last bytes are header and footer respectively (padded with 0s)." << endl << "The remaining bytes contain 10s or 01s, corresponding to 1 and 0 of the 3 settings, then the message," << endl;


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
