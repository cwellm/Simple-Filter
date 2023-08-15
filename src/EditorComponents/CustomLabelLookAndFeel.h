#pragma once

#include <JuceHeader.h>

namespace cw::Filter {
	class CustomLabelLookAndFeel : public juce::LookAndFeel_V4 {
	public:
		CustomLabelLookAndFeel() {}
		void drawLabel(juce::Graphics&, juce::Label&) override;
		

	};
} // cw::Filter