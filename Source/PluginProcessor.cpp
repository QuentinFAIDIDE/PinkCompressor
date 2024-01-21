/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SmplcompAudioProcessor::SmplcompAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
#if !JucePlugin_IsMidiEffect
#if !JucePlugin_IsSynth
                         .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
                         .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
                         ),
      parameters(*this, nullptr, "PARAMETERS", createParameterLayout())
#endif
{
    // Add parameter listener
    parameters.addParameterListener("inputgain", this);
    parameters.addParameterListener("makeup", this);
    parameters.addParameterListener("threshold", this);
    parameters.addParameterListener("ratio", this);
    parameters.addParameterListener("knee", this);
    parameters.addParameterListener("attack", this);
    parameters.addParameterListener("release", this);
    parameters.addParameterListener("mix", this);

    gainReduction = 0.0f;
    currentInput = -std::numeric_limits<float>::infinity();
    currentOutput = -std::numeric_limits<float>::infinity();
}

SmplcompAudioProcessor::~SmplcompAudioProcessor()
{
}

const juce::String SmplcompAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SmplcompAudioProcessor::acceptsMidi() const
{
    return false;
}

bool SmplcompAudioProcessor::producesMidi() const
{
    return false;
}

bool SmplcompAudioProcessor::isMidiEffect() const
{
    return false;
}

double SmplcompAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SmplcompAudioProcessor::getNumPrograms()
{
    return 1; // NB: some hosts don't cope very well if you tell them there are 0 programs,
    // so this should be at least 1, even if you're not really implementing programs.
}

int SmplcompAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SmplcompAudioProcessor::setCurrentProgram(int)
{
}

const juce::String SmplcompAudioProcessor::getProgramName(int)
{
    return {};
}

void SmplcompAudioProcessor::changeProgramName(int, const juce::String &)
{
}

void SmplcompAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    // Prepare dsp classes
    compressor.prepare({sampleRate, static_cast<juce::uint32>(samplesPerBlock), 2});
    inLevelFollower.prepare(sampleRate);
    outLevelFollower.prepare(sampleRate);

    // Set envelope follower for level meter to measure over 300ms time frame
    inLevelFollower.setPeakDecay(0.3f);
    outLevelFollower.setPeakDecay(0.3f);
}

void SmplcompAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

bool SmplcompAudioProcessor::isBusesLayoutSupported(const BusesLayout &layouts) const
{
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono() &&
        layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
    {
        return false;
    }

    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
    {
        return false;
    }

    return true;
}

void SmplcompAudioProcessor::processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer &)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    const auto numSamples = buffer.getNumSamples();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    // Update input peak metering
    inLevelFollower.updatePeak(buffer.getArrayOfReadPointers(), totalNumInputChannels, numSamples);
    currentInput = juce::Decibels::gainToDecibels(inLevelFollower.getPeak());

    // Do compressor processing
    compressor.process(buffer);

    // Update gain reduction metering
    gainReduction = compressor.getMaxGainReduction();

    // Update output peak metering
    outLevelFollower.updatePeak(buffer.getArrayOfReadPointers(), totalNumInputChannels, numSamples);
    currentOutput = juce::Decibels::gainToDecibels(outLevelFollower.getPeak());
}

//==============================================================================
bool SmplcompAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor *SmplcompAudioProcessor::createEditor()
{
    return new SmplcompAudioProcessorEditor(*this, parameters);
}

//==============================================================================
void SmplcompAudioProcessor::getStateInformation(juce::MemoryBlock &)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SmplcompAudioProcessor::setStateInformation(const void *, int)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor *JUCE_CALLTYPE createPluginFilter()
{
    return new SmplcompAudioProcessor();
}

