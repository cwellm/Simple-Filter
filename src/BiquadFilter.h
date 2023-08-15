#pragma once

#include <array>
#include "TFFilter.h"
#include "Chainable.h"
#include "BiquadCoeff.h"

namespace cw::Filter {

	class BiquadFilter : public TFFilter {

	public:
		/*
		* Set the filter coefficient type according to the types defined in BiquadCoeff.h. Each type takes two floats
		* as (user) parameters and calculates the according transfer function coefficients. 
		*/
		void setFilterCoeffType(std::unique_ptr<TFFilterCoeff<float, float>>&& filterCoeffType) {
			tfFilterCoeff = std::move(filterCoeffType);
		}

		/*
		* Set the filter coefficient type via the enum type defined in BiquadCoeff.h.
		*/
		void setFilterCoeffType(FilterType);

		/*
		* Sets the target values of the filter parameters, which determine the transfer function coefficients. Depending
		* on the filter type, the parameters may mean different things. The names in BiquadCoeff.cpp will reveal their
		* meaning for the specific coefficient type. 
		*/
		virtual void setTargetParams(const float&, const float&);
		void setSampleRate(const float&) override;

		void process(float*) override;
		void processBlock(float*, const int&) override;

		std::string name() override { return "BiquadFilter"; }
		void setSmoothingSpeed(float smoothingSpeed) { this->smoothingSpeed = smoothingSpeed; }

		virtual void reserveMemory(const int&);

	protected:
		// declare this here, so memory can be allocated beforehand with reserveMemory(), instead of calling
		// 'new' and 'delete' in the real-time thread
		std::unique_ptr<float[]> temporary{ nullptr };

	private: 
		std::array<float, 6> biquadCoefficients;
		std::unique_ptr<TFFilterCoeff<float, float>> tfFilterCoeff = nullptr;
		// I want to have a method which supplies to me the necessary a_0, a_1, a_2, b_0, b_1, b_2 parameters, based on
		// the specific algorithm. Also, some of the variables should be pre-bound, if they do not depend on any user
		// changeable parameters.

		void updateSmoothedCoeffs();

		// Hopefully, in future implementations, these params are not necessary anymore...
		float targetParam1{ 0 };
		float targetParam2{ 0 };
		float currentParam1{ 0 };
		float currentParam2{ 0 };
		float epsilon{ 1e-3 };
		float smoothingSpeed{ 1e-3 };

	};
} // cw::Filter