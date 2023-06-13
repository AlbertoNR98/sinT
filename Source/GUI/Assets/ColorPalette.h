/*
  ==============================================================================

    ColorPalette.h
    Paleta de colores de sinT

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

using namespace juce;

namespace ColorPalette 
{
    const Colour transparentblack{ 0 };
    const Colour transparentwhite{ 0x00ffffff };

    const Colour monwhite{ 0xffffffff };
    const Colour monblack{ 0xff000000 };

    const Colour basegray{ 0xff151515 }; // Container background color

    const Colour airun{ 0xffc685ff }; // Violet -> Side panel color
    const Colour orthzul{ 0xff443a84 }; // Purple -> Navbar component
    
    const Colour betis{ 0xff009739 }; // Green -> Enabled button color
    const Colour bypassgrey{ 0xff2a2a2a };  // Bypass button color

    // Colores de los bordes de los components
    const Colour miamipink{ 0xffe97da4 };
    const Colour miamiblue{ 0xff02b7dd };
    const Colour miamigreen{ 0xff57d5b5 };

    const Colour pmblue{ 0xff0959a4 };
    const Colour pmorange{ 0xffef7a68 };

    const Colour zeusblue{ 0xff4168e8 };
    const Colour zeusgold{ 0xffd27606 };
}
