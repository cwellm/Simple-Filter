/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "Processor.h"
#include "Editor.h"

#include <stdexcept>

//==============================================================================
Editor::Editor (Processor& p, juce::AudioProcessorValueTreeState& apvts)
    : AudioProcessorEditor (&p), 
        apvts(apvts),
        upperRowComponent(apvts),
        lowerRowComponent(apvts),
        bottomAreaComponent(apvts)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 500);
    p.isMidiEffect();

    // Upper Row
    addAndMakeVisible(upperRowComponent);

    // Lower Row
    addAndMakeVisible(lowerRowComponent);

    // Bottom Area (choosing filter type)
    addAndMakeVisible(bottomAreaComponent);
}

Editor::~Editor()
{

}

//==============================================================================
void Editor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)

}

void Editor::resized()
{
    auto localBounds = getLocalBounds();
    auto localHeight = localBounds.getHeight();
    auto localWidth = localBounds.getWidth();

    auto upperRow = localBounds.removeFromTop(2./5 * localHeight);
    auto lowerRow = localBounds.removeFromTop(2./5 * localHeight);
    auto bottomArea = localBounds;

    upperRowComponent.setBounds(upperRow);
    lowerRowComponent.setBounds(lowerRow);
    bottomAreaComponent.setBounds(bottomArea);

}

/*
juce::Component& Editor::getChildByName(std::string name) {
    if (name == "upperRow") {
        return upperRowComponent;
    }
    if (name == "lowerRow") {
        return lowerRowComponent;
    }
    if (name == "bottom") {
        return bottomAreaComponent;
    }
    throw std::invalid_argument("Component name unknown.");
} */