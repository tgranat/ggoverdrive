/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class GgOverdriveEditor  : public AudioProcessorEditor
{
public:
    GgOverdriveEditor (GgOverdriveProcessor&);
    ~GgOverdriveEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    GgOverdriveProcessor& processor;

    Slider levelSlider;
    Slider distSlider;
    Slider frequencySlider;

    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> mLevelAttachement;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> mDistAttachement;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> mFrequencyAttachement;

    // Scope stuff
    ScopeComponent<float> scopeComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GgOverdriveEditor)
};
