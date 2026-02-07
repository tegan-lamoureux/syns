#include <gtest/gtest.h>
#include "circular_buffer.h"


TEST(CircularBufferTests, SmokeTest) {
	EXPECT_TRUE(true);
}


// Basic class tests

TEST(CircularBufferTests, CanInstantiate1) {
	Syn::CircularBuffer buffer(10);
}

TEST(CircularBufferTests, CanInstantiate2) {
	Syn::CircularBuffer buffer(0);
}


// Push tests

TEST(CircularBufferTests, AddOne_zeroSize){
	Syn::CircularBuffer buffer(0);

	EXPECT_FALSE(buffer.push(12));
}

TEST(CircularBufferTests, AddOne){
	Syn::CircularBuffer buffer(5);

	EXPECT_TRUE(buffer.push(12));
}

TEST(CircularBufferTests, AddTwo){
	Syn::CircularBuffer buffer(5);
	
	EXPECT_TRUE(buffer.push(12));
	EXPECT_TRUE(buffer.push(14));
}

TEST(CircularBufferTests, AddMax){
	Syn::CircularBuffer buffer(5);
	
	ASSERT_TRUE(buffer.push(12));
	ASSERT_TRUE(buffer.push(14));
	ASSERT_TRUE(buffer.push(16));
	ASSERT_TRUE(buffer.push(18));
	ASSERT_TRUE(buffer.push(20));
}

TEST(CircularBufferTests, AddTooMany){
	Syn::CircularBuffer buffer(5);
	
	ASSERT_TRUE(buffer.push(12));
	ASSERT_TRUE(buffer.push(14));
	ASSERT_TRUE(buffer.push(16));
	ASSERT_TRUE(buffer.push(18));
	ASSERT_TRUE(buffer.push(20));
	
	ASSERT_FALSE(buffer.push(21)); // oops
}


// Pop tests

TEST(CircularBufferTests, PopEmpty1){
	Syn::CircularBuffer buffer(0);
	uint8_t popped;

	EXPECT_FALSE(buffer.pop(popped));
}

TEST(CircularBufferTests, PopEmpty2){
	Syn::CircularBuffer buffer(5);
	uint8_t popped;

	EXPECT_FALSE(buffer.pop(popped));
}

TEST(CircularBufferTests, PopOne){
	Syn::CircularBuffer buffer(5);
	uint8_t popped = 0;
	uint8_t pushed = 12;

	ASSERT_TRUE(buffer.push(pushed));
	ASSERT_TRUE(buffer.pop(popped));
	ASSERT_EQ(pushed, popped);
}

