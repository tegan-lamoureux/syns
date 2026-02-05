#include <gtest/gtest.h>
#include <iostream>
#include <iomanip>

#include "car.h"
#include "linked_list.h"
#include "sort_list.h"


// The one, the only.
TEST(SortTests, Sort) {
	Syn::LinkedList list1(10);
	Syn::LinkedList list2(10);

	Syn::ListSorter::Sort(list1, list2);

	// Did it do it? Print results along with asserts

	// This is too much. 
	// Do it logically. Iterate and assert each is after the next

	std::cout << "Sorted List: " << std::endl<< std::endl;
	for (int i = 0; i < 10; i++) {
		std::cout << std::left 
			<< "Original[" << i << "] Make: " << std::setw(20)  << "Toyota"
			<< "Sorted["   << i << "] Make: " << std::setw(20)  << "Toyota"
			<< std::endl

			<< std::setw(20) << "            Model: " << std::setw(20)  << "Yaris"
			<< std::setw(20) << "        Model: "   << std::setw(20)  << "Camry"
			<< std::endl
			
			<< std::setw(20) << "            Year: " << std::setw(20)  << "2014"
			<< std::setw(20) << "        Year: "   << std::setw(20)  << "2019"
			<< std::endl << std::endl;
	}
}

