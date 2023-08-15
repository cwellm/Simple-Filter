#pragma once

#include <JuceHeader.h>
#include "../Processor.h"

#include "CenterFreqComponent.h"
#include "BandwidthComponent.h"
#include "CustomLookAndFeel.h"

using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

namespace cw::Filter {

	class LowerRowComponent : public juce::Component, juce::Slider::Listener {
	public:
		LowerRowComponent(juce::AudioProcessorValueTreeState&);
		void resized() override;
		void paint(juce::Graphics&) override;
		void sliderValueChanged(juce::Slider*) override;

	private:
		CenterFreqComponent centerFreqComponent;
		std::unique_ptr<SliderAttachment> slCenterFreqAtt = nullptr;

		BandwidthComponent bandwidthComponent;
		std::unique_ptr<SliderAttachment> slBandwidthAtt = nullptr;

		std::unique_ptr<CustomLookAndFeel> customLookAndFeel{ std::make_unique<CustomLookAndFeel>() };

		juce::Label centerFreqLabel;
		juce::Label bandwidthLabel;

		static std::unique_ptr<juce::Image> bckg;
	};

} // cw::Filter