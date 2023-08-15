#include "Filter.h"

namespace cw::Filter {
	void Filter::resetFilter() {
		ffRingBuffer.clearBuffer();
		ffCurrentPos = 0;
	}

	void Filter::setBufSize(const int& newBufSize) {
		this->bufSize = newBufSize;
		ffRingBuffer.setBufSize(newBufSize);
		ffCurrentPos = 0;
	}
} // cw::Filter
