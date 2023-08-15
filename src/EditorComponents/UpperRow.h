#pragma once

#include <JuceHeader.h>
#include "../Processor.h"

#include "CutoffFreqComponent.h"
#include "SteepnessComponent.h"
#include "CustomLookAndFeel.h"

using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

namespace cw::Filter {

	class UpperRowComponent : public juce::Component {
	public:
		UpperRowComponent(juce::AudioProcessorValueTreeState&);
		void resized() override;
		void paint(juce::Graphics& g) override;

	private:
		CutoffFreqComponent cutoffFreqComponent;
		std::unique_ptr<SliderAttachment> slCutoffFrequencyAtt = nullptr;

		SteepnessComponent steepnessComponent;
		std::unique_ptr<SliderAttachment> slSteepnessAtt = nullptr;

		std::unique_ptr<CustomLookAndFeel> customLookAndFeel{ std::make_unique<CustomLookAndFeel>() };

		juce::Label cutoffFreqLabel;
		juce::Label steepnessLabel;

		static std::unique_ptr<juce::Image> bckg;
	};

} // cw::Filter