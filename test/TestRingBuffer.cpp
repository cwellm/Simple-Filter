#include <gtest/gtest.h>
#include "RingBuffer.h"

using cw::Filter::RingBuffer;

class RingBufferTest : public ::testing::Test {
protected:
	RingBuffer ringBuffer{ 20 };
};

TEST_F(RingBufferTest, get) {
	ASSERT_EQ(0, ringBuffer.get(-3));
	ASSERT_EQ(0, ringBuffer.get(0));
	ASSERT_EQ(0, ringBuffer.get(11));
	ASSERT_EQ(0, ringBuffer.get(19));
	ASSERT_EQ(0, ringBuffer.get(98));
}

TEST_F(RingBufferTest, set) {
	ringBuffer.set(1.2f, 1);
	ringBuffer.set(1.3f, 13);
	ringBuffer.set(1.4f, 19);
	ringBuffer.set(1.5f, 20);
	ringBuffer.set(1.6f, 46); // eq. to index 6
	ringBuffer.set(1.7f, -22); // eq. to index 18

	ASSERT_EQ(ringBuffer.get(1), 1.2f);
	ASSERT_EQ(ringBuffer.get(13), 1.3f);
	ASSERT_EQ(ringBuffer.get(19), 1.4f);
	ASSERT_EQ(ringBuffer.get(0), 1.5f);
	ASSERT_EQ(ringBuffer.get(6), 1.6f);
	ASSERT_EQ(ringBuffer.get(18), 1.7f);
}

TEST_F(RingBufferTest, bracketOperator) {
	ASSERT_EQ(ringBuffer[0], 0);
	ASSERT_EQ(ringBuffer[-3], 0);
	ASSERT_EQ(ringBuffer[13], 0);

	ringBuffer[-5] = 3.f; // eq. to index 15
	ringBuffer[5] = 4.f;
	ringBuffer[48] = 5.f; // eq. to index 8

	ASSERT_EQ(ringBuffer[15], 3.f);
	ASSERT_EQ(ringBuffer[5], 4.f);
	ASSERT_EQ(ringBuffer[8], 5.f);
}

TEST_F(RingBufferTest, clearBuffer) {
	ringBuffer[0] = 1.f;
	ringBuffer[16] = 2.f;

	ringBuffer.clearBuffer();

	ASSERT_EQ(ringBuffer[0], 0);
	ASSERT_EQ(ringBuffer[16], 0);
	ASSERT_EQ(ringBuffer[10], 0);
}

TEST_F(RingBufferTest, setBufSize) {
	ringBuffer[0] = 1.f;
	ringBuffer[10] = 2.f;

	ringBuffer.setBufSize(10);

	// clear buffer was called
	ASSERT_EQ(ringBuffer[0], 0);
	ASSERT_EQ(ringBuffer[10], 0);

	// new bufsize makes indices wrap earlier

	ringBuffer[12] = 1.2f; // ~ index 2
	ringBuffer[-3] = 1.4f; // ~ index 7

	ASSERT_EQ(ringBuffer[2], 1.2f);
	ASSERT_EQ(ringBuffer[7], 1.4f);
}

TEST_F(RingBufferTest, wrapPos) {
	ASSERT_EQ(ringBuffer.wrapPos(23), 3);
	ASSERT_EQ(ringBuffer.wrapPos(9), 9);
	ASSERT_EQ(ringBuffer.wrapPos(-14), 6);

	ringBuffer.setBufSize(10);
	ASSERT_EQ(ringBuffer.wrapPos(15), 5);
	ASSERT_EQ(ringBuffer.wrapPos(7), 7);
	ASSERT_EQ(ringBuffer.wrapPos(-4), 6);
}
