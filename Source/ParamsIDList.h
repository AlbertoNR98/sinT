/*
  ==============================================================================

    ParamsIDList.h
    Namespace que engloba los ID de los elementos del APVTS

  ==============================================================================
*/

#pragma once

namespace ParamsIDList
{
    // Controles generales
    inline constexpr auto mainGain { "MAINGAIN" };
    inline constexpr auto portamento { "PORTAMENTO" };

    // Oscilador 1
    inline constexpr auto osc1Bypassed { "OSC1BYPASSED" };
    inline constexpr auto osc1Waveform { "OSC1WF" };
    inline constexpr auto osc1Gain { "OSC1GAINDB" };
    inline constexpr auto osc1Pitch { "OSC1PITCH" };
    inline constexpr auto osc1FmFreq { "OSC1FMFREQ" };
    inline constexpr auto osc1FmDepth { "OSC1FMDEPTH" };

    // Oscilador 2
    inline constexpr auto osc2Bypassed { "OSC2BYPASSED" };
    inline constexpr auto osc2Waveform { "OSC2WF" };
    inline constexpr auto osc2Gain { "OSC2GAINDB" };
    inline constexpr auto osc2Pitch { "OSC2PITCH" };
    inline constexpr auto osc2FmFreq { "OSC2FMFREQ" };
    inline constexpr auto osc2FmDepth { "OSC2FMDEPTH" };

    // Amp ADSR
    inline constexpr auto ampAdsrAttack { "AMPADSRATTACK" };
    inline constexpr auto ampAdsrDecay { "AMPADSRDECAY" };
    inline constexpr auto ampAdsrSustain { "AMPADSRSUSTAIN" };
    inline constexpr auto ampAdsrRelease { "AMPADSRRELEASE" };

    // Filter ADSR
    inline constexpr auto filterAdsrDepth{ "FILTERADSRDEPTH" };
    inline constexpr auto filterAdsrAttack { "FILTERADSRATTACK" };
    inline constexpr auto filterAdsrDecay { "FILTERADSRDECAY" };
    inline constexpr auto filterAdsrSustain { "FILTERADSRSUSTAIN" };
    inline constexpr auto filterAdsrRelease { "FILTERADSRRELEASE" };

    // Filtro
    inline constexpr auto filterBypassed { "FILTERBYPASSED" };
    inline constexpr auto filterMode { "FILTERMODE" };
    inline constexpr auto filterCutoffFreq { "FILTERCUTOFFFREQ" };
    inline constexpr auto filterResonance { "FILTERRESONANCE" };

    // LFO
    inline constexpr auto lfoFreq { "LFOFREQ" };
    inline constexpr auto lfoDepth { "LFODEPTH" };

    // FX
    // Distorsion
    inline constexpr auto distortionBypassed { "DISTORTIONBYPASSED" };
    inline constexpr auto distortionDrive { "DISTORTIONDRIVE" };
    inline constexpr auto distortionRange { "DISTORTIONRANGE" };
    inline constexpr auto distortionMix { "DISTORTIONMIX" };

    // Chorus
    inline constexpr auto chorusBypassed { "CHORUSBYPASSED" };
    inline constexpr auto chorusRate { "CHORUSRATE" };
    inline constexpr auto chorusDepth { "CHORUSDEPTH" };
    inline constexpr auto chorusCentreDelay { "CHORUSCENTREDELAY" };
    inline constexpr auto chorusFeedback { "CHORUSFEEDBACK" };
    inline constexpr auto chorusMix { "CHORUSMIX" };

    // Delay
    inline constexpr auto delayBypassed { "DELAYBYPASSED" };
    inline constexpr auto delayTimeMs { "DELAYTIMEMS" };
    inline constexpr auto delayFeedback { "DELAYFEEDBACK" };

    // Reverb
    inline constexpr auto reverbBypassed { "REVERBBYPASSED" };
    inline constexpr auto reverbRoomSize { "REVERBROOMSIZE" };
    inline constexpr auto reverbWidth { "REVERBWIDTH" };
    inline constexpr auto reverbDamping { "REVERBDAMPING" };
    inline constexpr auto reverbFreezeMode { "REVERBFREEZEMODE" };
    inline constexpr auto reverbDryLevel { "REVERBDRYLEVEL" };
    inline constexpr auto reverbWetLevel { "REVERBWETLEVEL" };
}
