#include <gtest/gtest.h>
#include <iostream>

#include "car.h"
#include "linked_list.h"
#include "merge_sort.h"

// The one, the only.
// Build two lists, different order. Sort both, check proper order.
TEST(SortTests, Sort) {
	std::vector<Syn::Car> cars1 {
		Syn::Car("Toyota", "Camry", 2012),
		Syn::Car("Mazda", "RX7", 1995),
		Syn::Car("Honda", "Civic Type R", 2014),
		Syn::Car("Toyota", "Supra", 1997),
		Syn::Car("Honda", "Prelude", 1997)	
	};

	std::vector<Syn::Car> cars2 {
		Syn::Car("Toyota", "Supra", 1997),
		Syn::Car("Honda", "Civic Type R", 2014),
		Syn::Car("Honda", "Prelude", 1997),
		Syn::Car("Mazda", "RX7", 1995),
		Syn::Car("Toyota", "Camry", 2012)
	};

	// Build lists
	Syn::LinkedList list1(5);
	Syn::LinkedList list2(5);

	for (auto car : cars1) {
		ASSERT_TRUE(list1.appendFront(car));
	}
	ASSERT_EQ(5, list1.size());

	for (auto car : cars2) {
		ASSERT_TRUE(list2.appendFront(car));
	}
	ASSERT_EQ(5, list2.size());

	// Sort first
	Syn::LinkedList sortedList(5);
	Syn::MergeSort::sortDescending(list1, sortedList);

	// // Check list is in ascending order. 
	std::cout << std:: endl << "Check first sort: " << std::endl;

	uint32_t previousYear = 0;
	uint32_t currentYear  = 0;

	for (auto currentCar : sortedList) {
		if (previousYear) { // skip first
			currentYear = currentCar.getYear();

			std:: cout << "Checking that `" << previousYear << "` >= `" 
					   << currentYear << "`." << std::endl;
			ASSERT_GE(previousYear, currentYear);
		}
		previousYear = currentCar.getYear();
	}

	// Sort second
	Syn::LinkedList sortedList2(5);
	Syn::MergeSort::sortDescending(list2, sortedList2);

	// // Check list is in ascending order. 
	std::cout << std:: endl << "Check second sort: " << std::endl;

	previousYear = 0;
	currentYear  = 0;

	for (auto currentCar : sortedList2) {
		if (previousYear) { // skip first
			currentYear = currentCar.getYear();
			
			std:: cout << "Checking that `" << previousYear << "` >= `" 
					   << currentYear << "`." << std::endl;
			ASSERT_GE(previousYear, currentYear);
		}
		previousYear = currentCar.getYear();
	}
	std::cout << std::endl;
}

// Okay maybe a few more tests.. Check edge cases
TEST(SortTests, SortListFullOfDuplicates) {
	std::vector<Syn::Car> cars1 {
		Syn::Car("Mazda", "RX7", 1995),
		Syn::Car("Mazda", "RX7", 1995),
		Syn::Car("Mazda", "RX7", 1995),
		Syn::Car("Mazda", "RX7", 1995),
		Syn::Car("Mazda", "RX7", 1995),
	};

	Syn::LinkedList list1(5);
	for (auto car : cars1) {
		ASSERT_TRUE(list1.appendFront(car));
	}
	ASSERT_EQ(5, list1.size());

	Syn::LinkedList sortedList(5);
	Syn::MergeSort::sortDescending(list1, sortedList);

	uint32_t previousYear = 0;
	uint32_t currentYear  = 0;

	for (auto currentCar : sortedList) {
		if (previousYear) { // skip first
			currentYear = currentCar.getYear();
			ASSERT_GE(previousYear, currentYear);
		}
		previousYear = currentCar.getYear();
	}
}

TEST(SortTests, SortListFullOfBadData) {
	std::vector<Syn::Car> cars1 {
		Syn::Car("", "", 0),
		Syn::Car("", "", 0),
		Syn::Car("", "", 0),
		Syn::Car("", "", 0),
		Syn::Car("", "", 0),
	};

	Syn::LinkedList list1(5);
	for (auto car : cars1) {
		ASSERT_TRUE(list1.appendFront(car));
	}
	ASSERT_EQ(5, list1.size());

	Syn::LinkedList sortedList(5);
	Syn::MergeSort::sortDescending(list1, sortedList);

	uint32_t previousYear = 0;
	uint32_t currentYear  = 0;

	for (auto currentCar : sortedList) {
		if (previousYear) { // skip first
			currentYear = currentCar.getYear();
			ASSERT_GE(previousYear, currentYear);
		}
		previousYear = currentCar.getYear();
	}
}

TEST(SortTests, SortEmptyList) {
	Syn::LinkedList list1;

	ASSERT_EQ(0, list1.size());

	Syn::LinkedList sortedList;
	Syn::MergeSort::sortDescending(list1, sortedList);

	ASSERT_EQ(0, sortedList.size());
}

TEST(SortTests, SortListOf1) {
	Syn::LinkedList list1(1);
	ASSERT_TRUE(list1.appendFront(Syn::Car("Mazda", "RX7", 1995)));
	ASSERT_EQ(1, list1.size());

	Syn::LinkedList sortedList(1);
	Syn::MergeSort::sortDescending(list1, sortedList);

	ASSERT_EQ(1, sortedList.size());
}

TEST(SortTests, SortListOf2) {
	Syn::LinkedList list1(2);
	ASSERT_TRUE(list1.appendFront(Syn::Car("Mazda", "RX7", 1995)));
	ASSERT_TRUE(list1.appendFront(Syn::Car("Honda", "Civic", 1997)));
	ASSERT_EQ(2, list1.size());

	Syn::LinkedList sortedList(2);
	Syn::MergeSort::sortDescending(list1, sortedList);

	ASSERT_EQ(2, sortedList.size());

	auto car1 = sortedList.begin();
	auto car2 = ++sortedList.begin();

	ASSERT_GE((*car1).getYear(), (*car2).getYear());
}

TEST(SortTests, SortListOf3) {
	Syn::LinkedList list1(3);
	ASSERT_TRUE(list1.appendFront(Syn::Car("Mazda", "RX7", 1995)));
	ASSERT_TRUE(list1.appendFront(Syn::Car("Toyota", "GR Yaris", 2025)));
	ASSERT_TRUE(list1.appendFront(Syn::Car("Honda", "Civic", 1997)));
	ASSERT_EQ(3, list1.size());

	Syn::LinkedList sortedList(3);
	Syn::MergeSort::sortDescending(list1, sortedList);

	ASSERT_EQ(3, sortedList.size());

	auto car1 = sortedList.begin();
	auto car2 = ++sortedList.begin();
	auto car3 = ++(++sortedList.begin());

	ASSERT_GE((*car1).getYear(), (*car2).getYear());
	ASSERT_GE((*car2).getYear(), (*car3).getYear());
}
