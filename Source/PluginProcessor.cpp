/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SinTAudioProcessor::SinTAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    sinT.addSound(new SinTSound());

    for(int i = 0; i < numVoices; i++) sinT.addVoice(new SinTVoice());
}

SinTAudioProcessor::~SinTAudioProcessor()
{
}

//==============================================================================
const juce::String SinTAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SinTAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SinTAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SinTAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SinTAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SinTAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SinTAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SinTAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String SinTAudioProcessor::getProgramName (int index)
{
    return {};
}

void SinTAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void SinTAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    sinT.setCurrentPlaybackSampleRate(sampleRate);

    juce::dsp::ProcessSpec spec{};
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumOutputChannels();

    for (int i = 0; i < sinT.getNumVoices(); i++)
    {
        if (auto voice = dynamic_cast<SinTVoice*>(sinT.getVoice(i)))
        {
            voice->prepareToPlay(spec);
        }
    }

    fxProcessor.prepareToPlay(spec);
    mainGainMeter.prepareToPlay(spec);
}

void SinTAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SinTAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void SinTAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // Establece parametros
    setSinTParameters();
    
    // Procesamiento del buffer de muestras
    sinT.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());

    // Procesamiento de efectos
    juce::dsp::AudioBlock<float> audioBlock{ buffer };
    fxProcessor.renderNextBlock(audioBlock);

    // Procesamiento de slider de ganancia de salida
    auto& mainGainValue = *apvts.getRawParameterValue("MAINGAIN");
    mainGain.setGainDecibels(mainGainValue);
    mainGain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));

    // Procesamiento de medidor de ganancia de salida
    mainGainMeter.renderNextBlock(buffer);
}

//==============================================================================
bool SinTAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* SinTAudioProcessor::createEditor()
{
    //return new juce::GenericAudioProcessorEditor(*this); // Editor de test
    return new SinTAudioProcessorEditor (*this); // Editor original
}

