/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginEditor.h"
#include "PluginProcessor.h"

//==============================================================================
SmplcompAudioProcessorEditor::SmplcompAudioProcessorEditor(SmplcompAudioProcessor &p,
                                                           juce::AudioProcessorValueTreeState &vts)
    : juce::AudioProcessorEditor(&p), processor(p), valueTreeState(vts),
      backgroundApp(juce::Colour(Constants::Colors::bg_App)), inGainLSlider(this), makeupGainLSlider(this),
      threshLSlider(this), ratioLSlider(this), kneeLSlider(this), attackLSlider(this), releaseLSlider(this),
      mixLSlider(this)
{
    setLookAndFeel(&LAF);
    initWidgets();
    setSize(400, 260);
    startTimerHz(60);
}

SmplcompAudioProcessorEditor::~SmplcompAudioProcessorEditor()
{
    setLookAndFeel(nullptr);
}

//==============================================================================
void SmplcompAudioProcessorEditor::paint(juce::Graphics &g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(backgroundApp);
}

void SmplcompAudioProcessorEditor::resized()
{
    auto area = getLocalBounds().reduced(Constants::Margins::big);

    const auto btnAreaWidth = area.getWidth() / 5;
    const auto btnBotHeight = area.getHeight() / 3;

    auto lBtnArea = area.removeFromLeft(btnAreaWidth).reduced(Constants::Margins::small);
    auto rBtnArea = area.removeFromRight(btnAreaWidth).reduced(Constants::Margins::small);
    auto botBtnArea = area.removeFromBottom(btnBotHeight).reduced(Constants::Margins::medium);

    const juce::FlexItem::Margin knobMarginSmall = juce::FlexItem::Margin(Constants::Margins::medium);

    juce::FlexBox leftBtnBox;
    leftBtnBox.flexWrap = juce::FlexBox::Wrap::noWrap;
    leftBtnBox.flexDirection = juce::FlexBox::Direction::column;
    leftBtnBox.justifyContent = juce::FlexBox::JustifyContent::spaceAround;
    leftBtnBox.items.add(juce::FlexItem(attackLSlider).withFlex(1).withMargin(knobMarginSmall));
    leftBtnBox.items.add(juce::FlexItem(releaseLSlider).withFlex(1).withMargin(knobMarginSmall));
    leftBtnBox.items.add(juce::FlexItem(inGainLSlider).withFlex(1).withMargin(knobMarginSmall));
    leftBtnBox.performLayout(lBtnArea.toFloat());

    juce::FlexBox rightBtnBox;
    rightBtnBox.flexWrap = juce::FlexBox::Wrap::noWrap;
    rightBtnBox.flexDirection = juce::FlexBox::Direction::column;
    rightBtnBox.justifyContent = juce::FlexBox::JustifyContent::spaceAround;
    rightBtnBox.items.add(juce::FlexItem(kneeLSlider).withFlex(1).withMargin(knobMarginSmall));
    rightBtnBox.items.add(juce::FlexItem(ratioLSlider).withFlex(1).withMargin(knobMarginSmall));
    rightBtnBox.items.add(juce::FlexItem(mixLSlider).withFlex(1).withMargin(knobMarginSmall));
    rightBtnBox.performLayout(rBtnArea.toFloat());

    juce::FlexBox botBtnBox;
    botBtnBox.flexWrap = juce::FlexBox::Wrap::noWrap;
    botBtnBox.flexDirection = juce::FlexBox::Direction::row;
    botBtnBox.justifyContent = juce::FlexBox::JustifyContent::spaceAround;
    botBtnBox.items.add(juce::FlexItem(threshLSlider).withFlex(1));
    botBtnBox.items.add(juce::FlexItem(makeupGainLSlider).withFlex(1));
    botBtnBox.performLayout(botBtnArea.toFloat());

    juce::FlexBox meterBox;
    meterBox.flexWrap = juce::FlexBox::Wrap::noWrap;
    meterBox.justifyContent = juce::FlexBox::JustifyContent::spaceAround;
    meterBox.items.add(juce::FlexItem(meter).withFlex(1).withMargin(Constants::Margins::big));
    meterBox.performLayout(area.toFloat());
}

void SmplcompAudioProcessorEditor::timerCallback()
{
    int m = meter.getMode();
    switch (m)
    {
    case Meter::Mode::IN:
        meter.update(processor.currentInput);
        break;
    case Meter::Mode::OUT:
        meter.update(processor.currentOutput);
        break;
    case Meter::Mode::GR:
        meter.update(processor.gainReduction);
        break;
    default:
        break;
    }
}

void SmplcompAudioProcessorEditor::initWidgets()
{
    addAndMakeVisible(inGainLSlider);
    inGainLSlider.reset(valueTreeState, "inputgain");
    inGainLSlider.setLabelText("Input");

    addAndMakeVisible(makeupGainLSlider);
    makeupGainLSlider.reset(valueTreeState, "makeup");
    makeupGainLSlider.setLabelText("Makeup");

    addAndMakeVisible(threshLSlider);
    threshLSlider.reset(valueTreeState, "threshold");
    threshLSlider.setLabelText("Threshold");

    addAndMakeVisible(ratioLSlider);
    ratioLSlider.reset(valueTreeState, "ratio");
    ratioLSlider.setLabelText("Ratio");

    addAndMakeVisible(kneeLSlider);
    kneeLSlider.reset(valueTreeState, "knee");
    kneeLSlider.setLabelText("Knee");

    addAndMakeVisible(attackLSlider);
    attackLSlider.reset(valueTreeState, "attack");
    attackLSlider.setLabelText("Attack");

    addAndMakeVisible(releaseLSlider);
    releaseLSlider.reset(valueTreeState, "release");
    releaseLSlider.setLabelText("Release");

    addAndMakeVisible(mixLSlider);
    mixLSlider.reset(valueTreeState, "mix");
    mixLSlider.setLabelText("Mix");

    addAndMakeVisible(meter);
    meter.setMode(Meter::Mode::GR);
}
