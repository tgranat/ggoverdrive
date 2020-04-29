/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
GgOverdriveEditor::GgOverdriveEditor (GgOverdriveProcessor& p)
    : AudioProcessorEditor (&p), processor (p), scopeComponent(processor.getAudioBufferQueue())
{

    setSize (400, 300);

    levelSlider.setSliderStyle(Slider::RotaryVerticalDrag);
    levelSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    levelSlider.setPopupDisplayEnabled(true, false, this);
    //levelSlider.setLookAndFeel(&basicLookAndFeel);
    addAndMakeVisible(levelSlider);
    mLevelAttachement = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getAPVTS(), "LEVEL", levelSlider);

    distSlider.setSliderStyle(Slider::RotaryVerticalDrag);
    distSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    distSlider.setPopupDisplayEnabled(true, false, this);
    //distSlider.setLookAndFeel(&basicLookAndFeel);
    addAndMakeVisible(distSlider);
    mDistAttachement = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getAPVTS(), "DIST", distSlider);

    frequencySlider.setSliderStyle(Slider::RotaryVerticalDrag);
    frequencySlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    frequencySlider.setPopupDisplayEnabled(true, false, this);
    //frequencySlider.setLookAndFeel(&basicLookAndFeel);
    addAndMakeVisible(frequencySlider);
    mFrequencyAttachement = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getAPVTS(), "FREQUENCY", frequencySlider);

    // Scope stuff
    addAndMakeVisible(scopeComponent);
    auto area = getLocalBounds();
    scopeComponent.setTopLeftPosition(0, 80);
    scopeComponent.setSize(area.getWidth(), area.getHeight() - 100);
}

GgOverdriveEditor::~GgOverdriveEditor()
{
 
}

//==============================================================================
void GgOverdriveEditor::paint (Graphics& g)
{
    g.setColour(Colours::white);
    g.setFont(Font("Ariel", 15.0f, Font::bold));
    g.drawFittedText("Prototype Filter Overdrive", 0, 0, getWidth(), 30, Justification::centred, 1);
}

void GgOverdriveEditor::resized()
{
    int sliderLeft = 10;
    int sliderRow = 25;
    int w = 50;
    int h = 50;

    frequencySlider.setBounds(sliderLeft, sliderRow, w, h);
    distSlider.setBounds(sliderLeft + 80, sliderRow, w, h);
    levelSlider.setBounds(sliderLeft + 160, sliderRow, w, h);

}

