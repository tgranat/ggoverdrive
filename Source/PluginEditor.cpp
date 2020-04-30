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

    Font controlFont("Ariel", 13.0f, Font::plain);

    // === Output level ===
    levelSlider.setSliderStyle(Slider::RotaryVerticalDrag);
    levelSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    levelSlider.setPopupDisplayEnabled(true, false, this);
    //levelSlider.setLookAndFeel(&basicLookAndFeel);
    addAndMakeVisible(levelSlider);
    mLevelAttachement = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getAPVTS(), "LEVEL", levelSlider);

    levelLabel.setFont(controlFont);
    levelLabel.setText("Level Out", dontSendNotification);
    levelLabel.setJustificationType(Justification::centredBottom);
    levelLabel.attachToComponent(&levelSlider, false);
    addAndMakeVisible(levelLabel);

    // == Input level ==
    inputLevelSlider.setSliderStyle(Slider::RotaryVerticalDrag);
    inputLevelSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    inputLevelSlider.setPopupDisplayEnabled(true, false, this);
    //inputLevelSlider.setLookAndFeel(&basicLookAndFeel);
    addAndMakeVisible(inputLevelSlider);
    mLevelAttachement = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getAPVTS(), "INPUT LEVEL", inputLevelSlider);

    inputLevelLabel.setFont(controlFont);
    inputLevelLabel.setText("Level In", dontSendNotification);
    inputLevelLabel.setJustificationType(Justification::centredBottom);
    inputLevelLabel.attachToComponent(&inputLevelSlider, false);
    addAndMakeVisible(inputLevelLabel);

    // === Dist ===
    distSlider.setSliderStyle(Slider::RotaryVerticalDrag);
    distSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    distSlider.setPopupDisplayEnabled(true, false, this);
    //distSlider.setLookAndFeel(&basicLookAndFeel);
    addAndMakeVisible(distSlider);
    mDistAttachement = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getAPVTS(), "DIST", distSlider);

    distLabel.setFont(controlFont);
    distLabel.setText("Dist", dontSendNotification);
    distLabel.setJustificationType(Justification::centredBottom);
    distLabel.attachToComponent(&distSlider, false);
    addAndMakeVisible(distLabel);

    // === Frequency ===
    frequencySlider.setSliderStyle(Slider::RotaryVerticalDrag);
    //frequencySlider.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 20);
    frequencySlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    frequencySlider.setPopupDisplayEnabled(true, false, this);
    //frequencySlider.setLookAndFeel(&basicLookAndFeel);
    addAndMakeVisible(frequencySlider);
    mFrequencyAttachement = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getAPVTS(), "FREQUENCY", frequencySlider);

    frequencyLabel.setFont(controlFont);
    frequencyLabel.setText("Frequency", dontSendNotification);
    frequencyLabel.setJustificationType(Justification::centredBottom);
    frequencyLabel.attachToComponent(&frequencySlider, false);
    addAndMakeVisible(frequencyLabel);

    // Scope stuff
    addAndMakeVisible(scopeComponent);
    auto area = getLocalBounds();
    scopeComponent.setTopLeftPosition(0, 110);
    scopeComponent.setSize(area.getWidth(), area.getHeight() - 130);
}

GgOverdriveEditor::~GgOverdriveEditor()
{
 
}

//==============================================================================
void GgOverdriveEditor::paint (Graphics& g)
{
    g.setColour(Colours::white);
    g.setFont(Font("Ariel", 15.0f, Font::bold));
    g.drawFittedText("Prototype Systech Overdrive Simulator", 0, 0, getWidth(), 30, Justification::centred, 1);
}

void GgOverdriveEditor::resized()
{
    int sliderLeft = 10;
    int sliderRow = 45;
    int w = 50;
    int h = 60;

    inputLevelSlider.setBounds(sliderLeft, sliderRow, w, h);
    frequencySlider.setBounds(sliderLeft + 70, sliderRow, w, h);
    distSlider.setBounds(sliderLeft + 140, sliderRow, w, h);
    levelSlider.setBounds(sliderLeft + 210, sliderRow, w, h);

}

