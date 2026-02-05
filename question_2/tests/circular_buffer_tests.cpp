#include <gtest/gtest.h>
#include "circular_buffer.h"

using namespace Syn;

TEST(CircularBufferTests, SmokeTest) {
	EXPECT_TRUE(true);
}


// Basic class tests

TEST(CircularBufferTests, CanInstantiate1) {
	CircularBuffer buffer(10);
}

TEST(CircularBufferTests, CanInstantiate2) {
	CircularBuffer buffer(0);
}


// Push tests

TEST(CircularBufferTests, AddOne_zeroSize){
	CircularBuffer buffer(0);

	EXPECT_FALSE(buffer.push(12));
}

TEST(CircularBufferTests, AddOne){
	CircularBuffer buffer(5);

	EXPECT_TRUE(buffer.push(12));
}

TEST(CircularBufferTests, AddTwo){
	CircularBuffer buffer(5);
	
	EXPECT_TRUE(buffer.push(12));
	EXPECT_TRUE(buffer.push(14));
}

TEST(CircularBufferTests, AddMax){
	CircularBuffer buffer(5);
	
	ASSERT_TRUE(buffer.push(12));
	ASSERT_TRUE(buffer.push(14));
	ASSERT_TRUE(buffer.push(16));
	ASSERT_TRUE(buffer.push(18));
	ASSERT_TRUE(buffer.push(20));
}

TEST(CircularBufferTests, AddTooMany){
	CircularBuffer buffer(5);
	
	ASSERT_TRUE(buffer.push(12));
	ASSERT_TRUE(buffer.push(14));
	ASSERT_TRUE(buffer.push(16));
	ASSERT_TRUE(buffer.push(18));
	ASSERT_TRUE(buffer.push(20));
	
	ASSERT_FALSE(buffer.push(21)); // oops
}


// Pop tests

TEST(CircularBufferTests, PopEmpty1){
	CircularBuffer buffer(0);
	uint8_t popped;

	EXPECT_FALSE(buffer.pop(popped));
}

TEST(CircularBufferTests, PopEmpty2){
	CircularBuffer buffer(5);
	uint8_t popped;

	EXPECT_FALSE(buffer.pop(popped));
}

TEST(CircularBufferTests, PopOne){
	CircularBuffer buffer(5);
	uint8_t popped = 0;
	uint8_t pushed = 12;

	ASSERT_TRUE(buffer.push(pushed));
	ASSERT_TRUE(buffer.pop(popped));
	ASSERT_EQ(pushed, popped);
}

TEST(CircularBufferTests, PopTwo){
	CircularBuffer buffer(5);
	uint8_t popped = 0;
	uint8_t pushed1 = 12;
	uint8_t pushed2 = 14;

	ASSERT_TRUE(buffer.push(pushed1));
	ASSERT_TRUE(buffer.push(pushed2));

	ASSERT_TRUE(buffer.pop(popped));
	ASSERT_EQ(pushed1, popped);
	ASSERT_TRUE(buffer.pop(popped));
	ASSERT_EQ(pushed2, popped);
}

TEST(CircularBufferTests, PopMax){
	CircularBuffer buffer(5);
	uint8_t popped = 0;
	uint8_t pushed1 = 12;
	uint8_t pushed2 = 14;
	uint8_t pushed3 = 16;
	uint8_t pushed4 = 18;
	uint8_t pushed5 = 20;

	ASSERT_TRUE(buffer.push(pushed1));
	ASSERT_TRUE(buffer.push(pushed2));
	ASSERT_TRUE(buffer.push(pushed3));
	ASSERT_TRUE(buffer.push(pushed4));
	ASSERT_TRUE(buffer.push(pushed5));

	ASSERT_TRUE(buffer.pop(popped));
	ASSERT_EQ(pushed1, popped);
	ASSERT_TRUE(buffer.pop(popped));
	ASSERT_EQ(pushed2, popped);
	ASSERT_TRUE(buffer.pop(popped));
	ASSERT_EQ(pushed3, popped);
	ASSERT_TRUE(buffer.pop(popped));
	ASSERT_EQ(pushed4, popped);
	ASSERT_TRUE(buffer.pop(popped));
	ASSERT_EQ(pushed5, popped);
}

TEST(CircularBufferTests, PopTooMany){
	CircularBuffer buffer(5);
	uint8_t popped = 0;
	uint8_t pushed1 = 12;
	uint8_t pushed2 = 14;
	uint8_t pushed3 = 16;
	uint8_t pushed4 = 18;
	uint8_t pushed5 = 20;

	ASSERT_TRUE(buffer.push(pushed1));
	ASSERT_TRUE(buffer.push(pushed2));
	ASSERT_TRUE(buffer.push(pushed3));
	ASSERT_TRUE(buffer.push(pushed4));
	ASSERT_TRUE(buffer.push(pushed5));

	ASSERT_TRUE(buffer.pop(popped));
	ASSERT_TRUE(buffer.pop(popped));
	ASSERT_TRUE(buffer.pop(popped));
	ASSERT_TRUE(buffer.pop(popped));
	ASSERT_TRUE(buffer.pop(popped));

	ASSERT_FALSE(buffer.pop(popped));
}


// Push-Pop tests