//==============================================================================
void SinTAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SinTAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
juce::AudioProcessorValueTreeState::ParameterLayout SinTAudioProcessor::createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;

    // Controles generales
    layout.add(std::make_unique<juce::AudioParameterFloat>("MAINGAIN", "MainGain", juce::NormalisableRange<float> {-60.0f, 12.0f, 0.1f}, 0.0f, "dB"));
    layout.add(std::make_unique<juce::AudioParameterBool>("PORTAMENTO", "Portamento", false));

    // Oscilador 1
    layout.add(std::make_unique<juce::AudioParameterChoice>("OSC1WF", "Oscillator1Waveform", juce::StringArray { "Sine", "Saw", "Square" }, 0));
    layout.add(std::make_unique<juce::AudioParameterFloat>("OSC1GAINDB", "Oscillator1Gain", juce::NormalisableRange<float> {-48.0f, 6.0f, 0.1f}, 0.0f, "dB"));
    layout.add(std::make_unique<juce::AudioParameterInt>("OSC1PITCH", "Oscillator1Pitch", -48, 48, 0));
    layout.add(std::make_unique<juce::AudioParameterFloat>("OSC1FMFREQ", "Oscillator1FMFreq", juce::NormalisableRange<float> {0.0f, 999.9f, 1.0f, 0.4f}, 0.0f, "Hz"));
    layout.add(std::make_unique<juce::AudioParameterFloat>("OSC1FMDEPTH", "Oscillator1FMDepth", juce::NormalisableRange<float> {0.0f, 100.0f, 0.1f}, 0.0f));

    // Oscilador 2
    layout.add(std::make_unique<juce::AudioParameterChoice>("OSC2WF", "Oscillator2Waveform", juce::StringArray{ "Sine", "Saw", "Square" }, 0));
    layout.add(std::make_unique<juce::AudioParameterFloat>("OSC2GAINDB", "Oscillator2Gain", juce::NormalisableRange<float> {-48.0f, 6.0f, 0.1f}, 0.0f, "dB"));
    layout.add(std::make_unique<juce::AudioParameterInt>("OSC2PITCH", "Oscillator2Pitch", -48, 48, 0));
    layout.add(std::make_unique<juce::AudioParameterFloat>("OSC2FMFREQ", "Oscillator2FMFreq", juce::NormalisableRange<float> {0.0f, 999.9f, 1.0f, 0.4f}, 0.0f, "Hz"));
    layout.add(std::make_unique<juce::AudioParameterFloat>("OSC2FMDEPTH", "Oscillator2FMDepth", juce::NormalisableRange<float> {0.0f, 100.0f, 0.1f}, 0.0f));

    // Amp ADSR
    layout.add(std::make_unique<juce::AudioParameterFloat>("AMPADSRATTACK", "AmpADSRAttack", juce::NormalisableRange<float> {0.01f, 16.0f, 0.01f}, 0.01f, "s"));
    layout.add(std::make_unique<juce::AudioParameterFloat>("AMPADSRDECAY", "AmpADSRDecay", juce::NormalisableRange<float> {0.0f, 16.0f, 0.5f}, 2.25f, "s"));
    layout.add(std::make_unique<juce::AudioParameterFloat>("AMPADSRSUSTAIN", "AmpADSRSustain", juce::NormalisableRange<float> {0.0f, 1.0f, 0.05f}, 1.0f, ""));
    layout.add(std::make_unique<juce::AudioParameterFloat>("AMPADSRRELEASE", "AmpADSRRelease", juce::NormalisableRange<float> {0.01f, 16.0f, 0.01f}, 0.1f, "s"));

    // Filter ADSR
    layout.add(std::make_unique<juce::AudioParameterFloat>("FILTERADSRDEPTH", "FilterADSRDepth", juce::NormalisableRange<float> {0.0f, 10000.0f, 0.1f, 0.3f}, 10000.0f, ""));
    layout.add(std::make_unique<juce::AudioParameterFloat>("FILTERADSRATTACK", "FilterADSRAttack", juce::NormalisableRange<float> {0.0f, 16.0f, 0.01f}, 0.0f, "s"));
    layout.add(std::make_unique<juce::AudioParameterFloat>("FILTERADSRDECAY", "FilterADSRDecay", juce::NormalisableRange<float> {0.0f, 16.0f, 0.5f}, 2.25f, "s"));
    layout.add(std::make_unique<juce::AudioParameterFloat>("FILTERADSRSUSTAIN", "FilterADSRSustain", juce::NormalisableRange<float> {0.0f, 1.0f, 0.01f}, 0.5f, ""));
    layout.add(std::make_unique<juce::AudioParameterFloat>("FILTERADSRRELEASE", "FilterADSRRelease", juce::NormalisableRange<float> {0.0f, 16.0f, 0.01f}, 2.25f, "s"));

    // Filtro
    layout.add(std::make_unique<juce::AudioParameterChoice>("FILTERMODE", "FilterMode", juce::StringArray{ "LPF", "BPF", "HPF" }, 0));
    layout.add(std::make_unique<juce::AudioParameterFloat>("FILTERCUTOFFFREQ", "FilterCutoffFreq", juce::NormalisableRange<float> {20.0f, 20000.0f, 0.1f, 0.6f}, 20000.0f, "Hz"));
    layout.add(std::make_unique<juce::AudioParameterFloat>("FILTERRESONANCE", "FilterResonance", juce::NormalisableRange<float> {0.1f, 2.0f, 0.05f}, 0.1f, ""));
    
    // LFO
    layout.add(std::make_unique<juce::AudioParameterFloat>("LFOFREQ", "LFOFreq", juce::NormalisableRange<float> {0.0f, 20.0f, 0.1f}, 0.0f, "Hz"));
    layout.add(std::make_unique<juce::AudioParameterFloat>("LFODEPTH", "LFODepth", juce::NormalisableRange<float> {0.0f, 10000.0f, 1.0f, 0.3f}, 0.0f, ""));

    // FX
    // Distorsion
    layout.add(std::make_unique<juce::AudioParameterFloat>("DISTORTIONDRIVE", "DistortionDrive", juce::NormalisableRange<float> {0.0f, 1.0f, 0.001f}, 0.0f, ""));
    layout.add(std::make_unique<juce::AudioParameterFloat>("DISTORTIONRANGE", "DistortionRange", juce::NormalisableRange<float> {0.0f, 500.0f, 0.1f}, 0.0f, ""));
    layout.add(std::make_unique<juce::AudioParameterFloat>("DISTORTIONBLEND", "DistortionBlend", juce::NormalisableRange<float> {0.0f, 1.0f, 0.001f}, 0.0f, ""));

    // Chorus
    layout.add(std::make_unique<juce::AudioParameterFloat>("CHORUSRATE", "ChorusRate", juce::NormalisableRange<float> {0.0f, 100.0f, 0.1f}, 1.0f, ""));
    layout.add(std::make_unique<juce::AudioParameterFloat>("CHORUSDEPTH", "ChorusDepth", juce::NormalisableRange<float> {0.0f, 1.0f, 0.01f}, 0.25f, ""));
    layout.add(std::make_unique<juce::AudioParameterFloat>("CHORUSCENTREDELAY", "ChorusCentreDelay", juce::NormalisableRange<float> {1.0f, 100.0f, 0.1f}, 7.0f, "ms"));
    layout.add(std::make_unique<juce::AudioParameterFloat>("CHORUSFEEDBACK", "ChorusFeedback", juce::NormalisableRange<float> {-1.0f, 1.0f, 0.01f}, 0.0f, ""));
    layout.add(std::make_unique<juce::AudioParameterFloat>("CHORUSMIX", "ChorusMix", juce::NormalisableRange<float> {0.0f, 1.0f, 0.01f}, 0.0f, ""));

    // Delay
    layout.add(std::make_unique<juce::AudioParameterFloat>("DELAYTIMEMS", "DelayTimeMs", juce::NormalisableRange<float> {0.0f, 1000.0f, 0.1f}, 0.0f, "ms"));
    layout.add(std::make_unique<juce::AudioParameterFloat>("DELAYFEEDBACK", "DelayFeedback", juce::NormalisableRange<float> {0.0f, 1.0f, 0.01f}, 0.0f, ""));

    // Reverb
    layout.add(std::make_unique<juce::AudioParameterFloat>("REVERBROOMSIZE", "ReverbRoomSize", juce::NormalisableRange<float> {0.0f, 1.0f, 0.01f}, 0.0f, ""));
    layout.add(std::make_unique<juce::AudioParameterFloat>("REVERBWIDTH", "ReverbWidth", juce::NormalisableRange<float> {0.0f, 1.0f, 0.01f}, 1.0f, ""));
    layout.add(std::make_unique<juce::AudioParameterFloat>("REVERBDAMPING", "ReverbDamping", juce::NormalisableRange<float> {0.0f, 1.0f, 0.01f}, 0.5f, ""));
    layout.add(std::make_unique<juce::AudioParameterFloat>("REVERBFREEZEMODE", "ReverbFreezeMode", juce::NormalisableRange<float> {0.0f, 1.0f, 0.1f}, 0.0f, ""));
    layout.add(std::make_unique<juce::AudioParameterFloat>("REVERBDRYLEVEL", "ReverbDryLevel", juce::NormalisableRange<float> {0.0f, 1.0f, 0.01f}, 1.0f, ""));
    layout.add(std::make_unique<juce::AudioParameterFloat>("REVERBWETLEVEL", "ReverbWetLevel", juce::NormalisableRange<float> {0.0f, 1.0f, 0.01f}, 0.0f, ""));
    
    return layout;
}

