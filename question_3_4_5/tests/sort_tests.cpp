#include <gtest/gtest.h>
#include <iostream>

#include "car.h"
#include "linked_list.h"


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
	list1.sortDescending(sortedList);

	// // Check list is in ascending order. 
	uint32_t previousYear = 0;
	uint32_t currentYear  = 0;
	for (auto currentCar : sortedList) {
		if (previousYear) { // skip first
			currentYear = currentCar.getYear();
			ASSERT_GE(previousYear, currentYear);
		}
		previousYear = currentCar.getYear();
	}

	// Sort second
	Syn::LinkedList sortedList2(5);
	list2.sortDescending(sortedList2);

	// // Check list is in ascending order. 
	previousYear = 0;
	currentYear  = 0;
	for (auto currentCar : sortedList2) {
		if (previousYear) { // skip first
			currentYear = currentCar.getYear();
			ASSERT_GE(previousYear, currentYear);
		}
		previousYear = currentCar.getYear();
	}
}

// check list duplicates


