#include <JuceHeader.h>
#include "../Processor.h"

#include "LowerRow.h"
#include "../ParamIDs.h"
#include "../util/BinaryConversion.h"
#include "../Resources/background.h"

namespace cw::Filter {

	std::unique_ptr<juce::Image> LowerRowComponent::bckg{ nullptr };

	LowerRowComponent::LowerRowComponent(juce::AudioProcessorValueTreeState& apvts) {
		setName("lowerRow");

		// Center Freq
		centerFreqComponent.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
		centerFreqComponent.setSliderStyle(juce::Slider::Rotary);
		centerFreqComponent.setTooltip(TRANS("Center Frequency"));
		addAndMakeVisible(centerFreqComponent);
		slCenterFreqAtt.reset(new SliderAttachment(apvts, IDCenterFrequency, centerFreqComponent));

		centerFreqComponent.setLookAndFeel(customLookAndFeel.get());
		centerFreqComponent.addListener(this);

		// Bandwidth
		bandwidthComponent.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
		bandwidthComponent.setSliderStyle(juce::Slider::Rotary);
		bandwidthComponent.setTooltip(TRANS("Bandwidth"));
		addAndMakeVisible(bandwidthComponent);
		slBandwidthAtt.reset(new SliderAttachment(apvts, IDBandwidth, bandwidthComponent));

		bandwidthComponent.setLookAndFeel(customLookAndFeel.get());
		bandwidthComponent.addListener(this);

		// Labels
		centerFreqLabel.setText("Center Frequency", juce::dontSendNotification);
		centerFreqLabel.setJustificationType(juce::Justification::centred);
		addAndMakeVisible(centerFreqLabel);

		bandwidthLabel.setText("Bandwidth", juce::dontSendNotification);
		bandwidthLabel.setJustificationType(juce::Justification::centred);
		addAndMakeVisible(bandwidthLabel);
	}

	void LowerRowComponent::resized() {

		centerFreqComponent.setBounds(0, 0, proportionOfWidth(1. / 2), proportionOfHeight(9. / 10));
		bandwidthComponent.setBounds(proportionOfWidth(1. / 2), 0, proportionOfWidth(1. / 2), 
			proportionOfHeight(9. / 10));

		centerFreqLabel.setBounds(0, proportionOfHeight(9. / 10), proportionOfWidth(1. / 2),
			proportionOfHeight(1. / 10));
		bandwidthLabel.setBounds(proportionOfWidth(1. / 2), proportionOfHeight(9. / 10), proportionOfWidth(1. / 2),
			proportionOfHeight(1. / 10));
	}

	void LowerRowComponent::paint(juce::Graphics& g) {
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

	void LowerRowComponent::sliderValueChanged(juce::Slider* slider) {
		float centerFreqVal = centerFreqComponent.getValue();
		float bandwidthVal = bandwidthComponent.getValue();
		float lowerCutoff = centerFreqVal - 1. / 2 * bandwidthVal;
		float upperCutoff = centerFreqVal + 1. / 2 * bandwidthVal;

		if (slider == &bandwidthComponent) {
			if (lowerCutoff < 20.) {
				bandwidthComponent.setValue(2.*(centerFreqVal - 20.));
			}
			if (upperCutoff > 20000.) {
				bandwidthComponent.setValue(2. * (20000. - centerFreqVal));
			}
		}

		if (slider == &centerFreqComponent) {
			if (lowerCutoff < 20.) {
				centerFreqComponent.setValue(20. + 1. / 2 * bandwidthVal);
			}
			if (upperCutoff > 20000.) {
				centerFreqComponent.setValue(20000. - 1. / 2 * bandwidthVal);
			}
		}
	}

} // cw::Filter
