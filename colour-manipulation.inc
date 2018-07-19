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

#define GetColorComponentFractValue GetColourComponentFractValue
#define GetColorComponentBinaryValue GetColourComponentBinaryValue
#define AddColorComponentGammaCor AddColourComponentGammaCor
#define RemoveColorComponentGammaCor RemoveColourComponentGammaCor
#define GetColorComponents GetColourComponents
#define GetColorComponent GetColourComponent
#define SetColorComponent SetColourComponent
#define GetColorCode GetColourCode
#define ConvertColor ConvertColour
#define InterpolateColors InterpolateColours
#define DarkenColor DarkenColour
#define LightenColor LightenColour
#define GrayscaleColor GrayscaleColour
#define GreyscaleColor GrayscaleColour
#define GreyscaleColour GrayscaleColour


enum ColourMode {
    COLOUR_MODE_RGBA,
    COLOUR_MODE_ARGB,
    COLOUR_MODE_RGB
};


enum ColourComponent {
    COLOUR_COMPONENT_R,
    COLOUR_COMPONENT_G,
    COLOUR_COMPONENT_B,
    COLOUR_COMPONENT_A,
}


stock Float:GetColourComponentFractValue(value) {
    return float(value) / 255.0;
}


stock GetColourComponentBinaryValue(Float:value) {
    return floatround(value * 255.0);
}


stock Float:AddColourComponentGammaCor(Float:value) {
    if (value <= 0.0031308) {
        value *= 12.92;
    } else {
        value = (1.055 * floatpower(value, 1.0 / 2.4)) - 0.055;
    }

    return value;
}


stock Float:RemoveColourComponentGammaCor(Float:value) {
    if (value <= 0.04045) {
        value /= 12.92;
    } else {
        value = floatpower((value + 0.055) / 1.055, 2.4);
    }

    return value;
}


stock GetColourComponents(colour, &Float:r, &Float:g, &Float:b, &Float:a = 1.0, ColourMode:mode = COLOUR_MODE_RGBA) {
    switch (mode) {
        case COLOUR_MODE_RGBA: {
            r = GetColourComponentFractValue((colour >>> 24) & 0xFF);
            g = GetColourComponentFractValue((colour >>> 16) & 0xFF);
            b = GetColourComponentFractValue((colour >>> 8) & 0xFF);
            a = GetColourComponentFractValue(colour & 0xFF);
        }

        case COLOUR_MODE_ARGB: {
            r = GetColourComponentFractValue((colour >>> 16) & 0xFF);
            g = GetColourComponentFractValue((colour >>> 8) & 0xFF);
            b = GetColourComponentFractValue(colour & 0xFF);
            a = GetColourComponentFractValue((colour >>> 24) & 0xFF);
        }

        case COLOUR_MODE_RGB: {
            r = GetColourComponentFractValue((colour >>> 16) & 0xFF);
            g = GetColourComponentFractValue((colour >>> 8) & 0xFF);
            b = GetColourComponentFractValue(colour & 0xFF);
            a = 1.0;
        }
    }
}


stock Float:GetColourComponent(colour, ColourComponent:component, ColourMode:mode = COLOUR_MODE_RGBA) {
    new Float:components[4];
    GetColourComponents(colour, components[0], components[1], components[2], components[3], mode);

    return components[_:component];
}


stock SetColourComponent(colour, ColourComponent:component, Float:value, ColourMode:mode = COLOUR_MODE_RGBA) {
    new Float:components[4];
    GetColourComponents(colour, components[0], components[1], components[2], components[3], mode);

    if (0.0 <= value <= 1.0) {
        components[_:component] = value;
    }

    return GetColourCode(components[0], components[1], components[2], components[3], mode);
}


stock Float:GetColourBrightness(colour, ColourMode:mode = COLOUR_MODE_RGBA) {
    new Float:components[4];
    GetColourComponents(colour, components[0], components[1], components[2], components[3], mode);

    return AddColourComponentGammaCor(
        0.212655 * RemoveColourComponentGammaCor(components[0]) +
        0.715158 * RemoveColourComponentGammaCor(components[1]) +
        0.072187 * RemoveColourComponentGammaCor(components[2])
    );
}


stock GetColourCode(Float:r, Float:g, Float:b, Float:a = 1.0, ColourMode:mode = COLOUR_MODE_RGBA) {
    new colour, components[4];

    components[0] = GetColourComponentBinaryValue(r);
    components[1] = GetColourComponentBinaryValue(g);
    components[2] = GetColourComponentBinaryValue(b);
    components[3] = GetColourComponentBinaryValue(a);

    switch (mode) {
        case COLOUR_MODE_RGBA: {
            colour = (components[3] & 0xFF) | ((components[2] & 0xFF) << 8) | ((components[1] & 0xFF) << 16) | ((components[0] & 0xFF) << 24);
        }

        case COLOUR_MODE_ARGB: {
            colour = (components[2] & 0xFF) | ((components[1] & 0xFF) << 8) | ((components[0] & 0xFF) << 16) | ((components[3] & 0xFF) << 24);
        }

        case COLOUR_MODE_RGB: {
            colour = (components[2] & 0xFF) | ((components[1] & 0xFF) << 8) | ((components[0] & 0xFF) << 16);
        }
    }

    return colour;
}


stock ConvertColour(colour, ColourMode:from, ColourMode:to, Float:alpha = 1.0) {
    new a = GetColourComponentBinaryValue(alpha);

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
                    colour = (colour << 8) | a;
                }

                case COLOUR_MODE_ARGB: {
                    colour = colour | (a << 24);
                }
            }
        }
    }

    return colour;
}


stock InterpolateColours(colour1, colour2, Float:amount, ColourMode:mode = COLOUR_MODE_RGBA) {
    new Float:components[2][4];
    GetColourComponents(colour1, components[0][0], components[0][1], components[0][2], components[0][3], mode);
    GetColourComponents(colour2, components[1][0], components[1][1], components[1][2], components[1][3], mode);

    for (new i; i < 4; i++) {
        components[0][i] = RemoveColourComponentGammaCor(components[0][i]);
        components[1][i] = RemoveColourComponentGammaCor(components[1][i]);

        components[0][i] += (components[1][i] - components[0][i]) * amount;

        components[0][i] = AddColourComponentGammaCor(components[0][i]);
    }

    return GetColourCode(components[0][0], components[0][1], components[0][2], components[0][3], mode);
}


stock DarkenColour(colour, Float:amount, ColourMode:mode = COLOUR_MODE_RGBA) {
    new Float:alpha = GetColourComponent(colour, COLOUR_COMPONENT_A, mode),
        black = ConvertColour(0x000000, COLOUR_MODE_RGB, mode, alpha);

    return InterpolateColours(colour, black, amount, mode);
}


stock LightenColour(colour, Float:amount, ColourMode:mode = COLOUR_MODE_RGBA) {
    new Float:alpha = GetColourComponent(colour, COLOUR_COMPONENT_A, mode),
        white = ConvertColour(0xFFFFFF, COLOUR_MODE_RGB, mode, alpha);

    return InterpolateColours(colour, white, amount, mode);
}


stock GrayscaleColour(colour, ColourMode:mode = COLOUR_MODE_RGBA) {
    new Float:alpha = GetColourComponent(colour, COLOUR_COMPONENT_A, mode),
        Float:brightness = GetColourBrightness(colour, mode);

    return GetColourCode(brightness, brightness, brightness, alpha, mode);
}
