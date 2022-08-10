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
    sinT.addVoice(new SinTVoice());
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

    for (int i = 0; i < sinT.getNumVoices(); i++)
    {
        if (auto voice = dynamic_cast<SinTVoice*>(sinT.getVoice(i)))
        {
            voice->prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
        }
    }
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

    for (int i = 0; i < sinT.getNumVoices(); ++i)
    {
        if (auto voice = dynamic_cast<SinTVoice*>(sinT.getVoice(i)))
        {
            // ADSR
            auto& attack = *apvts.getRawParameterValue("ATTACK");
            auto& decay = *apvts.getRawParameterValue("DECAY");
            auto& sustain = *apvts.getRawParameterValue("SUSTAIN");
            auto& release = *apvts.getRawParameterValue("RELEASE");

            // OSC1
            auto& osc1WaveSelect = *apvts.getRawParameterValue("OSC1WF");
            auto& osc1Gain = *apvts.getRawParameterValue("OSC1GAIN");
            auto& osc1Pitch = *apvts.getRawParameterValue("OSC1PITCH");

            // OSC2
            auto& osc2WaveSelect = *apvts.getRawParameterValue("OSC2WF");
            auto& osc2Gain = *apvts.getRawParameterValue("OSC2GAIN");
            auto& osc2Pitch = *apvts.getRawParameterValue("OSC2PITCH");

            // Procesamiento
            voice->getOscillator1().setWaveform(osc1WaveSelect);
            voice->getOscillator1().setGain(osc1Gain);
            voice->getOscillator1().setPitch(osc1Pitch);

            voice->getOscillator2().setWaveform(osc2WaveSelect);
            voice->getOscillator2().setGain(osc2Gain);
            voice->getOscillator2().setPitch(osc2Pitch);

            voice->update(attack.load(), decay.load(), sustain.load(), release.load());

        }
    }

    sinT.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool SinTAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* SinTAudioProcessor::createEditor()
{
    // return new juce::GenericAudioProcessorEditor(*this); // Editor de test
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

    // Oscilador 1
    layout.add(std::make_unique<juce::AudioParameterChoice>("OSC1WF", "Oscillator1Waveform", juce::StringArray { "Sine", "Saw", "Square" }, 0));
    layout.add(std::make_unique<juce::AudioParameterFloat>("OSC1GAIN", "Oscillator1Gain", juce::NormalisableRange<float> {-48.0f, 6.0f, 0.1f}, 0.0f, "dB"));
    layout.add(std::make_unique<juce::AudioParameterInt>("OSC1PITCH", "Oscillator1Pitch", -48, 48, 0));

    // Oscilador 2
    layout.add(std::make_unique<juce::AudioParameterChoice>("OSC2WF", "Oscillator2Waveform", juce::StringArray{ "Sine", "Saw", "Square" }, 0));
    layout.add(std::make_unique<juce::AudioParameterFloat>("OSC2GAIN", "Oscillator2Gain", juce::NormalisableRange<float> {-48.0f, 6.0f, 0.1f}, 0.0f, "dB"));
    layout.add(std::make_unique<juce::AudioParameterInt>("OSC2PITCH", "Oscillator2Pitch", -48, 48, 0));

    // ADSR
    layout.add(std::make_unique<juce::AudioParameterFloat>("ATTACK", "Attack", juce::NormalisableRange<float> {0.1f, 1.0f, }, 0.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("DECAY", "Decay", juce::NormalisableRange<float> {0.1f, 1.0f, }, 0.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("SUSTAIN", "Sustain", juce::NormalisableRange<float> {0.1f, 1.0f, }, 1.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("RELEASE", "Release", juce::NormalisableRange<float> {0.1f, 3.0f, }, 0.5f));

    return layout;
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SinTAudioProcessor();
}
