#pragma once

#include "BiquadFilterChain.h"
#include "BiquadFilter.h"

/*
* Band reject filter, consisting of two biquad filters in row (BiquadFilterChain), setting the coefficients in a manner as
* to get a BR filter.
* chainables[0]: LP filter
* chainables[1]: HP filter
*/
namespace cw::Filter {

	class BandRejectFilter : public BiquadFilterChain<BiquadFilter, BiquadFilter> {
	public:
		BandRejectFilter() {
			chainables->at(0)->setFilterCoeffType(std::make_unique<BiquadLPCoeff>()); // LP
			chainables->at(1)->setFilterCoeffType(std::make_unique<BiquadHPCoeff>()); // HP
			isParallel = true;
		}

		void setTargetParams(const float&, const float&) override;

		std::string name() override { return "BandRejectFilter"; }

	private:
		float bandwidth{ 0 };
		float centerFrequency{ 0 };
	};

} // cw::Filter