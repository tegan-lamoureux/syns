#include <gtest/gtest.h>

#include "car.h"
#include "linked_list.h"


TEST(LinkedListTests, SmokeTest) {
	Syn::LinkedList list1(10);
	Syn::LinkedList list2;
}

TEST(LinkedListTests, AddNode) {
	Syn::LinkedList list(5);
	const Syn::Car car("Toyota", "GR Yaris", 2025);

	EXPECT_TRUE(list.appendFront(car));
	EXPECT_EQ(1, list.size());
}

TEST(LinkedListTests, AddNode2) {
	Syn::LinkedList list;
	const Syn::Car car("Toyota", "GR Yaris", 2025);

	EXPECT_TRUE(list.appendFront(car));
	EXPECT_TRUE(list.appendFront(car));
	EXPECT_EQ(2, list.size());
}

TEST(LinkedListTests, AddMaxNodes) {
	Syn::LinkedList list(3);
	const Syn::Car car("Toyota", "GR Yaris", 2025);
	
	ASSERT_TRUE(list.appendFront(car));
	ASSERT_TRUE(list.appendFront(car));
	ASSERT_TRUE(list.appendFront(car));
	EXPECT_EQ(3, list.size());
}

TEST(LinkedListTests, AddMoreThanMaxNodes) {
	Syn::LinkedList list(3);
	const Syn::Car car("Toyota", "GR Yaris", 2025);
	
	ASSERT_TRUE(list.appendFront(car));
	ASSERT_TRUE(list.appendFront(car));
	ASSERT_TRUE(list.appendFront(car));
	ASSERT_FALSE(list.appendFront(car));
	EXPECT_EQ(3, list.size());
}

