#include <gtest/gtest.h>
#include "TFFilter.h"

using cw::Filter::TFFilter;

// test class to test implemented methods of abstract Filter class
class DummyConcreteTFFilter : public TFFilter {

	// dummy implementation
	void DummyConcreteTFFilter::process(float* sample) override {
		return;
	}

	// dummy implementation
	void DummyConcreteTFFilter::processBlock(float* sampleBlock, const int& blockSize) override {
		return;
	}
};

// class for setting up tests (make FilterTest available for everything)

class TFFilterTest : public ::testing::Test {
protected:
	DummyConcreteTFFilter tfFilter{};
};

TEST_F(TFFilterTest, bufSize) {
	ASSERT_EQ(tfFilter.getBufSize(), 200);

	tfFilter.setBufSize(30);
	ASSERT_EQ(tfFilter.getBufSize(), 30);
}

TEST_F(TFFilterTest, name) {
	ASSERT_EQ(tfFilter.name(), "TFFilter");
}