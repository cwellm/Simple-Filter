#pragma once

#include "BiquadFilterChain.h"
#include "BiquadFilter.h"

/*
* Bandpass filter, consisting of two biquad filters in row (BiquadFilterChain), setting the coefficients in a manner as
* to get a BP filter. 
* chainables[0]: LP filter
* chainables[1]: HP filter
*/
namespace cw::Filter {

	class BandpassFilter : public BiquadFilterChain<BiquadFilter, BiquadFilter> {
	public:
		BandpassFilter() {
			chainables->at(0)->setFilterCoeffType(std::make_unique<BiquadLPCoeff>()); // LP
			chainables->at(1)->setFilterCoeffType(std::make_unique<BiquadHPCoeff>()); // HP
		}

		void setTargetParams(const float&, const float&) override;

		std::string name() override { return "BandpassFilter"; }

	private: 
		float bandwidth{ 0 };
		float centerFrequency{ 0 };
	};

} // cw::Filter