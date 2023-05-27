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
                       ),
#endif
    apvts(*this, nullptr, "Parameters", createParameterLayout())
{
    apvts.state.setProperty(PresetManagerData::presetNameProperty, "", nullptr);
    apvts.state.setProperty("version", ProjectInfo::versionString, nullptr);

    presetManager = std::make_unique<PresetManagerData>(apvts);

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
    auto& mainGainRawValue = *apvts.getRawParameterValue(ParamsIDList::mainGain);
    mainGainValue.setGainDecibels(mainGainRawValue);
    mainGainValue.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));

    // Procesamiento de medidor de ganancia de salida
    mainGainMeter.renderNextBlock(buffer);

    // Procesamiento de scope
    scopeDataCollector.process(buffer.getReadPointer(0), buffer.getNumSamples());
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

    // Guarda el estado como un XML
    const auto actualState = apvts.copyState();
    const auto xmlState(actualState.createXml());
    copyXmlToBinary(*xmlState, destData);
}

void SinTAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.

    // Carga un estado desde XML
    const auto xmlState = getXmlFromBinary(data, sizeInBytes);
    if (xmlState == nullptr)
        return;

    const auto newTree = juce::ValueTree::fromXml(*xmlState);
    if (newTree.isValid())
    {
        apvts.replaceState(newTree);
        setSinTParameters();
    }
}

