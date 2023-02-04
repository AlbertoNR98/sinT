/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "ParamsIDList.h"
#include "SinTSound.h"
#include "SinTVoice.h"
#include "FXProcessor.h"
#include "Data/Core/MeterData.h"
#include "Data/Core/PresetManagerData.h"

//==============================================================================
/**
*/
class SinTAudioProcessor  : public juce::AudioProcessor
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
{
public:
    //==============================================================================
    SinTAudioProcessor();
    ~SinTAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    //==============================================================================
    float getMainGainMeterRmsChannelValue(const int channel) const { return mainGainMeter.getRmsChannelValue(channel); }
    std::pair<float, float> getMainGainMeterRmsValues() const { return mainGainMeter.getRmsValues(); }

    //==============================================================================
    PresetManagerData& getPresetManager() { return *presetManager; };
    static juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    juce::AudioProcessorValueTreeState apvts;

private:
    static constexpr int numVoices{ 6 };

    void setSinTParameters();
    void setVoiceParameters();
    void setFilterParameters();
    void setFXParameters();

    juce::Synthesiser sinT;
    std::unique_ptr<PresetManagerData> presetManager;
    FXProcessor fxProcessor;
    MeterData mainGainMeter;
    juce::dsp::Gain<float> mainGainValue;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SinTAudioProcessor)
};