void SmplcompAudioProcessor::parameterChanged(const juce::String &parameterID, float newValue)
{
    if (parameterID == "inputgain")
        compressor.setInput(newValue);
    else if (parameterID == "threshold")
        compressor.setThreshold(newValue);
    else if (parameterID == "ratio")
        compressor.setRatio(newValue);
    else if (parameterID == "knee")
        compressor.setKnee(newValue);
    else if (parameterID == "attack")
        compressor.setAttack(newValue);
    else if (parameterID == "release")
        compressor.setRelease(newValue);
    else if (parameterID == "makeup")
        compressor.setMakeup(newValue);
    else if (parameterID == "mix")
        compressor.setMix(newValue);
}

juce::AudioProcessorValueTreeState::ParameterLayout SmplcompAudioProcessor::createParameterLayout()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    params.push_back(std::make_unique<juce::AudioParameterBool>("power", "Power", true));

    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        "inputgain", "Input",
        juce::NormalisableRange<float>(Constants::Parameter::inputStart, Constants::Parameter::inputEnd,
                                       Constants::Parameter::inputInterval),
        0.0f, juce::String(), juce::AudioProcessorParameter::genericParameter,
        [](float value, float) { return juce::String(value, 1) + " dB"; }));

    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        "threshold", "Tresh",
        juce::NormalisableRange<float>(Constants::Parameter::thresholdStart, Constants::Parameter::thresholdEnd,
                                       Constants::Parameter::thresholdInterval),
        -10.0f, juce::String(), juce::AudioProcessorParameter::genericParameter,
        [](float value, float) { return juce::String(value, 1) + " dB"; }));

    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        "ratio", "Ratio",
        juce::NormalisableRange<float>(Constants::Parameter::ratioStart, Constants::Parameter::ratioEnd,
                                       Constants::Parameter::ratioInterval, 0.5f),
        2.0f, juce::String(), juce::AudioProcessorParameter::genericParameter, [](float value, float) {
            if (value > 23.9f)
                return juce::String("Infinity") + ":1";
            return juce::String(value, 1) + ":1";
        }));

    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        "knee", "Knee",
        juce::NormalisableRange<float>(Constants::Parameter::kneeStart, Constants::Parameter::kneeEnd,
                                       Constants::Parameter::kneeInterval),
        6.0f, juce::String(), juce::AudioProcessorParameter::genericParameter,
        [](float value, float) { return juce::String(value, 1) + " dB"; }));

    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        "attack", "Attack",
        juce::NormalisableRange<float>(Constants::Parameter::attackStart, Constants::Parameter::attackEnd,
                                       Constants::Parameter::attackInterval, 0.5f),
        2.0f, "ms", juce::AudioProcessorParameter::genericParameter, [](float value, float) {
            if (value == 100.0f)
                return juce::String(value, 0) + " ms";
            return juce::String(value, 2) + " ms";
        }));

    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        "release", "Release",
        juce::NormalisableRange<float>(Constants::Parameter::releaseStart, Constants::Parameter::releaseEnd,
                                       Constants::Parameter::releaseInterval, 0.35f),
        140.0f, juce::String(), juce::AudioProcessorParameter::genericParameter, [](float value, float) {
            if (value <= 100)
                return juce::String(value, 2) + " ms";
            if (value >= 1000)
                return juce::String(value * 0.001f, 2) + " s";
            return juce::String(value, 1) + " ms";
        }));

    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        "makeup", "Makeup",
        juce::NormalisableRange<float>(Constants::Parameter::makeupStart, Constants::Parameter::makeupEnd,
                                       Constants::Parameter::makeupInterval),
        0.0f, juce::String(), juce::AudioProcessorParameter::genericParameter,
        [](float value, float) { return juce::String(value, 1) + " dB "; }));

    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        "mix", "Mix",
        juce::NormalisableRange<float>(Constants::Parameter::mixStart, Constants::Parameter::mixEnd,
                                       Constants::Parameter::mixInterval),
        1.0f, "%", juce::AudioProcessorParameter::genericParameter,
        [](float value, float) { return juce::String(value * 100.0f, 1) + " %"; }));

    return {params.begin(), params.end()};
}