void SinTAudioProcessor::setSinTParameters()
{
    setVoiceParameters();
    setFilterParameters();
    setFXParameters();
}

void SinTAudioProcessor::setVoiceParameters()
{
    for (int indexVoice = 0; indexVoice < sinT.getNumVoices(); indexVoice++)
    {
        if (auto voice = dynamic_cast<SinTVoice*>(sinT.getVoice(indexVoice)))
        {
            // Portamento
            auto& portamento = *apvts.getRawParameterValue("PORTAMENTO");

            // Amp ADSR
            auto& ampAdsrAttack = *apvts.getRawParameterValue("AMPADSRATTACK");
            auto& ampAdsrDecay = *apvts.getRawParameterValue("AMPADSRDECAY");
            auto& ampAdsrSustain = *apvts.getRawParameterValue("AMPADSRSUSTAIN");
            auto& ampAdsrRelease = *apvts.getRawParameterValue("AMPADSRRELEASE");

            // Filter ADSR
            auto& filterAdsrAttack = *apvts.getRawParameterValue("FILTERADSRATTACK");
            auto& filterAdsrDecay = *apvts.getRawParameterValue("FILTERADSRDECAY");
            auto& filterAdsrSustain = *apvts.getRawParameterValue("FILTERADSRSUSTAIN");
            auto& filterAdsrRelease = *apvts.getRawParameterValue("FILTERADSRRELEASE");

            // OSC1
            auto& osc1WaveSelect = *apvts.getRawParameterValue("OSC1WF");
            auto& osc1GainDecibels = *apvts.getRawParameterValue("OSC1GAINDB");
            auto& osc1Pitch = *apvts.getRawParameterValue("OSC1PITCH");
            auto& osc1FmFreq = *apvts.getRawParameterValue("OSC1FMFREQ");
            auto& osc1FmDepth = *apvts.getRawParameterValue("OSC1FMDEPTH");

            // OSC2
            auto& osc2WaveSelect = *apvts.getRawParameterValue("OSC2WF");
            auto& osc2GainDecibels = *apvts.getRawParameterValue("OSC2GAINDB");
            auto& osc2Pitch = *apvts.getRawParameterValue("OSC2PITCH");
            auto& osc2FmFreq = *apvts.getRawParameterValue("OSC2FMFREQ");
            auto& osc2FmDepth = *apvts.getRawParameterValue("OSC2FMDEPTH");

            // Procesamiento
            auto& osc1 = voice->getOscillator1();
            auto& osc2 = voice->getOscillator2();

            auto& ampAdsr = voice->getAmpADSR();
            auto& filterAdsr = voice->getFilterADSR();

            for (int channel = 0; channel < getTotalNumOutputChannels(); channel++)
            {
                osc1[channel].setParameters(osc1WaveSelect, portamento, osc1GainDecibels, osc1Pitch, osc1FmFreq, osc1FmDepth);
                osc2[channel].setParameters(osc2WaveSelect, portamento, osc2GainDecibels, osc2Pitch, osc2FmFreq, osc2FmDepth);
            }

            ampAdsr.update(ampAdsrAttack.load(), ampAdsrDecay.load(), ampAdsrSustain.load(), ampAdsrRelease.load());
            filterAdsr.update(filterAdsrAttack.load(), filterAdsrDecay.load(), filterAdsrSustain.load(), filterAdsrRelease.load());
        }
    }
}

