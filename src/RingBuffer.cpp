#include "RingBuffer.h"

namespace cw::Filter {

	float RingBuffer::get(int index) {
		while (index < 0) {
			index += bufSize;
		}
		index %= bufSize;

		return buffer[index];
	}

	void RingBuffer::set(const float& value, int index) {
		while (index < 0) {
			index += bufSize;
		}
		index %= bufSize;

		buffer[index] = value;
	}

	float& RingBuffer::operator[](int index) {
		while (index < 0) {
			index += bufSize;
		}
		index %= bufSize;

		return buffer[index];
	}

	void RingBuffer::clearBuffer() {
		for (int i = 0; i < bufSize; ++i) {
			buffer[i] = 0;
		}
	}

	void RingBuffer::setBufSize(const int& newBufSize) {
		this->bufSize = newBufSize;
		buffer = std::make_unique<float[]>(newBufSize);
		clearBuffer();
	}

	/* 
	* Convenience method to wrap an arbitrary integer to within the buffer range, according to the current buffersize
	* of the ring buffer. 
	*/
	int RingBuffer::wrapPos(int pos) {
		while (pos < 0) {
			pos += bufSize;
		}
		pos %= bufSize;

		return pos;
	}

} // cw::Filter