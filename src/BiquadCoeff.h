#pragma once

#include <string>
#include <unordered_set>

#include "TFFilterCoeff.h"

#define CW_PI 3.141592654

/*
* Classes which supply the methods (sefCoeffs) to calculate the transfer function coefficients from the filter input
* parameters. Since this is a biquad, there are six parameters: Three for feedforward (b's), three for feedback (a's).
* Note that the feedback parameters are given as in the transfer function and have opposite sign compared to their 
* usage in the feedback buffer evaluation. The array is ordered as:
* b_0, b_1, b_2: x[0], x[1], x[2]
* a_0, a_1, a_2: x[3], x[4], x[5]
*/

namespace cw::Filter {

	struct BiquadLPCoeff : public TFFilterCoeff<float, float> {
		void setCoeffs(std::array<float, 6>&) override;
		void setTargetParams(const float& cutoffFreq, const float& QValue) override;
		std::string getType() override;
	private:
		float cutoffFreq{ 0 };
		float QValue{ 0 };
	};

	struct BiquadHPCoeff : public TFFilterCoeff<float, float> {
		void setCoeffs(std::array<float, 6>&) override;
		void setTargetParams(const float& cutoffFreq, const float& QValue) override;
		std::string getType() override;
	private:
		float cutoffFreq{ 0 };
		float QValue{ 0 };
	};

	struct BiquadBPCoeff : public TFFilterCoeff<float, float> {
		void setCoeffs(std::array<float, 6>&) override;
		void setTargetParams(const float& centerFreq, const float& bandwidth) override;
		std::string getType() override;
	private:
		float centerFreq{ 0 };
		float bandwidth{ 0 };
	};

	struct BiquadBRCoeff : public TFFilterCoeff<float, float> {
		void setCoeffs(std::array<float, 6>&) override;
		void setTargetParams(const float& centerFreq, const float& bandwidth) override;
		std::string getType() override;
	private:
		float centerFreq{ 0 };
		float bandwidth{ 0 };
	};

	enum struct FilterType {
		BiquadLP,
		BiquadHP,
		BiquadBP,
		BiquadBR
	};

} // cw::Filter