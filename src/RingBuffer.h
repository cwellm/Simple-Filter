#pragma once

#include <memory>

namespace cw::Filter {

	class RingBuffer {
	public:
		RingBuffer(int bufSize) : bufSize(bufSize),
			buffer{std::make_unique<float[]>(bufSize)}
		{
			clearBuffer();
		};

		float get(int);
		void set(const float&, int);
		float& operator[](int);

		int getBufSize() { return bufSize; }
		void setBufSize(const int&);

		void clearBuffer();

		int wrapPos(int);

	private: 
		int bufSize;
		std::unique_ptr<float[]> buffer;
	};
} // cw::Filter