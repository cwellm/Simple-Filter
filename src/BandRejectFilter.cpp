#include "BandRejectFilter.h"

namespace cw::Filter {

	void BandRejectFilter::setTargetParams(const float& centerFrequency, const float& bandwidth) {
		this->bandwidth = bandwidth;
		this->centerFrequency = centerFrequency;

		float cutoffFreqLP = centerFrequency - 1. / 2 * bandwidth;
		float cutoffFreqHP = centerFrequency + 1. / 2 * bandwidth;
		chainables->at(0)->setTargetParams(cutoffFreqLP, 2.);
		chainables->at(1)->setTargetParams(cutoffFreqHP, 2.);
	}

} // cw::Filter