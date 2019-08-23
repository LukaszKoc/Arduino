#ifndef CONSTANTS_H
#define CONSTANTS_H
 
// define your own namespace to hold constants
namespace Constants {

	const uint8_t char_A[] = { SEG_A | SEG_B | SEG_C | SEG_E | SEG_F | SEG_G};
	const uint8_t char_L[] = { SEG_D | SEG_E | SEG_F };
	const uint8_t char_T[] = { SEG_D | SEG_E | SEG_F | SEG_G};
	const uint8_t char_I[] = { SEG_E | SEG_F };
	const uint8_t char_S[] = { SEG_A | SEG_C | SEG_D | SEG_F | SEG_G};
	const uint8_t char_O[] = { SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F};
	const uint8_t char_slash[] = { SEG_A | SEG_B | SEG_F | SEG_G}; // /
	const uint8_t char_percent[] = { SEG_C | SEG_D | SEG_E | SEG_G};// %

	const uint8_t SEG_DONE[] = {
		SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,           // d
		SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,   // O
		SEG_C | SEG_E | SEG_G,                           // n
		SEG_A | SEG_D | SEG_E | SEG_F | SEG_G            // E
	};	
}


#endif