//==============================================================================
juce::AudioProcessorValueTreeState::ParameterLayout SinTAudioProcessor::createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;

    using namespace ParamsIDList;

    // Controles generales
    layout.add(std::make_unique<juce::AudioParameterFloat>(mainGain, "MainGain", juce::NormalisableRange<float> {-60.0f, 12.0f, 0.1f, 1.5f}, 0.0f, "dB"));
    layout.add(std::make_unique<juce::AudioParameterBool>(portamento, "Portamento", false));

    // Oscilador 1
    layout.add(std::make_unique<juce::AudioParameterBool>(osc1Bypassed, "Oscillator1Bypassed", false));
    layout.add(std::make_unique<juce::AudioParameterChoice>(osc1Waveform, "Oscillator1Waveform", juce::StringArray { "Sine", "Saw", "Square", "Tri" }, 0));
    layout.add(std::make_unique<juce::AudioParameterFloat>(osc1Gain, "Oscillator1Gain", juce::NormalisableRange<float> {-48.0f, 6.0f, 0.1f}, 0.0f, "dB"));
    layout.add(std::make_unique<juce::AudioParameterInt>(osc1Pitch, "Oscillator1Pitch", -48, 48, 0));
    layout.add(std::make_unique<juce::AudioParameterFloat>(osc1FmFreq, "Oscillator1FMFreq", juce::NormalisableRange<float> {0.0f, 999.9f, 1.0f, 0.4f}, 0.0f, "Hz"));
    layout.add(std::make_unique<juce::AudioParameterFloat>(osc1FmDepth, "Oscillator1FMDepth", juce::NormalisableRange<float> {0.0f, 100.0f, 0.1f}, 0.0f));

    // Oscilador 2
    layout.add(std::make_unique<juce::AudioParameterBool>(osc2Bypassed, "Oscillator2Bypassed", false));
    layout.add(std::make_unique<juce::AudioParameterChoice>(osc2Waveform, "Oscillator2Waveform", juce::StringArray{ "Sine", "Saw", "Square", "Tri" }, 0));
    layout.add(std::make_unique<juce::AudioParameterFloat>(osc2Gain, "Oscillator2Gain", juce::NormalisableRange<float> {-48.0f, 6.0f, 0.1f}, 0.0f, "dB"));
    layout.add(std::make_unique<juce::AudioParameterInt>(osc2Pitch, "Oscillator2Pitch", -48, 48, 0));
    layout.add(std::make_unique<juce::AudioParameterFloat>(osc2FmFreq, "Oscillator2FMFreq", juce::NormalisableRange<float> {0.0f, 999.9f, 1.0f, 0.4f}, 0.0f, "Hz"));
    layout.add(std::make_unique<juce::AudioParameterFloat>(osc2FmDepth, "Oscillator2FMDepth", juce::NormalisableRange<float> {0.0f, 100.0f, 0.1f}, 0.0f));

    // Amp ADSR
    layout.add(std::make_unique<juce::AudioParameterFloat>(ampAdsrAttack, "AmpADSRAttack", juce::NormalisableRange<float> {0.01f, 16.0f, 0.01f, 0.5f}, 0.01f, "s"));
    layout.add(std::make_unique<juce::AudioParameterFloat>(ampAdsrDecay, "AmpADSRDecay", juce::NormalisableRange<float> {0.0f, 16.0f, 0.5f, 0.5f}, 2.25f, "s"));
    layout.add(std::make_unique<juce::AudioParameterFloat>(ampAdsrSustain, "AmpADSRSustain", juce::NormalisableRange<float> {0.0f, 1.0f, 0.05f}, 1.0f, ""));
    layout.add(std::make_unique<juce::AudioParameterFloat>(ampAdsrRelease, "AmpADSRRelease", juce::NormalisableRange<float> {0.01f, 16.0f, 0.01f, 0.5f}, 0.1f, "s"));

    // Filter ADSR
    layout.add(std::make_unique<juce::AudioParameterFloat>(filterAdsrDepth, "FilterADSRDepth", juce::NormalisableRange<float> {0.0f, 10000.0f, 0.1f, 0.3f}, 10000.0f, ""));
    layout.add(std::make_unique<juce::AudioParameterFloat>(filterAdsrAttack, "FilterADSRAttack", juce::NormalisableRange<float> {0.0f, 16.0f, 0.01f, 0.5f}, 0.0f, "s"));
    layout.add(std::make_unique<juce::AudioParameterFloat>(filterAdsrDecay, "FilterADSRDecay", juce::NormalisableRange<float> {0.0f, 16.0f, 0.5f, 0.5f}, 0.0f, "s"));
    layout.add(std::make_unique<juce::AudioParameterFloat>(filterAdsrSustain, "FilterADSRSustain", juce::NormalisableRange<float> {0.0f, 1.0f, 0.01f}, 0.0f, ""));
    layout.add(std::make_unique<juce::AudioParameterFloat>(filterAdsrRelease, "FilterADSRRelease", juce::NormalisableRange<float> {0.0f, 16.0f, 0.01f, 0.5f}, 0.0f, "s"));

    // Filtro
    layout.add(std::make_unique<juce::AudioParameterBool>(filterBypassed, "FilterBypassed", false));
    layout.add(std::make_unique<juce::AudioParameterChoice>(filterMode, "FilterMode", juce::StringArray{ "LPF", "BPF", "HPF" }, 0));
    layout.add(std::make_unique<juce::AudioParameterFloat>(filterCutoffFreq, "FilterCutoffFreq", juce::NormalisableRange<float> {20.0f, 20000.0f, 0.1f, 0.5f}, 20000.0f, "Hz"));
    layout.add(std::make_unique<juce::AudioParameterFloat>(filterResonance, "FilterResonance", juce::NormalisableRange<float> {0.3f, 20.0f, 0.01f, 0.5}, 1.0f / juce::MathConstants<float>::sqrt2, ""));

    // LFO
    layout.add(std::make_unique<juce::AudioParameterFloat>(lfoFreq, "LFOFreq", juce::NormalisableRange<float> {0.0f, 20.0f, 0.1f}, 0.0f, "Hz"));
    layout.add(std::make_unique<juce::AudioParameterFloat>(lfoDepth, "LFODepth", juce::NormalisableRange<float> {0.0f, 10000.0f, 1.0f, 0.65f}, 0.0f, ""));

    // FX
    // Distorsion
    layout.add(std::make_unique<juce::AudioParameterBool>(distortionBypassed, "DistortionBypassed", false));
    layout.add(std::make_unique<juce::AudioParameterFloat>(distortionDrive, "DistortionDrive", juce::NormalisableRange<float> {0.0f, 1.0f, 0.01f}, 0.0f, ""));
    layout.add(std::make_unique<juce::AudioParameterFloat>(distortionRange, "DistortionRange", juce::NormalisableRange<float> {0.0f, 500.0f, 0.1f}, 0.0f, ""));
    layout.add(std::make_unique<juce::AudioParameterFloat>(distortionBlend, "DistortionBlend", juce::NormalisableRange<float> {0.0f, 1.0f, 0.01f}, 0.0f, ""));

    // Chorus
    layout.add(std::make_unique<juce::AudioParameterBool>(chorusBypassed, "ChorusBypassed", false));
    layout.add(std::make_unique<juce::AudioParameterFloat>(chorusRate, "ChorusRate", juce::NormalisableRange<float> {0.0f, 100.0f, 0.1f}, 1.0f, ""));
    layout.add(std::make_unique<juce::AudioParameterFloat>(chorusDepth, "ChorusDepth", juce::NormalisableRange<float> {0.0f, 1.0f, 0.01f}, 0.25f, ""));
    layout.add(std::make_unique<juce::AudioParameterFloat>(chorusCentreDelay, "ChorusCentreDelay", juce::NormalisableRange<float> {1.0f, 100.0f, 0.1f}, 7.0f, "ms"));
    layout.add(std::make_unique<juce::AudioParameterFloat>(chorusFeedback, "ChorusFeedback", juce::NormalisableRange<float> {-1.0f, 1.0f, 0.01f}, 0.0f, ""));
    layout.add(std::make_unique<juce::AudioParameterFloat>(chorusMix, "ChorusMix", juce::NormalisableRange<float> {0.0f, 1.0f, 0.01f}, 0.0f, ""));

    // Delay
    layout.add(std::make_unique<juce::AudioParameterBool>(delayBypassed, "DelayBypassed", false));
    layout.add(std::make_unique<juce::AudioParameterFloat>(delayTimeMs, "DelayTimeMs", juce::NormalisableRange<float> {0.0f, 4000.0f, 0.1f, 0.65}, 0.0f, "ms"));
    layout.add(std::make_unique<juce::AudioParameterFloat>(delayFeedback, "DelayFeedback", juce::NormalisableRange<float> {0.0f, 1.0f, 0.01f}, 0.0f, ""));

    // Reverb
    layout.add(std::make_unique<juce::AudioParameterBool>(reverbBypassed, "ReverbBypassed", false));
    layout.add(std::make_unique<juce::AudioParameterFloat>(reverbRoomSize, "ReverbRoomSize", juce::NormalisableRange<float> {0.0f, 1.0f, 0.01f}, 0.0f, ""));
    layout.add(std::make_unique<juce::AudioParameterFloat>(reverbWidth, "ReverbWidth", juce::NormalisableRange<float> {0.0f, 1.0f, 0.01f}, 1.0f, ""));
    layout.add(std::make_unique<juce::AudioParameterFloat>(reverbDamping, "ReverbDamping", juce::NormalisableRange<float> {0.0f, 1.0f, 0.01f}, 0.5f, ""));
    layout.add(std::make_unique<juce::AudioParameterBool>(reverbFreezeMode, "ReverbFreezeMode", false));
    layout.add(std::make_unique<juce::AudioParameterFloat>(reverbDryLevel, "ReverbDryLevel", juce::NormalisableRange<float> {0.0f, 1.0f, 0.01f}, 1.0f, ""));
    layout.add(std::make_unique<juce::AudioParameterFloat>(reverbWetLevel, "ReverbWetLevel", juce::NormalisableRange<float> {0.0f, 1.0f, 0.01f}, 0.0f, ""));
    
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
            auto& portamento = *apvts.getRawParameterValue(ParamsIDList::portamento);

            // Amp ADSR
            auto& ampAdsrAttack = *apvts.getRawParameterValue(ParamsIDList::ampAdsrAttack);
            auto& ampAdsrDecay = *apvts.getRawParameterValue(ParamsIDList::ampAdsrDecay);
            auto& ampAdsrSustain = *apvts.getRawParameterValue(ParamsIDList::ampAdsrSustain);
            auto& ampAdsrRelease = *apvts.getRawParameterValue(ParamsIDList::ampAdsrRelease);

            // Filter ADSR
            auto& filterAdsrAttack = *apvts.getRawParameterValue(ParamsIDList::filterAdsrAttack);
            auto& filterAdsrDecay = *apvts.getRawParameterValue(ParamsIDList::filterAdsrDecay);
            auto& filterAdsrSustain = *apvts.getRawParameterValue(ParamsIDList::filterAdsrSustain);
            auto& filterAdsrRelease = *apvts.getRawParameterValue(ParamsIDList::filterAdsrRelease);

            // OSC1
            auto& osc1Bypassed = *apvts.getRawParameterValue(ParamsIDList::osc1Bypassed);
            auto& osc1WaveSelect = *apvts.getRawParameterValue(ParamsIDList::osc1Waveform);
            auto& osc1GainDecibels = *apvts.getRawParameterValue(ParamsIDList::osc1Gain);
            auto& osc1Pitch = *apvts.getRawParameterValue(ParamsIDList::osc1Pitch);
            auto& osc1FmFreq = *apvts.getRawParameterValue(ParamsIDList::osc1FmFreq);
            auto& osc1FmDepth = *apvts.getRawParameterValue(ParamsIDList::osc1FmDepth);

            // OSC2
            auto& osc2Bypassed = *apvts.getRawParameterValue(ParamsIDList::osc2Bypassed);
            auto& osc2WaveSelect = *apvts.getRawParameterValue(ParamsIDList::osc2Waveform);
            auto& osc2GainDecibels = *apvts.getRawParameterValue(ParamsIDList::osc2Gain);
            auto& osc2Pitch = *apvts.getRawParameterValue(ParamsIDList::osc2Pitch);
            auto& osc2FmFreq = *apvts.getRawParameterValue(ParamsIDList::osc2FmFreq);
            auto& osc2FmDepth = *apvts.getRawParameterValue(ParamsIDList::osc2FmDepth);

            // Procesamiento
            auto& osc1 = voice->getOscillator1();
            auto& osc2 = voice->getOscillator2();

            auto& ampAdsr = voice->getAmpADSR();
            auto& filterAdsr = voice->getFilterADSR();

            for (int channel = 0; channel < getTotalNumOutputChannels(); channel++)
            {
                osc1[channel].setParameters(osc1Bypassed, osc1WaveSelect, portamento, osc1GainDecibels, osc1Pitch, osc1FmFreq, osc1FmDepth);
                osc2[channel].setParameters(osc2Bypassed, osc2WaveSelect, portamento, osc2GainDecibels, osc2Pitch, osc2FmFreq, osc2FmDepth);
            }

            ampAdsr.update(ampAdsrAttack.load(), ampAdsrDecay.load(), ampAdsrSustain.load(), ampAdsrRelease.load());
            filterAdsr.update(filterAdsrAttack.load(), filterAdsrDecay.load(), filterAdsrSustain.load(), filterAdsrRelease.load());
        }
    }
}

