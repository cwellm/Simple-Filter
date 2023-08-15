#include <gtest/gtest.h>
#include "BiquadFilter.h"
#include "BiquadCoeff.h"
#include "ParameterMappings.h"

using cw::Filter::BiquadFilter;

// class for setting up tests (make FilterTest available for everything)

class BiquadFilterTest : public ::testing::Test {
public:
	BiquadFilter biquadFilter{};

protected:
	static constexpr int blockSize{ 10 };
	float zeros[blockSize]{ 0,0,0,0,0,0,0,0,0,0 };
	float ones[blockSize]{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
	float pulse[blockSize]{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
};

TEST_F(BiquadFilterTest, lpFilterCoeffZeros) {
	biquadFilter.setFilterCoeffType(std::make_unique<cw::Filter::BiquadLPCoeff>());
	biquadFilter.setSampleRate(1);
	biquadFilter.setTargetParams(1, 1); // cutoffFreq, Qval
	
	biquadFilter.processBlock(zeros, blockSize);

	EXPECT_FLOAT_EQ(0.f, zeros[0]);
	EXPECT_FLOAT_EQ(0.f, zeros[1]);
	EXPECT_FLOAT_EQ(0.f, zeros[2]);
	EXPECT_FLOAT_EQ(0.f, zeros[3]);
	EXPECT_FLOAT_EQ(0.f, zeros[4]);
	EXPECT_FLOAT_EQ(0.f, zeros[5]);
	EXPECT_FLOAT_EQ(0.f, zeros[6]);
	EXPECT_FLOAT_EQ(0.f, zeros[7]);
	EXPECT_FLOAT_EQ(0.f, zeros[8]);
	EXPECT_FLOAT_EQ(0.f, zeros[9]);
}

TEST_F(BiquadFilterTest, lpFilterCoeffPulse) {
	biquadFilter.setFilterCoeffType(std::make_unique<cw::Filter::BiquadLPCoeff>());
	biquadFilter.setSampleRate(1);
	biquadFilter.setTargetParams(1.f/(2*CW_PI), 1); // cutoffFreq, Qval
	biquadFilter.setSmoothingSpeed(1.f);

	biquadFilter.processBlock(pulse, blockSize);

	EXPECT_FLOAT_EQ(1.f/7, pulse[0]);
	EXPECT_FLOAT_EQ(0.40816328, pulse[1]);
	EXPECT_FLOAT_EQ(0.43148687, pulse[2]);
	/*
	EXPECT_FLOAT_EQ(0.f, pulse[3]);
	EXPECT_FLOAT_EQ(0.f, pulse[4]);
	EXPECT_FLOAT_EQ(0.f, pulse[5]);
	EXPECT_FLOAT_EQ(0.f, pulse[6]);
	EXPECT_FLOAT_EQ(0.f, pulse[7]);
	EXPECT_FLOAT_EQ(0.f, pulse[8]);
	EXPECT_FLOAT_EQ(0.f, pulse[9]); */
}


TEST_F(BiquadFilterTest, lpFilterIsSetViaEnum) {
	biquadFilter.setFilterCoeffType(cw::Filter::FilterType::BiquadLP);
	biquadFilter.setSampleRate(1);
	biquadFilter.setTargetParams(1.f / (2*CW_PI), 1); // cutoffFreq, Qval
	biquadFilter.setSmoothingSpeed(1.f);

	biquadFilter.processBlock(pulse, blockSize);

	EXPECT_FLOAT_EQ(1.f / 7, pulse[0]);
	EXPECT_FLOAT_EQ(0.40816328, pulse[1]);
	EXPECT_FLOAT_EQ(0.43148687, pulse[2]);
}

TEST(TestBiquadFilter, name) {
	BiquadFilter filter{};

	ASSERT_EQ("BiquadFilter", filter.name());
}