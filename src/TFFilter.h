#pragma once

#include "Filter.h"

namespace cw::Filter {

	class TFFilter : public Filter {
	public:
		TFFilter(): fbRingBuffer(this->getBufSize()) {}
		void resetFilter() override;
		void setBufSize(const int&) override;

		std::string name() override { return "TFFilter"; }

	protected:
		int fbCurrentPos{ 0 };
		RingBuffer fbRingBuffer;

	};

} // cw::Filter