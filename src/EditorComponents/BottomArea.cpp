#include <JuceHeader.h>
#include "../Processor.h"

#include "BottomArea.h"

namespace cw::Filter {

	BottomAreaComponent::BottomAreaComponent(juce::AudioProcessorValueTreeState& apvts) {
		// Filter Type Choice
		filterTypeChoice.addItemList(filterTypeChoiceItems, 1);
		filterTypeChoice.setSelectedId(1);
		addAndMakeVisible(filterTypeChoice);
		filterTypeChoice.addListener(this);
		cbFilterTypeChoiceAtt.reset(new ComboBoxAttachment(apvts, IDFilterType, filterTypeChoice));

		setName("bottomArea");
	}

	void BottomAreaComponent::resized() {
		auto localBounds = getLocalBounds();
		auto localWidth = localBounds.getWidth();
		auto localHeight = localBounds.getHeight();

		float deltaX = localWidth * 8.5 / 20;
		float deltaY = localHeight * 6.5 / 20;
		auto choiceArea = localBounds.reduced(deltaX, deltaY);
		filterTypeChoice.setBounds(choiceArea);
	}

	//  ------------ todo: include some testing flag /variable to only compile this if it is set ------------ 
	/*
	void BottomAreaComponent::paint(juce::Graphics& g) {
		g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
		g.drawText("Selected Item index:" + std::to_string(filterTypeChoice.getSelectedItemIndex()),
			getLocalBounds(), juce::Justification::centredTop);
		g.drawText("Selected Item ID:" + std::to_string(filterTypeChoice.getSelectedId()),
			getLocalBounds(), juce::Justification::centred);
		g.drawText("Name of Item: " + filterTypeChoiceItems[filterTypeChoice.getSelectedItemIndex()],
			getLocalBounds(), juce::Justification::centredBottom);
	} */
	// -----------------------------------

	void BottomAreaComponent::comboBoxChanged(ComboBox* comboBox) {
		int selectedId = comboBox->getSelectedId();

		if (comboBox == &filterTypeChoice) {
			auto parent = this->getParentComponent();
			if (parent == nullptr) {
				return;
			}
			auto parentsChildren = parent->getChildren();
			auto it = parentsChildren.begin();

			if (selectedId == 1 || selectedId == 2) {
				while (it != parentsChildren.end()) {
					if ((*it)->getName() == "upperRow") {
						(*it)->setEnabled(true);
					}
					if ((*it)->getName() == "lowerRow") {
						(*it)->setEnabled(false);
					}
					++it;
				}
			}

			if (selectedId == 3 || selectedId == 4) {
				while (it != parentsChildren.end()) {
					if ((*it)->getName() == "upperRow") {
						(*it)->setEnabled(false);
					}
					if ((*it)->getName() == "lowerRow") {
						(*it)->setEnabled(true);
					}
					++it;
				}
			}

			repaint();
		}
	}

} // cw::Filter