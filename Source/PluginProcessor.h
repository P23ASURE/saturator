/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "filters.h"
#include "AutoGain.h"


//==============================================================================
/**
*/
class SaturatorAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    SaturatorAudioProcessor();
    ~SaturatorAudioProcessor() override;

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

    
    juce::AudioProcessorValueTreeState& getValueTreeState()
    {
        return mValueTreeState;
    }
        
private:
    
    float saturatorInput, saturatorDrive, saturatorMix;
    int button1, button2, button3;
    
    Filter highPassFilter, lowPassFilter;
    void updateFilterParameters();
    
    AutoGain autoGain;

    juce::AudioProcessorValueTreeState mValueTreeState;
    juce::AudioProcessorValueTreeState::ParameterLayout createParameters();
    
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SaturatorAudioProcessor)
};
