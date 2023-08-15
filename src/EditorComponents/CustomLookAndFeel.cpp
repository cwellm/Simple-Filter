#include "CustomLookAndFeel.h"
#include "../Resources/SliderImg.h"
#include "../util/BinaryConversion.h" 

namespace cw::Filter {

	std::unique_ptr<juce::Image> CustomLookAndFeel::sliderImage{ nullptr };

	void CustomLookAndFeel::drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
		const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider& slider) {

		if (sliderImage.get() == nullptr) {
			juce::MemoryBlock block{};
			cw::utils::BinaryConversion::loadBinaryIntoMemoryBlock(block, SliderImg, std::size(SliderImg));
			auto img = juce::ImageFileFormat::loadFrom(block.getData(), block.getSize());
			sliderImage.reset(new juce::Image{ img.createCopy() });
		}

		if (!(*sliderImage).isValid()) {
			return;
		}

		auto sizes = juce::jmin(width, height);

		auto centreX = (float)x + (float)sizes * 0.5f;
		auto centreY = (float)y + (float)sizes * 0.5f;

		auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle) - 0.4;

		g.addTransform(juce::AffineTransform::translation(-centreX, -centreY).rotated(angle)
			.translated(centreX, centreY));

		g.setOpacity(1.0f);

		g.drawImage(*sliderImage, x, y, sizes, sizes, 0, 0, (*sliderImage).getWidth(), (*sliderImage).getHeight(), false);
	}

} // cw::Filter