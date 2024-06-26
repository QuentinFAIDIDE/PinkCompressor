/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "dsp/Compressor.h"
#include "dsp/Filter.h"
#include "dsp/LevelEnvelopeFollower.h"
#include <juce_audio_processors/juce_audio_processors.h>

class SmplcompAudioProcessor : public juce::AudioProcessor, public juce::AudioProcessorValueTreeState::Listener
{
  public:
    SmplcompAudioProcessor();
    ~SmplcompAudioProcessor();

    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

#ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported(const BusesLayout &layouts) const override;
#endif

    void processBlock(juce::AudioBuffer<float> &, juce::MidiBuffer &) override;

    juce::AudioProcessorEditor *createEditor() override;
    bool hasEditor() const override;

    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram(int index) override;
    const juce::String getProgramName(int index) override;
    void changeProgramName(int index, const juce::String &newName) override;

    void getStateInformation(juce::MemoryBlock &destData) override;
    void setStateInformation(const void *data, int sizeInBytes) override;

    void parameterChanged(const juce::String &parameterID, float newValue) override;
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();

    std::atomic<float> gainReduction;
    std::atomic<float> currentInput;
    std::atomic<float> currentOutput;

  private:
    juce::AudioProcessorValueTreeState parameters;
    Compressor compressor;
    Filter pinkToWhiteFilterLeft;
    Filter whiteToPinkFilterLeft;
    Filter pinkToWhiteFilterRight;
    Filter whiteToPinkFilterRight;
    LevelEnvelopeFollower inLevelFollower;
    LevelEnvelopeFollower outLevelFollower;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SmplcompAudioProcessor)
};
