#include "UpperRow.h"

#include <JuceHeader.h>
#include "../Processor.h"
#include "../ParamIDs.h"
#include "../util/BinaryConversion.h"
#include "../Resources/background.h"

namespace cw::Filter {

	std::unique_ptr<juce::Image> UpperRowComponent::bckg{ nullptr };

	UpperRowComponent::UpperRowComponent(juce::AudioProcessorValueTreeState& apvts) {
		setName("upperRow");

		// Cutoff Freq
		cutoffFreqComponent.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
		cutoffFreqComponent.setSliderStyle(juce::Slider::Rotary);
		cutoffFreqComponent.setTooltip(TRANS("Cutoff Frequency"));
		addAndMakeVisible(cutoffFreqComponent);
		slCutoffFrequencyAtt.reset(new SliderAttachment(apvts, IDCutoffFreq, cutoffFreqComponent));

		cutoffFreqComponent.setLookAndFeel(customLookAndFeel.get());

		// Steepness
		steepnessComponent.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
		steepnessComponent.setSliderStyle(juce::Slider::Rotary);
		steepnessComponent.setSkewFactor(0.7);
		steepnessComponent.setTooltip(TRANS("Steepness"));
		addAndMakeVisible(steepnessComponent);
		slSteepnessAtt.reset(new SliderAttachment(apvts, IDSteepness, steepnessComponent));

		steepnessComponent.setLookAndFeel(customLookAndFeel.get());

		// Labels
		cutoffFreqLabel.setText("Cutoff Frequency", juce::dontSendNotification);
		cutoffFreqLabel.setJustificationType(juce::Justification::centred);
		addAndMakeVisible(cutoffFreqLabel);

		steepnessLabel.setText("Steepness", juce::dontSendNotification);
		steepnessLabel.setJustificationType(juce::Justification::centred);
		addAndMakeVisible(steepnessLabel);
	}

	void UpperRowComponent::resized() {

		cutoffFreqComponent.setBounds(0, 0, proportionOfWidth(1. / 2), proportionOfHeight(9. / 10));
		steepnessComponent.setBounds(proportionOfWidth(1./2), 0, proportionOfWidth(1. / 2), proportionOfHeight(9. / 10));

		cutoffFreqLabel.setBounds(0, proportionOfHeight(9. / 10), proportionOfWidth(1. / 2), 
			proportionOfHeight(1. / 10));
		steepnessLabel.setBounds(proportionOfWidth(1./2), proportionOfHeight(9. / 10), proportionOfWidth(1. / 2),
			proportionOfHeight(1. / 10));
	}

	void UpperRowComponent::paint(juce::Graphics& g) {
		g.fillAll(juce::Colour(0xa1255a68));

		if (bckg.get() == nullptr) {
			juce::MemoryBlock block{};
			cw::utils::BinaryConversion::loadBinaryIntoMemoryBlock(block, BackgroundImg, std::size(BackgroundImg));
			auto img = juce::ImageFileFormat::loadFrom(block.getData(), block.getSize());
			bckg.reset(new juce::Image{ img.createCopy() });
		}

		auto bounds = getLocalBounds();
		g.drawImage(*bckg, juce::Rectangle<float>{(float)bounds.getX(), 
			(float)bounds.getY(), (float)bounds.getWidth(), (float)bounds.getHeight()},
			juce::RectanglePlacement::fillDestination
		);
	}

} // cw::Filter