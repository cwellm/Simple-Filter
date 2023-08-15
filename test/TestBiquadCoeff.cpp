#include <gtest/gtest.h>
#include <array>

#include "BiquadCoeff.h"

namespace cw::Filter {

	class BiquadCoeffTest : public ::testing::Test {
	protected:
		BiquadLPCoeff lpCoeff{};
		BiquadHPCoeff hpCoeff{};
		BiquadBPCoeff bpCoeff{};
		BiquadBRCoeff brCoeff{};
	};

	TEST_F(BiquadCoeffTest, SampleRateZero) {
		lpCoeff.setTargetParams(1, 1);
		lpCoeff.setSampleRate(0);
		std::array<float, 6> arr{ 0,0,0,0,0,0 };

		lpCoeff.setCoeffs(arr);

		EXPECT_EQ(arr[0], 1);
		EXPECT_EQ(arr[1], 2);
		EXPECT_EQ(arr[2], 1);
		EXPECT_EQ(arr[3], 1);
		EXPECT_EQ(arr[4], 2);
		EXPECT_EQ(arr[5], 1);
	}

	TEST_F(BiquadCoeffTest, AllParamsOne) {
		// sr = 1, cutoff = 1, Q = 1
		lpCoeff.setTargetParams(1/(2*CW_PI), 1);
		lpCoeff.setSampleRate(1);
		std::array<float, 6> arr{ 0,0,0,0,0,0 };

		lpCoeff.setCoeffs(arr);

		EXPECT_EQ(arr[0], 1);
		EXPECT_EQ(arr[1], 2);
		EXPECT_EQ(arr[2], 1);
		EXPECT_EQ(arr[3], 7);
		EXPECT_EQ(arr[4], -6);
		EXPECT_EQ(arr[5], 3);
	}

	TEST_F(BiquadCoeffTest, ParamsSimpleValues) {
		// sr = 44100, cutoff = 22050, Q = 10
		lpCoeff.setTargetParams(22050/(2*CW_PI), 10);
		std::array<float, 6> arr{ 0,0,0,0,0,0 };

		lpCoeff.setCoeffs(arr);

		EXPECT_EQ(arr[0], 1);
		EXPECT_EQ(arr[1], 2);
		EXPECT_EQ(arr[2], 1);
		EXPECT_EQ(arr[3], 17.4f);
		EXPECT_EQ(arr[4], -30);
		EXPECT_EQ(arr[5], 16.6f);
	}

} // cw::Filter