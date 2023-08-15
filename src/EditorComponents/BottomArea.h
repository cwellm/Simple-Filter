#pragma once

#include <JuceHeader.h>
#include "../Processor.h"

#include "../ParamIDs.h"

using ComboBoxAttachment = juce::AudioProcessorValueTreeState::ComboBoxAttachment;

namespace cw::Filter {

	class BottomAreaComponent : public juce::Component, juce::ComboBox::Listener {
	public:
		BottomAreaComponent(juce::AudioProcessorValueTreeState&);
		void resized() override;
		//  ------------ todo: include some testing flag /variable to only compile this if it is set ------------ 
		//void paint(juce::Graphics&) override;
		// -----------------------------------

		void comboBoxChanged(ComboBox*) override;

	private:
		juce::ComboBox filterTypeChoice;
		std::unique_ptr<ComboBoxAttachment> cbFilterTypeChoiceAtt = nullptr;
		
	};

} // cw::Filter