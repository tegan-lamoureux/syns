#include <gtest/gtest.h>
#include <iostream>
#include <iomanip>

#include "car.h"
#include "linked_list.h"
#include "sort_list.h"


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
	Syn::ListSorter::Sort(list1, sortedList);

	// // Check list is in ascending order. 
	auto previousCar = sortedList.begin();
	for (auto currentCar : sortedList) {
		if (previousCar != sortedList.begin()) { // skip first
			ASSERT_TRUE(*previousCar < currentCar);
		}
	}
}

