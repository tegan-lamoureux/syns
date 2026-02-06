#pragma once

#include <cstdint>
#include <memory>

#include "car.h"

// Note: Templates would make this MUCH more generic, but felt out of scope.

namespace Syn {

class Node {
public:
	std::unique_ptr<Node> next{nullptr};
	std::unique_ptr<Car> data{nullptr};
};


// Custom iterator for traversing linked list. Added for quality of life. Allows 
// range based for loops, traversal of the list with ++ operator, equality check 
// of iterators, etc.
class ListIterator {
public:
	ListIterator();
	ListIterator(const std::unique_ptr<Node> &node);

	ListIterator &operator++();   // pre-increment
	ListIterator operator++(int); // post-increment
	bool operator!=(const ListIterator &other) const;
	bool operator==(const ListIterator &other) const;
	Car& operator*() const;

private:
	Node *previousNode;
	Node *currentNode;
};


class LinkedList {
public:
	LinkedList();
	LinkedList(const uint32_t maxSize);

	std::size_t size() const;
	bool isEmpty() const;

	bool appendFront(const Car& car);

	// Note: Can add other nice methods, such as appendBack(), clear(), delete() ...
	// Left out for sake of scope and time.

	ListIterator begin() const;
	ListIterator end() const;

	// Per the requirements, this takes in an empty list and returns a new copy of that 
	// list, which is this list but sorted in descending order. This means it *does* 
	// allocate memory.
	//
	// Returns false if the input list is not empty or this list is empty. True otherwise.
	bool sortDescending(LinkedList& sorted);
	
private:
	std::unique_ptr<Node> head;
	uint32_t maxSize;
	std::size_t listSize;
};

}