void SinTAudioProcessor::setFilterParameters()
{
    // Filtro
    auto& filterAdsrDepth = *apvts.getRawParameterValue("FILTERADSRDEPTH");
    auto& filterMode = *apvts.getRawParameterValue("FILTERMODE");
    auto& filterCutoffFreq = *apvts.getRawParameterValue("FILTERCUTOFFFREQ");
    auto& filterResonance = *apvts.getRawParameterValue("FILTERRESONANCE");

    // LFO
    auto& lfoFreq = *apvts.getRawParameterValue("LFOFREQ");
    auto& lfoDepth = *apvts.getRawParameterValue("LFODEPTH");

    for (int indexVoice = 0; indexVoice < sinT.getNumVoices(); indexVoice++)
    {
        if (auto voice = dynamic_cast<SinTVoice*>(sinT.getVoice(indexVoice)))
        {
            voice->setFilterModulationParameters(filterMode, filterCutoffFreq, filterResonance, filterAdsrDepth, lfoFreq, lfoDepth);
        }
    }
}

void SinTAudioProcessor::setFXParameters()
{
    // Distorsion
    auto& distortionDrive = *apvts.getRawParameterValue("DISTORTIONDRIVE");
    auto& distortionRange = *apvts.getRawParameterValue("DISTORTIONRANGE");
    auto& distortionBlend = *apvts.getRawParameterValue("DISTORTIONBLEND");

    // Chorus
    auto& chorusRate = *apvts.getRawParameterValue("CHORUSRATE");
    auto& chorusDepth = *apvts.getRawParameterValue("CHORUSDEPTH");
    auto& chorusCentreDelay = *apvts.getRawParameterValue("CHORUSCENTREDELAY");
    auto& chorusFeedback = *apvts.getRawParameterValue("CHORUSFEEDBACK");
    auto& chorusMix = *apvts.getRawParameterValue("CHORUSMIX");

    // Delay
    auto& delayTimeMs = *apvts.getRawParameterValue("DELAYTIMEMS");
    auto& delayFeedback = *apvts.getRawParameterValue("DELAYFEEDBACK");

    // Reverb
    auto& reverbRoomSize = *apvts.getRawParameterValue("REVERBROOMSIZE");
    auto& reverbWidth = *apvts.getRawParameterValue("REVERBWIDTH");
    auto& reverbDamping = *apvts.getRawParameterValue("REVERBDAMPING");
    auto& reverbFreezeMode = *apvts.getRawParameterValue("REVERBFREEZEMODE");
    auto& reverbDryLevel = *apvts.getRawParameterValue("REVERBDRYLEVEL");
    auto& reverbWetLevel = *apvts.getRawParameterValue("REVERBWETLEVEL");

    fxProcessor.setDistortionParameters(distortionDrive, distortionRange, distortionBlend);
    fxProcessor.setChorusParameters(chorusRate, chorusDepth, chorusCentreDelay, chorusFeedback, chorusMix);
    fxProcessor.setDelayParameters(delayTimeMs, delayFeedback);
    fxProcessor.setReverbParameters(reverbRoomSize, reverbWidth, reverbDamping, reverbFreezeMode, reverbDryLevel, reverbWetLevel);
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SinTAudioProcessor();
}
