#pragma once

#include "Morser.h"

//arcitecture of psoc...?
//	main
//		nothing, runs morsecon on startup
//	morsecon
//		init
//			inits
//			on startup, check eeprom - if set, save as array and run blinker with ptr to its
//		isrs
//			check for incoming - save if there are any, once enough 0's come through, run save then blinker with ptr
//		save
//			save to eeprom
//		blinker
//			takes ptr, if no pointer/null - take from eeprom
