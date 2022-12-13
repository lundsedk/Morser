#include <vector>
#pragma once

using namespace std;

class X10Mess
{
public:
	X10Mess();													// Constructor
	void addVibbleNum(uint8_t newchar);							// Skriver 5 (komplementære) bits til X10Contents_
	void addVibbleChar(uint8_t newchar);						// Konverterer en char til rette 5 bits, og skriver dem til X10Contents_
	void addHeader();											// Lægger rette header (0b00001110) til X10Contents_
	void addFooter();											// Lægger rette footer (0b00000000) til X10Contents_
	void getX10ContentsPtr(char *& X10ContentsPtr);				// Opdaterer parameter med reference til char arrayet indeholdt i X10Contents_
private:
	vector<char> X10Contents_;									// Indeholder X10 besked
	void addTwoBits(bool conditional);							// Skriver 10 eller 01 til X10Contents_
	uint8_t lastWrittenBitSet_;									// Holder styr på hvornår der skal en ny char på vectoren
};
