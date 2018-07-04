# Colour Manipulation

This library provides a number of easy-to-use colour manipulation functions for PAWN.

## Installation

Simply install to your project:

```bash
sampctl package install kristoisberg/colour-manipulation
```

Include in your code and begin using the library:

```pawn
#include <colour-manipulation>
```

## Functions

```pawn
GetColourComponents(colour, &r, &g, &b, &a = 0xFF, ColourMode:mode = COLOUR_MODE_RGBA)
```
Extracts the RGB(A) components from a colour code.


```pawn
GetColourComponent(colour, ColourComponent:component, ColourMode:mode = COLOUR_MODE_RGBA)
```
Extracts an individual colour component from a colour code and returns it.


```pawn
SetColourComponent(colour, ColourComponent:component, value, ColourMode:mode = COLOUR_MODE_RGBA)
```
Modifies an individual component of an existing colour and returns the new colour.


```pawn
GetColourCode(r, g, b, a = 0xFF, ColourMode:mode = COLOUR_MODE_RGBA)
```
Creates a colour code from RGB(A) components.



```pawn
ConvertColour(colour, ColourMode:from, ColourMode:to, alpha = 0xFF)
```
Converts a colour from one colour mode to another. Alpha _should_ be specified when converting from RGB, otherwise `0xFF` (fully non-transparent) is used.



```pawn
InterpolateColours(colour1, colour2, Float:amount, ColourMode:colour_mode = COLOUR_MODE_RGBA, InterpolationMode:interpolation_mode = INTERPOLATION_MODE_LINEAR)
```
Interpolates two colours. `amount` must be in the range 0.0 - 1.0. The larger `amount` is, the closer the returned colour is to `colour2`.



```pawn
DarkenColour(colour, Float:amount, ColourMode:colour_mode = COLOUR_MODE_RGBA, InterpolationMode:interpolation_mode = INTERPOLATION_MODE_LINEAR)
```
Darkens a colour by interpolating it with the black colour.



```pawn
LightenColour(colour, Float:amount, ColourMode:colour_mode = COLOUR_MODE_RGBA, InterpolationMode:interpolation_mode = INTERPOLATION_MODE_LINEAR)
```
Lightens a colour by interpolating it with the white colour.




## Definitions

### Colour modes

`COLOUR_MODE_RGBA` - The most common colour format in SA-MP: used by `SendClientMessage`, textdraws, etc.

`COLOUR_MODE_ARGB`- Colour format used by `SetObjectMaterial`, `SetObjectMaterialText` and `SetPlayerAttachedObject`.

`COLOUR_MODE_RGB` - Colour format used by embedded colours, probably the most common colour format outside of SA-MP, most notably in webpages.


### Interpolation modes

`INTERPOLATION_MODE_LINEAR` - Linear, mathematically even interpolation. Should be fine in most situations, especially when used with textdraws as the game engine seems to be handling gamma correction itself.

`INTERPOLATION_MODE_CORRECTED` - Gamma corrected interpolation to make it seem more smooth and even for the human eye. Further explanation available [here](http://blog.johnnovak.net/2016/09/21/what-every-coder-should-know-about-gamma/).

`INTERPOLATION_MODE_REVERSE` - Does the exact opposite of `INTERPOLATION_MODE_CORRECTED`. I can't see any real usages for this, I only added this for testing.


### Colour components

`COLOUR_COMPONENT_R` - Red

`COLOUR_COMPONENT_G` - Green

`COLOUR_COMPONENT_B` - Blue

`COLOUR_COMPONENT_A` - Alpha


## Notes

The American spelling (color instead of colour) is supported for everything noted above.
