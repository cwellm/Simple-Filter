#pragma once

#include <string>

namespace cw::Filter {

	struct Chainable {
		// what do I need to chain sth? I need to have clear input and output. In comes the processing float memory
		// block (e.g. via processBlock), which changes the internal state of the stage (e.g. filter), and changes
		// the float value in-place. What I need as output is, then, the pointer to the memory block and the blocksize.
		// So, this interface must supply vals for the blocksize and a pointer to the memory. Since all stages in the
		// chain operate on the same memory block, one could make the interface static. 

		static int blockSize; // size of the current memory block
		static float* memBlock; // current memory block
		bool isChain{ false };
		virtual void processBlock(float* sampleBlock, const int& blockSize) = 0;
		virtual std::string name() = 0;
	};
} // cw::Filter