#include "TFFilter.h"

namespace cw::Filter {

	void TFFilter::resetFilter() {
		Filter::resetFilter();
		fbRingBuffer.clearBuffer();
		fbCurrentPos = 0;
	}

	void TFFilter::setBufSize(const int& newBufSize) {
		Filter::setBufSize(newBufSize);
		fbRingBuffer.setBufSize(newBufSize);
		fbCurrentPos = 0;
	}

} // cw::Filter