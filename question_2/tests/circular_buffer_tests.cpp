#include <gtest/gtest.h>
#include "circular_buffer.h"

using namespace Syn;

TEST(CircularBufferTests, SmokeTest) {
	EXPECT_TRUE(true);
}

TEST(CircularBufferTests, CanInstantiate) {
	CircularBuffer buffer(10);
}

