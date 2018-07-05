#include <a_samp>

#if defined _col_man_included
    #endinput
#endif
#define _col_man_included


#define COLOR_MODE_RGBA COLOUR_MODE_RGBA
#define COLOR_MODE_ARGB COLOUR_MODE_ARGB
#define COLOR_MODE_RGB COLOUR_MODE_RGB

#define COLOR_COMPONENT_R COLOUR_COMPONENT_R
#define COLOR_COMPONENT_G COLOUR_COMPONENT_G
#define COLOR_COMPONENT_B COLOUR_COMPONENT_B
#define COLOR_COMPONENT_A COLOUR_COMPONENT_A

#define GetColorComponents GetColourComponents
#define GetColorComponent GetColourComponent
#define SetColorComponent SetColourComponent
#define GetColorCode GetColourCode
#define ConvertColor ConvertColour
#define InterpolateColors InterpolateColours
#define DarkenColor DarkenColour
#define LightenColor LightenColour


enum ColourMode {
    COLOUR_MODE_RGBA,
    COLOUR_MODE_ARGB,
    COLOUR_MODE_RGB
};


enum InterpolationMode {
    INTERPOLATION_MODE_LINEAR,
    INTERPOLATION_MODE_CORRECTED,
    INTERPOLATION_MODE_REVERSE,
}


enum ColourComponent {
    COLOUR_COMPONENT_R,
    COLOUR_COMPONENT_G,
    COLOUR_COMPONENT_B,
    COLOUR_COMPONENT_A,
}


stock GetColourComponents(colour, &r, &g, &b, &a = 0xFF, ColourMode:mode = COLOUR_MODE_RGBA) {
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
            a = 0xFF;
        }
    }
}


stock GetColourComponent(colour, ColourComponent:component, ColourMode:mode = COLOUR_MODE_RGBA) {
    new components[4];
    GetColourComponents(colour, components[0], components[1], components[2], components[3], mode);

    return components[_:component];
}


stock SetColourComponent(colour, ColourComponent:component, value, ColourMode:mode = COLOUR_MODE_RGBA) {
    new components[4];
    GetColourComponents(colour, components[0], components[1], components[2], components[3], mode);

    components[_:component] = value & 0xFF;

    return GetColourCode(components[0], components[1], components[2], components[3], mode);
}


stock GetColourCode(r, g, b, a = 0xFF, ColourMode:mode = COLOUR_MODE_RGBA) {
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


stock ConvertColour(colour, ColourMode:from, ColourMode:to, alpha = 0xFF) {
    switch (from) {
        case COLOUR_MODE_RGBA: {
            switch (to) {
                case COLOUR_MODE_ARGB: {
                    colour = ((colour << 24) & 0xFF000000) | ((colour >>> 8) & 0xFFFFFF);
                }

                case COLOUR_MODE_RGB: {
                    colour = (colour >>> 8) & 0xFFFFFF;
                }
            }
        }

        case COLOUR_MODE_ARGB: {
            switch (to) {
                case COLOUR_MODE_RGBA: {
                    colour = ((colour << 8) & 0xFFFFFF00) | ((colour >>> 24) & 0xFF);
                }

                case COLOUR_MODE_RGB: {
                    colour = colour & 0x00FFFFFF;
                }
            }
        }

        case COLOUR_MODE_RGB: {
            switch (to) {
                case COLOUR_MODE_RGBA: {
                    colour = (colour << 8) | alpha;
                }

                case COLOUR_MODE_ARGB: {
                    colour = colour | (alpha << 24);
                }
            }
        }
    }

    return colour;
}


stock InterpolateColours(colour1, colour2, Float:amount, ColourMode:colour_mode = COLOUR_MODE_RGBA, InterpolationMode:interpolation_mode = INTERPOLATION_MODE_LINEAR) {
    new colour[2][4], Float:power;
    GetColourComponents(colour1, colour[0][0], colour[0][1], colour[0][2], colour[0][3], colour_mode);
    GetColourComponents(colour2, colour[1][0], colour[1][1], colour[1][2], colour[1][3], colour_mode);

    switch (interpolation_mode) {
        case INTERPOLATION_MODE_LINEAR: {
            power = 1.0;
        }

        case INTERPOLATION_MODE_CORRECTED: {
            power = 2.2;
        }

        case INTERPOLATION_MODE_REVERSE: {
            power = 1.0 / 2.2;
        }
    }

    for (new i; i < 4; i++) {
        colour[0][i] += floatround((colour[1][i] - colour[0][i]) * amount);
        colour[0][i] = floatround(floatpower(float(colour[0][i]) / 255.0, power) * 255.0);
    }

    return GetColourCode(colour[0][0], colour[0][1], colour[0][2], colour[0][3], colour_mode);
}


stock DarkenColour(colour, Float:amount, ColourMode:colour_mode = COLOUR_MODE_RGBA, InterpolationMode:interpolation_mode = INTERPOLATION_MODE_LINEAR) {
    new alpha = GetColourComponent(colour, COLOUR_COMPONENT_A, colour_mode),
        black = ConvertColour(0x000000, COLOUR_MODE_RGB, colour_mode, alpha);

    return InterpolateColours(colour, black, amount, colour_mode, interpolation_mode);
}


stock LightenColour(colour, Float:amount, ColourMode:colour_mode = COLOUR_MODE_RGBA, InterpolationMode:interpolation_mode = INTERPOLATION_MODE_LINEAR) {
    new alpha = GetColourComponent(colour, COLOUR_COMPONENT_A, colour_mode),
        white = ConvertColour(0xFFFFFF, COLOUR_MODE_RGB, colour_mode, alpha);

    return InterpolateColours(colour, white, amount, colour_mode, interpolation_mode);
}
