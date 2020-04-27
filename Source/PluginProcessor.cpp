/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
GgOverdriveProcessor::GgOverdriveProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ), mAPVTS(*this, nullptr, "PARAMETERS", createParameters())
#endif
{
    mAPVTS.state.addListener(this);
}

GgOverdriveProcessor::~GgOverdriveProcessor()
{
}

//==============================================================================
const String GgOverdriveProcessor::getName() const
{
    return JucePlugin_Name;
}

bool GgOverdriveProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool GgOverdriveProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool GgOverdriveProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double GgOverdriveProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int GgOverdriveProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int GgOverdriveProcessor::getCurrentProgram()
{
    return 0;
}

void GgOverdriveProcessor::setCurrentProgram (int index)
{
}

const String GgOverdriveProcessor::getProgramName (int index)
{
    return {};
}

void GgOverdriveProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void GgOverdriveProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    mSampleRate = sampleRate;
    updateParams();

    dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = uint32(samplesPerBlock);
    spec.numChannels = uint32(getTotalNumOutputChannels());
    processorChain.prepare(spec);

    mCurrentFilterFrequency = mFrequency;
    mCurrentDistortion = mDistortion;
    //mCurrentLevel = mLevel;

    setFrequencyFilterData(true);
    setOutputLevelData();
}

void GgOverdriveProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool GgOverdriveProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
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

void GgOverdriveProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    ignoreUnused(midiMessages);
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // Clear output channels if there are more than input channels 
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    if (mParamsHaveBeenUpdatedInGUI) {  // varför gör jag inte det här i valueTreePropertyChanged??
        updateParams();
        setFrequencyFilterData();
        setOutputLevelData();
        mParamsHaveBeenUpdatedInGUI = false;
    }

    dsp::AudioBlock<float> ioBuffer(buffer);
    dsp::ProcessContextReplacing<float> context(ioBuffer);
    processorChain.process(context);
}

AudioProcessorValueTreeState::ParameterLayout GgOverdriveProcessor::createParameters() {
    std::vector<std::unique_ptr<RangedAudioParameter>> parameters;

    const float maxGain = Decibels::decibelsToGain(12.f);

    parameters.push_back(std::make_unique<AudioParameterFloat>("FREQUENCY", "eq",
        NormalisableRange<float> {200.f,
        900.f,
        1.0f, std::log(0.5f) / std::log((350.f - 200.f) / (900.f - 200.f))},
        350.f,
        String(),
        AudioProcessorParameter::genericParameter,
        [](float value, int) { return (value < 1000) ? String(value, 0) + " Hz" : String(value / 1000.0, 2) + " kHz"; },
        [](String text) { return text.endsWith(" kHz") ? text.dropLastCharacters(4).getFloatValue() * 1000.0 : text.dropLastCharacters(3).getFloatValue(); }));

    parameters.push_back(std::make_unique<AudioParameterFloat>("DIST", "distortion",
        NormalisableRange<float> {1.0f / maxGain, maxGain, 0.001f,
        std::log(0.5f) / std::log((1.0f - (1.0f / maxGain)) / (maxGain - (1.0f / maxGain)))},
        1.f,
        String(),
        AudioProcessorParameter::genericParameter,
        [](float value, int) {return String(Decibels::gainToDecibels(value), 1) + " dB"; },
        [](String text) {return Decibels::decibelsToGain(text.dropLastCharacters(3).getFloatValue()); }));

    parameters.push_back(std::make_unique<AudioParameterFloat>("LEVEL", "gain",
        NormalisableRange<float> {1.0f / maxGain, maxGain, 0.001f,
        std::log(0.5f) / std::log((1.0f - (1.0f / maxGain)) / (maxGain - (1.0f / maxGain)))},
        1.f,
        String(),
        AudioProcessorParameter::genericParameter,
        [](float value, int) {return String(Decibels::gainToDecibels(value), 1) + " dB"; },
        [](String text) {return Decibels::decibelsToGain(text.dropLastCharacters(3).getFloatValue()); }));

    return { parameters.begin(), parameters.end() };
}

void GgOverdriveProcessor::updateParams() {
    mLevel = mAPVTS.getRawParameterValue("LEVEL")->load();
    mDistortion = mAPVTS.getRawParameterValue("DIST")->load();
    mFrequency = mAPVTS.getRawParameterValue("FREQUENCY")->load();
    
}

void GgOverdriveProcessor::setFrequencyFilterData(bool firstTime) {
    if (firstTime || mCurrentFilterFrequency != mFrequency) {
        mFilterQ = 4;  // Fix this to be a function of the frequency. Logartithmic or so. 4 (200 Hz) - 14 (800 Hz)
        // .state has to do with that the filter is duplicated
        auto& frequencyFilter = processorChain.get<frequencyIndex>().state;
        dsp::IIR::Coefficients<float>::Ptr newCoefficients = dsp::IIR::Coefficients<float>::makeBandPass(mSampleRate, mFrequency, mFilterQ);
        *frequencyFilter = *newCoefficients;
        mCurrentFilterFrequency = mFrequency;
    }
}

void GgOverdriveProcessor::setOutputLevelData() {
    auto& level = processorChain.get<levelIndex>();
    level.setGainLinear(mLevel);
}

void GgOverdriveProcessor::valueTreePropertyChanged(ValueTree& treeWhosePropertyHasChanged, const Identifier& property) {
    mParamsHaveBeenUpdatedInGUI = true;
}

//==============================================================================
bool GgOverdriveProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* GgOverdriveProcessor::createEditor()
{
    return new GgOverdriveEditor (*this);
}

//==============================================================================
void GgOverdriveProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
        // Run updateParams() to make sure latest GUI params have been fecthed (in case of "Reset to factory")
    updateParams();
    auto state = getAPVTS().copyState();
    std::unique_ptr<XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);

}

void GgOverdriveProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    std::unique_ptr<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName(getAPVTS().state.getType()))
            getAPVTS().replaceState(ValueTree::fromXml(*xmlState));

}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new GgOverdriveProcessor();
}
