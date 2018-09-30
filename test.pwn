#include <a_samp>
#include "colour-manipulation.inc"


main() {
	test(0xFFFFFFCC, COLOUR_MODE_RGBA);
	test(0x000000CC, COLOUR_MODE_RGBA);

	test(0xFFFFFFFF, COLOUR_MODE_ARGB);
	test(0xFF000000, COLOUR_MODE_ARGB);

	test(0xFFFFFF, COLOUR_MODE_RGB);
	test(0x000000, COLOUR_MODE_RGB);

	printf("0x%06x", SetColourComponent(0x000000, COLOUR_COMPONENT_R, 1.0, COLOUR_MODE_RGB));
	printf("0x%06x", SetColourComponent(0x000000, COLOUR_COMPONENT_G, 1.0, COLOUR_MODE_RGB));
	printf("0x%06x", SetColourComponent(0x000000, COLOUR_COMPONENT_B, 1.0, COLOUR_MODE_RGB));

	printf("0x%08x", ConvertColour(0xFF0000, COLOUR_MODE_RGB, COLOUR_MODE_RGBA));
	printf("0x%08x", ConvertColour(0xFF0000CC, COLOUR_MODE_RGBA, COLOUR_MODE_ARGB));
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
	printf(fmt, GrayscaleColour(colour, mode));

	printf("%f", GetColourBrightness(colour, mode));
}


new Text:ColourTD[40];


public OnGameModeInit() {
	new colour;

	for (new i; i < 40; i++) {
		colour = InterpolateColours(0xFF0000FF, 0x0000FFFF, float(i) * 0.025);

		ColourTD[i] = TextDrawCreate(106.0 + float(i * 6), 88.0, "_");
		TextDrawUseBox(ColourTD[i], true);
		TextDrawBoxColor(ColourTD[i], colour);
		TextDrawTextSize(ColourTD[i], 111.0 + float(i * 6), 20.0);
	}

	return 1;
}


public OnPlayerConnect(playerid) {
	for (new i; i < 40; i++) {
		TextDrawShowForPlayer(playerid, ColourTD[i]);
	}

	return 1;
}
