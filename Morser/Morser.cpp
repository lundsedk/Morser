#include <stdint.h>
#include <string>
#include "Morser.h"

using namespace std;

Morser::Morser()
	: messOrg_(""), onIntensity_(0), offIntensity_(0), speed_(1), allAttrUpToDate_(false)
{
	// Skaber Morser objekt med default v�rdier.
	// allAttrUpToDate_ s�ttes false, da v�rdierne nu er �ndrede fra sidste (her, ikke-eksisterened) opdatering af myX10Mess_
}

																// Setters

void Morser::setSpeed(uint8_t newspeed) {

	if (speed_ == newspeed) { return; }							// Return bruges, s� vi skipper alt, inkl. "allAttrUpToDate_ = false;" linien

	if (newspeed > 31) {										// Sikrer vi ikke overstiger max
		speed_ = 31;
	}
	else if (newspeed < 1) {									// Sikrer vi ikke g�r under min
		speed_ = 1;
	}
	else {
		speed_ = newspeed;										// Opdaterer hvis input OK
	}
	allAttrUpToDate_ = false;									// Holder styr p� at vi nu har �ndrede v�rdier; myX10Mess_ ikke opdateret
}

void Morser::setOnIntensity(uint8_t onInt) {					// Fuldst�ndig parallel implementering ift. setSpeed()
	if (onIntensity_ == onInt) { return; }

	if (onInt > 31) {
		onIntensity_ = 31;
	}
	else {
		onIntensity_ = onInt;
	}
	allAttrUpToDate_ = false;
}

void Morser::setOffIntensity(uint8_t offInt) {					// Fuldst�ndig parallel implementering ift. setSpeed()
	if (offIntensity_ == offInt) { return; }

	if (offInt > 31) {
		offIntensity_= 31;
	}
	else {
		offIntensity_ = offInt;
	}
	allAttrUpToDate_ = false;
}

void Morser::setMessage(string newmessage) {
	if (messOrg_ == newmessage) { return; }						// Return bruges, s� vi skipper alt, inkl. "allAttrUpToDate_ = false;" linien

	messOrg_ = newmessage;

																// Loopet sikrer at alle bogstaver er upper case
	for ( uint64_t i = 0 ; i < messOrg_.length() ; i++) {			
		if ((messOrg_[i] >= 97) && (messOrg_[i] <= 122)) {		// 97 og 122 er hvor lower case ascii alfabetet starter/stopper
			messOrg_[i] += ('A' - 'a');							// Fra char'en l�gges forskellen mellem et upper og lower case A...
																// ...man kunne istedet have skrevet 32, men dette forklarer hvor det stammer fra, og hvad form�let er
		}
	}
	messOrg_ += " ";											//Sikrer at beskeden ikke er tom, og giver en pause i slutningen

	allAttrUpToDate_ = false;									// Holder styr p� at vi nu har �ndrede v�rdier; myX10Mess_ ikke opdateret

}

																// Getters - for simple til at kommentere p�

string Morser::getMessage() const
{
	return messOrg_;
}

uint16_t Morser::getSpeed() const
{
	return speed_;
}

uint8_t Morser::getOnIntensity_() const
{
	return onIntensity_;
}

uint8_t Morser::getOffIntensity_() const
{
	return offIntensity_;
}

void Morser::getAllAttrPtr(char*& allAttrPtr) {

	if (allAttrUpToDate_ == false) {							// Eneste sted vi l�ser allAttrUpToDate_ - kun hvis indholdet ikke er up to date, skal det opdateres
		genAllAttr();
	}
	
	myX10Mess_.getX10ContentsPtr(allAttrPtr);					// Returnerer ved at �ndre v�rdien af dens ene parameter...
																// ...f�r allAttrPtr til at pege p� hvor det rette indhold er
	return;
}


// Private, interne metoder

void Morser::genAllAttr()
{
	myX10Mess_.addHeader();										// Skriver header (og rydder eksisterende indhold f�rst).

	myX10Mess_.addVibbleNum(speed_);							// Skriver de tre numeriske attributer ind
	myX10Mess_.addVibbleNum(onIntensity_);
	myX10Mess_.addVibbleNum(offIntensity_);

	for (	auto it = messOrg_.begin() ;						// Skaber en iterator fra starten af string'en med vores besked i ASCII
			it != messOrg_.end() ;								// Forts�tter indtil vi n�et enden p� samme
			++it ) {											// Inkrementerer med en
		myX10Mess_.addVibbleChar(*it);							// Skriver hver char fra oprindelig besked ind, via addVibbleChar
	}

	myX10Mess_.addFooter();										// Skriver footer

	allAttrUpToDate_ = true;									// S� vi ikke beh�ver det ovenst�ende igen, medmindre noget er �ndret

}