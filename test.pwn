#include <a_samp>

#include "colour-manipulation.inc"


main() {
	test(0xFFFFFFFF, COLOUR_MODE_RGBA);
	test(0x000000FF, COLOUR_MODE_RGBA);

	test(0xFFFFFFFF, COLOUR_MODE_ARGB);
	test(0xFF000000, COLOUR_MODE_ARGB);

	test(0xFFFFFF, COLOUR_MODE_RGB);
	test(0x000000, COLOUR_MODE_RGB);
}


test(colour, ColourMode:mode) {
	new fmt[7];

	if (mode == COLOUR_MODE_RGB) {
		fmt = "0x%06x";
	} else {
		fmt = "0x%08x";
	}

	printf(fmt, colour);
	printf(fmt, DarkenColour(colour, 0.2, mode));
	printf(fmt, LightenColour(colour, 0.2, mode));
}
