/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Processor.h"

#include "ParamIDs.h"

#include "EditorComponents/UpperRow.h"
#include "EditorComponents/LowerRow.h"
#include "EditorComponents/BottomArea.h"

//==============================================================================
/**
*/

using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

class Editor  : public juce::AudioProcessorEditor
{
public:
    Editor (Processor&, juce::AudioProcessorValueTreeState&);
    ~Editor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    /*juce::Component& getChildByName(std::string);*/

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    //Processor& audioProcessor;
    juce::AudioProcessorValueTreeState& apvts;

    cw::Filter::CenterFreqComponent centerFreqComponent;
    cw::Filter::BandwidthComponent bandwidthComponent;

    cw::Filter::UpperRowComponent upperRowComponent;
    cw::Filter::LowerRowComponent lowerRowComponent;
    cw::Filter::BottomAreaComponent bottomAreaComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Editor)
};
