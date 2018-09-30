# PAWN Colour Manipulation

[![sampctl](https://shields.southcla.ws/badge/sampctl-pawn--colour--manipulation-2f2f2f.svg?style=for-the-badge)](https://github.com/kristoisberg/pawn-colour-manipulation)

This library provides a number of easy-to-use colour manipulation functions for PAWN.

## Installation

Simply install to your project:

```bash
sampctl package install kristoisberg/pawn-colour-manipulation
```

Include in your code and begin using the library:

```pawn
#include <colour-manipulation>
```

## Testing

To test, simply run the package:

```bash
sampctl package run
```

There is also a separate test script ([samp-grayscale-bitmap](https://github.com/kristoisberg/samp-grayscale-bitmap)) that unfortunately doesn't work yet due to a bug in [samp-bitmapper](https://github.com/Southclaws/samp-bitmapper).

## Functions

```pawn
GetColourComponents(colour, &Float:r, &Float:g, &Float:b, &Float:a = 1.0, ColourMode:mode = COLOUR_MODE_RGBA)
```
Extracts the RGB(A) components from a colour code.


```pawn
Float:GetColourComponent(colour, ColourComponent:component, ColourMode:mode = COLOUR_MODE_RGBA)
```
Extracts an individual colour component from a colour code and returns it.


```pawn
SetColourComponent(colour, ColourComponent:component, Float:value, ColourMode:mode = COLOUR_MODE_RGBA)
```
Modifies an individual component of an existing colour and returns the new colour.


```pawn
GetColourCode(Float:r, Float:g, Float:b, Float:a = 1.0, ColourMode:mode = COLOUR_MODE_RGBA)
```
Creates a colour code from RGB(A) components.


```pawn
ConvertColour(colour, ColourMode:from, ColourMode:to, Float:alpha = 1.0)
```
Converts a colour from one colour mode to another. Alpha _should_ be specified when converting from RGB, otherwise `0xFF` (fully non-transparent) is used.


```pawn
InterpolateColours(colour1, colour2, Float:amount, ColourMode:mode = COLOUR_MODE_RGBA)
```
Interpolates two colours. `amount` must be in the range 0.0 - 1.0. The larger `amount` is, the closer the returned colour is to `colour2`.


```pawn
Float:GetColourBrightness(colour, ColourMode:mode = COLOUR_MODE_RGBA)
```
Returns the brightness of a colour.


```pawn
DarkenColour(colour, Float:amount, ColourMode:mode = COLOUR_MODE_RGBA)
```
Darkens a colour by interpolating it with the black colour.


```pawn
LightenColour(colour, Float:amount, ColourMode:mode = COLOUR_MODE_RGBA)
```
Lightens a colour by interpolating it with the white colour.


```pawn
GrayscaleColour(colour, ColourMode:mode = COLOUR_MODE_RGBA)
```
Returns the grayscale equivalent of a colour.


```pawn
Float:GetColourComponentFractValue(value)
```
Converts a binary colour component value to a fractional value.


```pawn
GetColourComponentBinaryValue(Float:value)
```
Converts a fractional colour component value to a binary value.


```pawn
Float:AddColourComponentGammaCor(Float:value)
```
Adds sRGB gamma correction to a colour component.


```pawn
Float:RemoveColourComponentGammaCor(Float:value)
```
Removes the sRGB gamma correction from a colour component.



## Definitions

### Colour modes

`COLOUR_MODE_RGBA` - The most common colour format in SA-MP: used by `SendClientMessage`, textdraws, etc.

`COLOUR_MODE_ARGB`- Colour format used by `SetObjectMaterial`, `SetObjectMaterialText` and `SetPlayerAttachedObject`.

`COLOUR_MODE_RGB` - Colour format used by embedded colours, probably the most common colour format outside of SA-MP, most notably in webpages.



### Colour components

`COLOUR_COMPONENT_R` - Red

`COLOUR_COMPONENT_G` - Green

`COLOUR_COMPONENT_B` - Blue

`COLOUR_COMPONENT_A` - Alpha


## Notes

Both British and American spellings (color/colour, gray/grey) are supported for everything noted above.
