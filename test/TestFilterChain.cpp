#include <gtest/gtest.h>

#include <stdexcept>

#include "FilterChain.h"
#include "BiquadFilter.h"

namespace cw::Filter {

	
	class FilterChainTest : public ::testing::Test {

	public:
		FilterChainTest() {}

	protected:
		FilterChain<BiquadFilter, BiquadFilter, BiquadFilter> filterChain{ std::map<int, std::vector<int>>
			{
				{1, { 1 } }
			}
		};
	};

	TEST_F(FilterChainTest, name) {
		ASSERT_EQ("FilterChain", filterChain.name());
	}

	TEST_F(FilterChainTest, noOfKnots) {
		ASSERT_EQ(3, filterChain.getNoOfKnots());
	}

	TEST_F(FilterChainTest, kindOfKnots) {
		std::string expected = "Chainable: BiquadFilter\n"
			"Chainable: BiquadFilter\n"
			"Chainable: BiquadFilter\n";

		ASSERT_EQ(expected, filterChain.printKnotsInOrder().str());
	}

	TEST_F(FilterChainTest, bracketOperatorRead) {
		auto chainable = filterChain[1];
		ASSERT_EQ(chainable->isChain, false);
		ASSERT_EQ(chainable->name(), "BiquadFilter");
	}

	TEST_F(FilterChainTest, bracketOperatorReadException) {
		
		ASSERT_THROW(filterChain[3], std::invalid_argument);
	}

	TEST(TestFilterChain, defaultConstructor) {
		FilterChain<BiquadFilter, BiquadFilter> filterChain{};
		ASSERT_EQ(2, filterChain.getNoOfKnots());
	}

} // cw::Filter