// Push and pop two elements, one at a time
TEST(CircularBufferTests, PushPop2){
	CircularBuffer buffer(5);
	uint8_t popped = 0;
	uint8_t pushed1 = 12;
	uint8_t pushed2 = 14;

	ASSERT_TRUE(buffer.push(pushed1));
	ASSERT_TRUE(buffer.pop(popped));
	ASSERT_EQ(pushed1, popped);

	ASSERT_TRUE(buffer.push(pushed2));
	ASSERT_TRUE(buffer.pop(popped));
	ASSERT_EQ(pushed2, popped);
}

// Push and pop the maximum number of elements, one at a time
TEST(CircularBufferTests, PushPopMax){
	CircularBuffer buffer(5);
	uint8_t popped = 0;
	uint8_t pushed1 = 12;
	uint8_t pushed2 = 14;
	uint8_t pushed3 = 16;
	uint8_t pushed4 = 18;
	uint8_t pushed5 = 20;

	ASSERT_TRUE(buffer.push(pushed1));
	ASSERT_TRUE(buffer.pop(popped));
	ASSERT_EQ(pushed1, popped);

	ASSERT_TRUE(buffer.push(pushed2));
	ASSERT_TRUE(buffer.pop(popped));
	ASSERT_EQ(pushed2, popped);

	ASSERT_TRUE(buffer.push(pushed3));
	ASSERT_TRUE(buffer.pop(popped));
	ASSERT_EQ(pushed3, popped);

	ASSERT_TRUE(buffer.push(pushed4));
	ASSERT_TRUE(buffer.pop(popped));
	ASSERT_EQ(pushed4, popped);

	ASSERT_TRUE(buffer.push(pushed5));
	ASSERT_TRUE(buffer.pop(popped));
	ASSERT_EQ(pushed5, popped);
}

// Push and pop beyond the buffer size (so indexes wrap), one at a time
TEST(CircularBufferTests, PushPopWrapBuffer_oneAtATime){
	CircularBuffer buffer(5);
	uint8_t popped = 0;
	uint8_t pushed1 = 12;
	uint8_t pushed2 = 14;
	uint8_t pushed3 = 16;
	uint8_t pushed4 = 18;
	uint8_t pushed5 = 20;
	uint8_t pushed6 = 22;
	uint8_t pushed7 = 24;

	ASSERT_TRUE(buffer.push(pushed1));
	ASSERT_TRUE(buffer.pop(popped));
	ASSERT_EQ(pushed1, popped);

	ASSERT_TRUE(buffer.push(pushed2));
	ASSERT_TRUE(buffer.pop(popped));
	ASSERT_EQ(pushed2, popped);

	ASSERT_TRUE(buffer.push(pushed3));
	ASSERT_TRUE(buffer.pop(popped));
	ASSERT_EQ(pushed3, popped);

	ASSERT_TRUE(buffer.push(pushed4));
	ASSERT_TRUE(buffer.pop(popped));
	ASSERT_EQ(pushed4, popped);

	ASSERT_TRUE(buffer.push(pushed5));
	ASSERT_TRUE(buffer.pop(popped));
	ASSERT_EQ(pushed5, popped);

	ASSERT_TRUE(buffer.push(pushed6));
	ASSERT_TRUE(buffer.pop(popped));
	ASSERT_EQ(pushed6, popped);

	ASSERT_TRUE(buffer.push(pushed7));
	ASSERT_TRUE(buffer.pop(popped));
	ASSERT_EQ(pushed7, popped);
}

// Push and pop beyond the buffer size (so indexes wrap), with multiple at a time
TEST(CircularBufferTests, PushPopWrapBuffer_severalAtATime){
	CircularBuffer buffer(5);
	uint8_t popped = 0;
	uint8_t pushed1 = 12;
	uint8_t pushed2 = 14;
	uint8_t pushed3 = 16;
	uint8_t pushed4 = 18;
	uint8_t pushed5 = 20;
	uint8_t pushed6 = 22;
	uint8_t pushed7 = 24;

	// Push 3 values
	ASSERT_TRUE(buffer.push(pushed1));
	ASSERT_TRUE(buffer.push(pushed2));
	ASSERT_TRUE(buffer.push(pushed3));

	// Pop 3, expect correct order
	ASSERT_TRUE(buffer.pop(popped));
	ASSERT_EQ(pushed1, popped);
	ASSERT_TRUE(buffer.pop(popped));
	ASSERT_EQ(pushed2, popped);
	ASSERT_TRUE(buffer.pop(popped));
	ASSERT_EQ(pushed3, popped);

	// Push 4 values, causing HEAD and TAIL to wrap
	ASSERT_TRUE(buffer.push(pushed4));
	ASSERT_TRUE(buffer.push(pushed5));
	ASSERT_TRUE(buffer.push(pushed6));
	ASSERT_TRUE(buffer.push(pushed7));

	// Pop 4, expect correct values
	ASSERT_TRUE(buffer.pop(popped));
	ASSERT_EQ(pushed4, popped);
	ASSERT_TRUE(buffer.pop(popped));
	ASSERT_EQ(pushed5, popped);
	ASSERT_TRUE(buffer.pop(popped));
	ASSERT_EQ(pushed6, popped);
	ASSERT_TRUE(buffer.pop(popped));
	ASSERT_EQ(pushed7, popped);
}