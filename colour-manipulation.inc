#include <a_samp>

#if defined _ColMan_included
    #endinput
#endif
#define _ColMan_included


#define COLOR_MODE_RGBA COLOUR_MODE_RGBA
#define COLOR_MODE_ARGB COLOUR_MODE_ARGB
#define COLOR_MODE_RGB COLOUR_MODE_RGB

#define LerpColor LerpColour
#define DarkenColor DarkenColour
#define LightenColor LightenColour
#define GetColorComponents GetColourComponents
#define GetColorCode GetColourCode


enum ColourMode {
	COLOUR_MODE_RGBA,
	COLOUR_MODE_ARGB,
	COLOUR_MODE_RGB
};


stock GetColourComponents(colour, &r, &g, &b, &a = 0, ColourMode:mode = COLOUR_MODE_RGBA) {
	switch (mode) {
	    case COLOUR_MODE_RGBA: {
	        r = (colour >>> 24) & 0xFF;
			g = (colour >>> 16) & 0xFF;
			b = (colour >>> 8) & 0xFF;
			a = colour & 0xFF;
	    }

	    case COLOUR_MODE_ARGB: {
	        r = (colour >>> 16) & 0xFF;
			g = (colour >>> 8) & 0xFF;
			b = colour & 0xFF;
	        a = (colour >>> 24) & 0xFF;
	    }

	    case COLOUR_MODE_RGB: {
	        r = (colour >>> 16) & 0xFF;
			g = (colour >>> 8) & 0xFF;
			b = colour & 0xFF;
	        a = 0;
	    }
	}
}


stock GetColourCode(r, g, b, a, ColourMode:mode = COLOUR_MODE_RGBA) {
	new colour;

    switch (mode) {
	    case COLOUR_MODE_RGBA: {
	        colour = (a & 0xFF) | ((b & 0xFF) << 8) | ((g & 0xFF) << 16) | ((r & 0xFF) << 24);
	    }

	    case COLOUR_MODE_ARGB: {
	        colour = (b & 0xFF) | ((g & 0xFF) << 8) | ((r & 0xFF) << 16) | ((a & 0xFF) << 24);
	    }

	    case COLOUR_MODE_RGB: {
            colour = (b & 0xFF) | ((g & 0xFF) << 8) | ((r & 0xFF) << 16);
	    }
	}

	return colour;
}


stock LerpColour(colour1, colour2, Float:amount, ColourMode:mode = COLOUR_MODE_RGBA) {
	new colour[2][4];
	GetColourComponents(colour1, colour[0][0], colour[0][1], colour[0][2], colour[0][3], mode);
	GetColourComponents(colour2, colour[1][0], colour[1][1], colour[1][2], colour[1][3], mode);

	for (new i; i < 4; i++) {
	    colour[0][i] += floatround((colour[1][i] - colour[0][i]) * amount);
	}

	return GetColourCode(colour[0][0], colour[0][1], colour[0][2], colour[0][3], mode);
}


stock DarkenColour(colour, Float:amount, ColourMode:mode = COLOUR_MODE_RGBA) {
	new black;

	switch (mode) {
	    case COLOUR_MODE_RGBA: {
	        black = 0x000000FF;
	    }

	    case COLOUR_MODE_ARGB: {
			black = 0xFF000000;
	    }

	    case COLOUR_MODE_RGB: {
            black = 0x000000;
	    }
	}

	return LerpColour(colour, black, amount, mode);
}


stock LightenColour(colour, Float:amount, ColourMode:mode = COLOUR_MODE_RGBA) {
	new white;

	switch (mode) {
	    case COLOUR_MODE_RGBA: {
	        white = 0xFFFFFFFF;
	    }

	    case COLOUR_MODE_ARGB: {
			white = 0xFFFFFFFF;
	    }

	    case COLOUR_MODE_RGB: {
            white = 0xFFFFFF;
	    }
	}

	return LerpColour(colour, white, amount, mode);
}


stock RGBAToRGB(colour) {
	return (colour >>> 8) & 0xFFFFFF;
}


stock RGBToRGBA(colour, alpha) {
	return (colour << 8) | alpha;
}


stock ARGBToRGB(colour) {
	return colour & 0x00FFFFFF;
}


stock RGBToARGB(colour, alpha) {
	return colour | (alpha << 24);
}


stock RGBAToARGB(colour) {
	return ((colour << 24) & 0xFF000000) | ((colour >>> 8) & 0xFFFFFF);
}


stock ARGBToRGBA(colour) {
	return ((colour << 8) & 0xFFFFFF00) | ((colour >>> 24) & 0xFF);
}
