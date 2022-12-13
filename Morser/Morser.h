#include <string>
#include <vector>
#include <stdbool.h>
#include "X10Mess.h"

using namespace std;

class Morser {
public:
	// Constructors
		Morser();
	// Setters
		void setMessage(string);
		void setSpeed(uint8_t newspeed);
		void setOnIntensity(uint8_t onInt);
		void setOffIntensity(uint8_t offInt);
	// Getters
		string getMessage() const;
		uint16_t getSpeed() const;
		uint8_t getOnIntensity_() const;
		uint8_t getOffIntensity_() const;
		void getAllAttrPtr(char *& allAttrPtr);				// "Hoved-metoden", som afleverer en reference til et null-termineret char array, med de rette vibbles (X10 besked)
private:
															// Attributer, svarer til input / set'ers
	uint8_t speed_;											// Hastighed beskeden skal sendes med
	uint8_t onIntensity_;									// Lysintensitet når der morses aktivt (prik eller streg i gang)
	uint8_t offIntensity_;									// Lysintensitet når der ikke morses aktivt (ingen besked, pauser)
	string messOrg_;										// Beskeden indtastet af bruger (upper case A-Z, ' ', ',', '.')

															// Metoder og klasser til intern brug
	bool allAttrUpToDate_;									// Hvis "true", så er myX10Mess_ opdatret med nyeste speed, hi/lo-int og mess værdier
	void genAllAttr();										// Opdaterer besked i Vibbles, ud fra "input" attributer

															// Under-klasse - Hver Morser indeholder (composition) præcis én X10Mess
	X10Mess myX10Mess_;										// Indeholder besked i Vibbles, og metoder skrive komplementære bits, samt header og footer, korrekt hertil
};

