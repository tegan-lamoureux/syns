#include <gtest/gtest.h>

#include <vector>
#include <algorithm>

#include "car.h"
#include "linked_list.h"

TEST(LinkedListTests, SmokeTest) {
	Syn::LinkedList list1(10);
	Syn::LinkedList list2;
}


// Add node tests, check size and add return value
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




// Iterator tests, check actual list validity
TEST(LinkedListTests, CanTraverseWithRangedFor) {
	std::vector<Syn::Car> cars {
		Syn::Car("Toyota", "Camry", 2012),
		Syn::Car("Mazda", "RX7", 1995),
		Syn::Car("Honda", "Civic Type R", 2014),
		Syn::Car("Toyota", "Supra", 1997),
		Syn::Car("Honda", "Prelude", 1997)	
	};

	Syn::LinkedList list(5);

	for (auto car : cars) {
		ASSERT_TRUE(list.appendFront(car));
	}
	ASSERT_EQ(5, list.size());

	std::reverse(cars.begin(), cars.end()); // Reverse original input list to match the linked list

	// Iterate linked list with auto ranged based for loop, check validity
	auto current = cars.begin();
	for (const auto& car : list) {
		EXPECT_EQ(*current, car);
		current++;
	}
}

TEST(LinkedListTests, CanTraverseWithPostIncrement) {
	std::vector<Syn::Car> cars {
		Syn::Car("Toyota", "Camry", 2012),
		Syn::Car("Mazda", "RX7", 1995),
		Syn::Car("Honda", "Civic Type R", 2014),
		Syn::Car("Toyota", "Supra", 1997),
		Syn::Car("Honda", "Prelude", 1997)	
	};

	Syn::LinkedList list(5);

	for (auto car : cars) {
		ASSERT_TRUE(list.appendFront(car));
	}
	ASSERT_EQ(5, list.size());

	std::reverse(cars.begin(), cars.end()); // Reverse original input list to match the linked list

	// Iterate list with ++, check validity
	auto current = list.begin();
	for (auto car : cars) {
		EXPECT_TRUE(*current == car);
		current++;
	}
}

TEST(LinkedListTests, CanTraverseWithPreIncrement) {
	std::vector<Syn::Car> cars {
		Syn::Car("Toyota", "Camry", 2012),
		Syn::Car("Mazda", "RX7", 1995),
		Syn::Car("Honda", "Civic Type R", 2014),
		Syn::Car("Toyota", "Supra", 1997),
		Syn::Car("Honda", "Prelude", 1997)	
	};

	Syn::LinkedList list(5);

	for (auto car : cars) {
		ASSERT_TRUE(list.appendFront(car));
	}
	ASSERT_EQ(5, list.size());

	std::reverse(cars.begin(), cars.end()); // Reverse original input list to match the linked list

	// Iterate list with ++, check validity
	auto current = list.begin();
	for (auto car : cars) {
		EXPECT_TRUE(*current == car);
		++current;
	}
}

TEST(LinkedListTests, TraverseEmptyIsRuntimeSafe) {
	Syn::LinkedList list;

	for (auto car : list) {
		// nop
	}
	
	auto start = list.begin();
	ASSERT_TRUE(start == list.end());

	start++;
	ASSERT_TRUE(start == list.end());

	// *start == Undefined Behavior (Expected)
}

TEST(LinkedListTests, CanCheckIteratorEquality) {
	std::vector<Syn::Car> cars {
		Syn::Car("Toyota", "Camry", 2012),
		Syn::Car("Mazda", "RX7", 1995),
		Syn::Car("Honda", "Civic Type R", 2014),
		Syn::Car("Toyota", "Supra", 1997),
		Syn::Car("Honda", "Prelude", 1997)	
	};

	Syn::LinkedList list(5);

	for (auto car : cars) {
		ASSERT_TRUE(list.appendFront(car));
	}
	ASSERT_EQ(5, list.size());

	auto secondItem = ++ list.begin();
	auto secondItemAgain = list.begin();
	secondItemAgain ++;

	ASSERT_TRUE(secondItem == secondItemAgain);
}

TEST(LinkedListTests, CanCheckIteratorInequality) {
	std::vector<Syn::Car> cars {
		Syn::Car("Toyota", "Camry", 2012),
		Syn::Car("Mazda", "RX7", 1995),
		Syn::Car("Honda", "Civic Type R", 2014),
		Syn::Car("Toyota", "Supra", 1997),
		Syn::Car("Honda", "Prelude", 1997)	
	};

	Syn::LinkedList list(5);

	for (auto car : cars) {
		ASSERT_TRUE(list.appendFront(car));
	}
	ASSERT_EQ(5, list.size());

	auto firstItem = list.begin();
	auto secondItem = ++ list.begin();

	ASSERT_TRUE(firstItem != secondItem);
}