TEST(CircularBufferTests, PopTwo){
	Syn::CircularBuffer buffer(5);
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
	Syn::CircularBuffer buffer(5);
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
	Syn::CircularBuffer buffer(5);
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
	Syn::CircularBuffer buffer(5);
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
	Syn::CircularBuffer buffer(5);
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
	Syn::CircularBuffer buffer(5);
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
	Syn::CircularBuffer buffer(5);
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

// Push and pop beyond the buffer size (so indexes wrap), with multiple 
// at a time, async version (mismatched push pop)
TEST(CircularBufferTests, PushPopWrapBuffer_severalAtATime_async){
	Syn::CircularBuffer buffer(5);
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

	// Pop 2, expect correct order
	ASSERT_TRUE(buffer.pop(popped));
	ASSERT_EQ(pushed1, popped);
	ASSERT_TRUE(buffer.pop(popped));
	ASSERT_EQ(pushed2, popped);

	// Push 4 values, causing HEAD and TAIL to wrap
	ASSERT_TRUE(buffer.push(pushed4));
	ASSERT_TRUE(buffer.push(pushed5));
	ASSERT_TRUE(buffer.push(pushed6));
	ASSERT_TRUE(buffer.push(pushed7));

	// Pop 5, expect correct values
	ASSERT_TRUE(buffer.pop(popped));
	ASSERT_EQ(pushed3, popped);
	ASSERT_TRUE(buffer.pop(popped));
	ASSERT_EQ(pushed4, popped);
	ASSERT_TRUE(buffer.pop(popped));
	ASSERT_EQ(pushed5, popped);
	ASSERT_TRUE(buffer.pop(popped));
	ASSERT_EQ(pushed6, popped);
	ASSERT_TRUE(buffer.pop(popped));
	ASSERT_EQ(pushed7, popped);
}

// Push and pop beyond the buffer size (so indexes wrap), with multiple 
// at a time, async version, with extra pops beyond buffer size
TEST(CircularBufferTests, PushPopWrapBuffer_severalAtATime_async_extraPops){
	Syn::CircularBuffer buffer(5);
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

	// Pop 1, expect correct order
	ASSERT_TRUE(buffer.pop(popped));
	ASSERT_EQ(pushed1, popped);

	// Push 3 values, causing HEAD and TAIL to wrap
	ASSERT_TRUE(buffer.push(pushed4));
	ASSERT_TRUE(buffer.push(pushed5));
	ASSERT_TRUE(buffer.push(pushed6));

	// Pop 5, expect correct values
	ASSERT_TRUE(buffer.pop(popped));
	ASSERT_EQ(pushed2, popped);
	ASSERT_TRUE(buffer.pop(popped));
	ASSERT_EQ(pushed3, popped);
	ASSERT_TRUE(buffer.pop(popped));
	ASSERT_EQ(pushed4, popped);
	ASSERT_TRUE(buffer.pop(popped));
	ASSERT_EQ(pushed5, popped);
	ASSERT_TRUE(buffer.pop(popped));
	ASSERT_EQ(pushed6, popped);

	// Push 1 value
	ASSERT_TRUE(buffer.push(pushed1));
		
	// Pop 2, expect correct value and then failure
	ASSERT_TRUE(buffer.pop(popped));
	ASSERT_EQ(pushed1, popped);

	ASSERT_FALSE(buffer.pop(popped));
	ASSERT_FALSE(buffer.pop(popped));
}

// Push and pop beyond the buffer size (so indexes wrap), with multiple 
// at a time, async version, with extra pushes beyond buffer size
TEST(CircularBufferTests, PushPopWrapBuffer_severalAtATime_async_extraPush){
	Syn::CircularBuffer buffer(5);
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

	// Pop 1, expect correct order
	ASSERT_TRUE(buffer.pop(popped));
	ASSERT_EQ(pushed1, popped);

	// Push 3 values, causing HEAD and TAIL to wrap
	ASSERT_TRUE(buffer.push(pushed4));
	ASSERT_TRUE(buffer.push(pushed5));
	ASSERT_TRUE(buffer.push(pushed6));

	// Pop 6, expect correct values
	ASSERT_TRUE(buffer.pop(popped));
	ASSERT_EQ(pushed2, popped);
	ASSERT_TRUE(buffer.pop(popped));
	ASSERT_EQ(pushed3, popped);
	ASSERT_TRUE(buffer.pop(popped));
	ASSERT_EQ(pushed4, popped);
	ASSERT_TRUE(buffer.pop(popped));
	ASSERT_EQ(pushed5, popped);
	ASSERT_TRUE(buffer.pop(popped));
	ASSERT_EQ(pushed6, popped);

	// Push 1 value
	ASSERT_TRUE(buffer.push(pushed1));
		
	// Pop 2, expect correct value and then failure
	ASSERT_TRUE(buffer.pop(popped));
	ASSERT_EQ(pushed1, popped);

	ASSERT_FALSE(buffer.pop(popped));
	ASSERT_FALSE(buffer.pop(popped));

	// Push 7 values, expect failure after 5
	ASSERT_TRUE(buffer.push(pushed1));
	ASSERT_TRUE(buffer.push(pushed1));
	ASSERT_TRUE(buffer.push(pushed1));
	ASSERT_TRUE(buffer.push(pushed1));
	ASSERT_TRUE(buffer.push(pushed1));
	ASSERT_FALSE(buffer.push(pushed1));
	ASSERT_FALSE(buffer.push(pushed1));
}