/*
  ==============================================================================

  Editor for Systech Overdrive Pedal Simulator

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
GgOverdriveEditor::GgOverdriveEditor (GgOverdriveProcessor& p)
    : AudioProcessorEditor (&p), processor (p), scopeComponent(processor.getAudioBufferQueue())
{

    setSize (200, 250);

    Font controlFont("Ariel", 13.0f, Font::plain);
    Colour controlColour = Colours::black;

    // === Output level ===
    levelSlider.setSliderStyle(Slider::RotaryVerticalDrag);
    levelSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    levelSlider.setPopupDisplayEnabled(true, false, this);
    //levelSlider.setLookAndFeel(&basicLookAndFeel);
    addAndMakeVisible(levelSlider);
    mLevelAttachement = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getAPVTS(), "LEVEL", levelSlider);

    levelLabel.setFont(controlFont);
    levelLabel.setColour(Label::textColourId, controlColour);
    levelLabel.setText("level out", dontSendNotification);
    levelLabel.setJustificationType(Justification::centredBottom);
    levelLabel.attachToComponent(&levelSlider, false);
    addAndMakeVisible(levelLabel);

    // == Input level ==
    inputLevelSlider.setSliderStyle(Slider::RotaryVerticalDrag);
    inputLevelSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    inputLevelSlider.setPopupDisplayEnabled(true, false, this);
    //inputLevelSlider.setLookAndFeel(&basicLookAndFeel);
    addAndMakeVisible(inputLevelSlider);
    mInputLevelAttachement = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getAPVTS(), "INPUTLEVEL", inputLevelSlider);

    inputLevelLabel.setFont(controlFont);
    inputLevelLabel.setColour(Label::textColourId, controlColour);
    inputLevelLabel.setText("level in", dontSendNotification);
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
    distLabel.setColour(Label::textColourId, controlColour);
    distLabel.setText("distortion", dontSendNotification);
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
    frequencyLabel.setColour(Label::textColourId, controlColour);
    frequencyLabel.setText("eq", dontSendNotification);
    frequencyLabel.setJustificationType(Justification::centredBottom);
    frequencyLabel.attachToComponent(&frequencySlider, false);
    addAndMakeVisible(frequencyLabel);

    //// Scope stuff
    //addAndMakeVisible(scopeComponent);
    //auto area = getLocalBounds();
    //scopeComponent.setTopLeftPosition(0, 120);
    //scopeComponent.setSize(area.getWidth(), area.getHeight() - 120);
}

GgOverdriveEditor::~GgOverdriveEditor()
{
 
}

//==============================================================================
void GgOverdriveEditor::paint (Graphics& g)
{
    auto area = getLocalBounds();
    int aw = area.getWidth();
    int ah = area.getHeight();
    g.drawRect(area, 1.f);
    Rectangle<int> topFrame = area.withTrimmedBottom(ah - 40);

    g.setColour(Colours::lightgrey);
    g.fillRect(topFrame);
    g.setColour(Colours::black);
    //g.drawRect(topFrame, 1.f);
    
    g.setColour(Colours::black);
    g.setFont(Font("Ariel", 16.0f, Font::bold));
    g.drawFittedText("Systech Overdrive Simulator", topFrame, Justification::centred, 1);

    Rectangle<int> controlsFrame = Rectangle<int>(0, topFrame.getHeight(), aw, 80);
    g.setColour(Colours::lightblue);
    g.fillRect(controlsFrame);
    g.setColour(Colours::black);
    //g.drawRect(controlsFrame, 1.f);

    Rectangle<int> bottomFrame = Rectangle<int>(0, controlsFrame.getHeight() + topFrame.getHeight(), aw, ah - controlsFrame.getHeight() - topFrame.getHeight());
    g.setColour(Colours::lightgrey);
    g.fillRect(bottomFrame);
    //g.drawRect(bottomFrame, 1.f);

    g.setColour(Colours::darkgrey);
    g.drawRect(area, 1.f);
}

void GgOverdriveEditor::resized()
{
    auto area = getLocalBounds();
    int sliderLeft = area.getWidth() - 200;
    int sliderRow = 60;
    int w = 50;
    int h = 60;

    inputLevelSlider.setBounds(sliderLeft, sliderRow, w, h);
    frequencySlider.setBounds(sliderLeft + 50, sliderRow, w, h);
    distSlider.setBounds(sliderLeft + 100, sliderRow, w, h);
    levelSlider.setBounds(sliderLeft + 150, sliderRow, w, h);

}

