#include <gtest/gtest.h>
#include "Filter.h"

using cw::Filter::Filter;

// test class to test implemented methods of abstract Filter class
class DummyConcreteFilter : public Filter {

	// dummy implementation
	void DummyConcreteFilter::process(float* sample) override {
		return;
	}

	// dummy implementation
	void DummyConcreteFilter::processBlock(float* sampleBlock, const int& blockSize) override {
		return;
	}
};

// class for setting up tests (make FilterTest available for everything)

class FilterTest : public ::testing::Test {
protected:
	DummyConcreteFilter filter{};
};

TEST_F(FilterTest, bufSize) {
	ASSERT_EQ(filter.getBufSize(), 200);

	filter.setBufSize(30);
	ASSERT_EQ(filter.getBufSize(), 30);
}