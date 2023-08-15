#pragma once

#include "BiquadFilter.h"
#include <cmath>

namespace cw::Filter {

	void BiquadFilter::setTargetParams(const float& param1, const float &param2) {
		targetParam1 = param1;
		targetParam2 = param2;
		// set some internal state function/functional which "communicates" with processBlock, or tells the smoothing
		// alg. to update...?
		// then set filtercoeff: setTargetParams(currentParam1, currentParam2), setCoeffs(biquadCoefficients)

		// legacy - does not allow for sample-based param smoothing at this point
		// tfFilterCoeff->setTargetParams(param1, param2);
		// tfFilterCoeff->setCoeffs(biquadCoefficients);
	}

	void BiquadFilter::setSampleRate(const float& sampleRate) {
		Filter::setSampleRate(sampleRate);
		tfFilterCoeff->setSampleRate(sampleRate);
	}

	void BiquadFilter::process(float* sample) {

	}
	void BiquadFilter::processBlock(float* inMemBlock, const int& inBlockSize) {
		
		// set those values for the Chainable - to be able to hand it over to the next DSP process in the chain
		blockSize = inBlockSize;
		memBlock = inMemBlock;
		
		ffCurrentPos = ffRingBuffer.wrapPos(ffCurrentPos);
		fbCurrentPos = fbRingBuffer.wrapPos(fbCurrentPos);

		for (int i = 0; i < blockSize; ++i) {
			// parameter smoothing --> TODO: put this into an extra thread, to occur in parallel with the actual 
			// processing....also think about a better way instead of calling this method each time in this for-loop
			// (parallelization might help?)...friend class or pointers do not seem to be a solution (bad practice,
			// breaking encapsulation etc.) - also, think about moving this into the TFFilter part, if it can be made
			// more generic

			// btw what about creating SmoothedParam class and doing its own internal processing, in parallel, or so?
			updateSmoothedCoeffs();

			// y[n] = (-a_1 y[n-1] - a_2 y[n-2] + b_0 x[n] + b_1 x[n-1] + b_2 x[n-2]) / (-a_0)
			ffRingBuffer[ffCurrentPos] = inMemBlock[i];
			fbRingBuffer[fbCurrentPos] = (biquadCoefficients[0] * ffRingBuffer[ffCurrentPos]
				+ biquadCoefficients[1] * ffRingBuffer[ffRingBuffer.wrapPos(ffCurrentPos - 1)]
				+ biquadCoefficients[2] * ffRingBuffer[ffRingBuffer.wrapPos(ffCurrentPos - 2)]
				- biquadCoefficients[4] * fbRingBuffer[fbRingBuffer.wrapPos(fbCurrentPos - 1)]
				- biquadCoefficients[5] * fbRingBuffer[fbRingBuffer.wrapPos(fbCurrentPos - 2)])
				/ biquadCoefficients[3];

			temporary[i] = fbRingBuffer[fbCurrentPos];
			ffCurrentPos = ffRingBuffer.wrapPos(ffCurrentPos + 1);
			fbCurrentPos = fbRingBuffer.wrapPos(fbCurrentPos + 1);
		}
		for (int i = 0; i < blockSize; ++i) {
			inMemBlock[i] = temporary[i];
		}
	}

	
	void BiquadFilter::setFilterCoeffType(FilterType filterType) {

		switch (filterType) {
			case FilterType::BiquadLP: {
				setFilterCoeffType(std::make_unique<BiquadLPCoeff>());
				break;
			}

			case FilterType::BiquadHP: {
				setFilterCoeffType(std::make_unique<BiquadHPCoeff>());
				break;
			}

			case FilterType::BiquadBP: {
				setFilterCoeffType(std::make_unique<BiquadBPCoeff>());
				break;
			}

			case FilterType::BiquadBR: {
				setFilterCoeffType(std::make_unique<BiquadBRCoeff>());
				break;
			}
		} 
	}

	void BiquadFilter::updateSmoothedCoeffs() {
		// not only put this somewhere else, but also use a more intelligent smoothing alg., if exists...
		// and add some "flag" so this only gets called if any changes are still happening

		if (std::abs(currentParam1 - targetParam1) >= epsilon) {
			currentParam1 = currentParam1 + smoothingSpeed * (targetParam1 - currentParam1);
		}

		if (std::abs(currentParam2 - targetParam2) >= epsilon) {
			currentParam2 = currentParam2 + smoothingSpeed * (targetParam2 - currentParam2);
		}

		tfFilterCoeff->setTargetParams(currentParam1, currentParam2);
		tfFilterCoeff->setCoeffs(biquadCoefficients);
	}

	void BiquadFilter::reserveMemory(const int& size) {
		temporary = std::make_unique<float[]>(size);
		for (int i = 0; i < size; ++i) {
			temporary[i] = 0;
		}
	}

} // cw::Filter