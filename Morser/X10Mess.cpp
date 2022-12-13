#include "X10Mess.h"

X10Mess::X10Mess()
	: lastWrittenBitSet_(4)										// lastWrittenBitSet sættes til 4, hvilket er vores check for at skulle have en ny char/byte på vectoren...
																// Starter her, fordi vi vil have addTwoBits til at starte med at skabe en plads på vectoren
{
}

void X10Mess::addTwoBits(bool conditional) {					// Skriver komplementære bit-set (10/01) til leftmost siden af en byte i en vektor
																
	if (lastWrittenBitSet_ == 4) {								// Først checkes om nuværende plads i vector'en er fuld
		X10Contents_.push_back(0b00000000);						// I så fald laves plads - med rene 0'er, så vi kan eller (=|) 10/01 ind og sikre at de pladser der skulle være 0 giver 0...
																// ...da logisk eller ikke kan give 0 hvis der står 1 i forvejen
		lastWrittenBitSet_ = 0;									// Og vi resetter vores tæller
	}

	if (conditional == true) {									// Hvis sand (ie. 1), sættes de to rette pladser i sidste plads i vectoren lig 10.
		X10Contents_.back() |= (0b10000000 >> (lastWrittenBitSet_ * 2) );
	} else {													// Og tilsvarende for falsk, 01.
		X10Contents_.back() |= (0b01000000 >> (lastWrittenBitSet_ * 2) );
	}
	++lastWrittenBitSet_;										
}

void X10Mess::addVibbleNum(uint8_t newchar)						// Skriver et nummer mellem 0 og 31 til X10Contents_ ved at kalde addTwoBits
{
	for (uint8_t i = 0; i < 5; i++) {							// Tallet er mellem 0 og 31, vi skal kun bruge 5 pladser
		//read from bit, AND it out, then bitshift?
		addTwoBits(newchar & 0b00000001);						// Beder addTwoBits skrive indholdet af den rightmost bit ind
		newchar >>= 1;											// Bitshifter newchar til højre, så vi kan kigge på næste bit fra højre
	}
}

void X10Mess::addVibbleChar(uint8_t newchar)					// Konverterer diverse char's til tal mellem 0 og 31, og beder addVibbleNum om at skrive dem til X10Contents_
{
	// Jeg har forsøgt at skrive det følgende nogenlunde effektivt ift. tid/cycles, prioriteret lige foran læsbarhed
	// Derfor også brug af return - vi vil hurtigt ud af funktionen hvis der intet skal skrives alligevel.

	if (newchar > 90) return;									// Vi har ingen tegn med ASCII værdi over 90 vi vil arbejde på

	switch (newchar)											// De følgende speciel-karakterer håndteres
	{
	case ' ':
		addVibbleNum(27);
		break;
	case ',':
		addVibbleNum(28);
		break;
	case '.':
		addVibbleNum(29);
		break;
	}

	if (newchar < 65 ) return;									// Efter speciel-char check har vi ingen værdier under 65 vi vil arbejde på
										
	addVibbleNum(newchar);										// Alle muligheder undtagen 65-90 er nu udelukket, resterende kan bruges direkte i addVibbleNum
}

void X10Mess::addHeader()
{
	X10Contents_.clear();										// Nulstil indhold i X10Contents_ vektoren
	X10Contents_.push_back(0b00001110);							// Det er kun de sidste 4 bits der er nødvendigt, men de første 4 bits gør ingen skade...
																// ...og holder koden simplere for kun 4 * (100 Hz) = 2,5 millisekunder spildtid ved afsending.
}

void X10Mess::addFooter()
{
	if (X10Contents_.back() != NULL) {							// Vi behøver ikke smide et NULL ind, hvis der allerede er et
		X10Contents_.push_back(NULL);							// Ift. X10 behøver footeren ikke være mere end 6 0'er lang, igen forsimpler dette koden
	}
}

void X10Mess::getX10ContentsPtr(char*& X10ContentsPtr)			// Returnerer en pointer til indholdet i X10Contents_ vectoren, som et char array
{
	X10ContentsPtr = X10Contents_.data();
	return;
}
