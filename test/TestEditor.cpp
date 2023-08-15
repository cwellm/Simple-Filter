#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "../src/Editor.h"


class MockProcessor : public Processor {
	MOCK_METHOD(bool, isMidiEffect, ());
	MOCK_METHOD(void, prepareToPlay, (double, int), (override));
};


TEST(TestEditor, Example) {
	//MockProcessor mockProcessor;
	//Editor editor{mockProcessor};
	ASSERT_EQ(1, 1);
}



TEST(TestEditor, Example2) {
	ASSERT_EQ(1, 1);
}