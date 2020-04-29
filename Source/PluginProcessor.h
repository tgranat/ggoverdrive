/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class GgOverdriveProcessor  : public AudioProcessor,
                              public ValueTree::Listener
{
public:
    //==============================================================================
    GgOverdriveProcessor();
    ~GgOverdriveProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    AudioProcessorValueTreeState& getAPVTS() { return mAPVTS; }
 
    float mFrequency;
    float mDistortion;
    float mLevel;

private:
    enum
    {
        bandPassIndex,
        highPassIndex,
        levelIndex
    };

    // ProcessorDuplicator is used to duplicate mono processor classes. dsp::IIR::Filter only processes one channel.
    using BandPassFilter = dsp::ProcessorDuplicator<dsp::IIR::Filter<float>, dsp::IIR::Coefficients<float>>;
    using HighPassFilter = dsp::ProcessorDuplicator<dsp::IIR::Filter<float>, dsp::IIR::Coefficients<float>>;
    using Gain = dsp::Gain<float>;
    juce::dsp::ProcessorChain < BandPassFilter,       // The variable band pass filter
                                HighPassFilter,       // High pass filter before distorion stage
                                // gain stage (opamp)
                                // wave shaper opamp clipping
                                // maybe LP filter here simulating low opamp bandwidth?
                                // wave shaper diode clipping
                                // HP 22 Hz here (maybe)
                                // Maybe some bias and slight clipping on last transistor gain stage
                                Gain>                 // Main plugin Output level
                                processorChain;

    AudioProcessorValueTreeState mAPVTS;
    AudioProcessorValueTreeState::ParameterLayout createParameters();
    void valueTreePropertyChanged(ValueTree& treeWhosePropertyHasChanged, const Identifier& property) override;
    void updateParams();
    void setFrequencyFilterData(bool firstTime = false);
    void setOutputLevelData();

    float mCurrentFilterFrequency;
    float mFilterQ;
    float mCurrentDistortion;
    float mSampleRate = 0;

    std::atomic<bool> mParamsHaveBeenUpdatedInGUI{ false };

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GgOverdriveProcessor)
};