void SinTAudioProcessor::setFilterParameters()
{
    // Filtro
    auto& filterBypassed = *apvts.getRawParameterValue(ParamsIDList::filterBypassed);
    auto& filterAdsrDepth = *apvts.getRawParameterValue(ParamsIDList::filterAdsrDepth);
    auto& filterMode = *apvts.getRawParameterValue(ParamsIDList::filterMode);
    auto& filterCutoffFreq = *apvts.getRawParameterValue(ParamsIDList::filterCutoffFreq);
    auto& filterResonance = *apvts.getRawParameterValue(ParamsIDList::filterResonance);

    // LFO
    auto& lfoFreq = *apvts.getRawParameterValue(ParamsIDList::lfoFreq);
    auto& lfoDepth = *apvts.getRawParameterValue(ParamsIDList::lfoDepth);

    for (int indexVoice = 0; indexVoice < sinT.getNumVoices(); indexVoice++)
    {
        if (auto voice = dynamic_cast<SinTVoice*>(sinT.getVoice(indexVoice)))
        {
            voice->setFilterModulationParameters(filterBypassed, filterMode, filterCutoffFreq, filterResonance, filterAdsrDepth, lfoFreq, lfoDepth);
        }
    }
}

void SinTAudioProcessor::setFXParameters()
{
    // Distorsion
    auto& distortionBypassed = *apvts.getRawParameterValue(ParamsIDList::distortionBypassed);
    auto& distortionDrive = *apvts.getRawParameterValue(ParamsIDList::distortionDrive);
    auto& distortionRange = *apvts.getRawParameterValue(ParamsIDList::distortionRange);
    auto& distortionBlend = *apvts.getRawParameterValue(ParamsIDList::distortionBlend);

    // Chorus
    auto& chorusBypassed = *apvts.getRawParameterValue(ParamsIDList::chorusBypassed);
    auto& chorusRate = *apvts.getRawParameterValue(ParamsIDList::chorusRate);
    auto& chorusDepth = *apvts.getRawParameterValue(ParamsIDList::chorusDepth);
    auto& chorusCentreDelay = *apvts.getRawParameterValue(ParamsIDList::chorusCentreDelay);
    auto& chorusFeedback = *apvts.getRawParameterValue(ParamsIDList::chorusFeedback);
    auto& chorusMix = *apvts.getRawParameterValue(ParamsIDList::chorusMix);

    // Delay
    auto& delayBypassed = *apvts.getRawParameterValue(ParamsIDList::delayBypassed);
    auto& delayTimeMs = *apvts.getRawParameterValue(ParamsIDList::delayTimeMs);
    auto& delayFeedback = *apvts.getRawParameterValue(ParamsIDList::delayFeedback);

    // Reverb
    auto& reverbBypassed = *apvts.getRawParameterValue(ParamsIDList::reverbBypassed);
    auto& reverbFreezeMode = *apvts.getRawParameterValue(ParamsIDList::reverbFreezeMode);
    auto& reverbRoomSize = *apvts.getRawParameterValue(ParamsIDList::reverbRoomSize);
    auto& reverbWidth = *apvts.getRawParameterValue(ParamsIDList::reverbWidth);
    auto& reverbDamping = *apvts.getRawParameterValue(ParamsIDList::reverbDamping);
    auto& reverbDryLevel = *apvts.getRawParameterValue(ParamsIDList::reverbDryLevel);
    auto& reverbWetLevel = *apvts.getRawParameterValue(ParamsIDList::reverbWetLevel);

    fxProcessor.setDistortionParameters(distortionBypassed, distortionDrive, distortionRange, distortionBlend);
    fxProcessor.setChorusParameters(chorusBypassed, chorusRate, chorusDepth, chorusCentreDelay, chorusFeedback, chorusMix);
    fxProcessor.setDelayParameters(delayBypassed, delayTimeMs, delayFeedback);
    fxProcessor.setReverbParameters(reverbBypassed, reverbFreezeMode, reverbRoomSize, reverbWidth, reverbDamping, reverbDryLevel, reverbWetLevel);
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SinTAudioProcessor();
}
