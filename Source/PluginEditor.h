/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "PluginProcessor.h"
#include "gui/LabeledSlider.h"
#include "gui/Meter.h"
#include "gui/MeterBackground.h"
#include "gui/SMPLCompLookAndFeel.h"
#include <juce_gui_extra/juce_gui_extra.h>

//==============================================================================
/**
 */
class SmplcompAudioProcessorEditor : public juce::AudioProcessorEditor, juce::Timer
{
  public:
    SmplcompAudioProcessorEditor(SmplcompAudioProcessor &, juce::AudioProcessorValueTreeState &);
    ~SmplcompAudioProcessorEditor();

    //==============================================================================
    void paint(juce::Graphics &) override;
    void resized() override;
    void timerCallback() override;
    void initWidgets();

  private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SmplcompAudioProcessor &processor;
    juce::AudioProcessorValueTreeState &valueTreeState;

    SMPLCompLookAndFeel LAF;

    juce::Colour backgroundApp;

    // Widgets
    MeterBackground meterbg;
    Meter meter;
    LabeledSlider inGainLSlider;
    LabeledSlider makeupGainLSlider;
    LabeledSlider threshLSlider;
    LabeledSlider ratioLSlider;
    LabeledSlider kneeLSlider;
    LabeledSlider attackLSlider;
    LabeledSlider releaseLSlider;
    LabeledSlider mixLSlider;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SmplcompAudioProcessorEditor)
};
