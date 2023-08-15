#pragma once

#include "RingBuffer.h"
#include "Chainable.h"

namespace cw::Filter {

	class Filter : public Chainable {

	public:
		Filter() : ffRingBuffer(this->bufSize) {}

		virtual void process(float* sample) {}; // still necessary???

		/*
		* Clears all buffers and resets all positions.
		*/
		virtual void resetFilter();

		virtual void setBufSize(const int&);
		int getBufSize() { return bufSize; }
		virtual void setSampleRate(const float& sampleRate) { this->sampleRate = sampleRate; }
		float getSampleRate() { return sampleRate; }

		std::string name() override { return "Filter"; }

	private:
		int bufSize{ 200 };
		float sampleRate{ 44100 };

	protected:
		RingBuffer ffRingBuffer;
		int ffCurrentPos{ 0 };
	};

} // cw::Filter