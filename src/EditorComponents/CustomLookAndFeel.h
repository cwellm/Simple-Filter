#pragma once

#include <JuceHeader.h>

namespace cw::Filter {

	class CustomLookAndFeel : public juce::LookAndFeel_V4 {
	public:
		CustomLookAndFeel() {}
		void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
			const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider&) override;

	private:
		static std::unique_ptr<juce::Image> sliderImage;
	};

} // cw::Filter