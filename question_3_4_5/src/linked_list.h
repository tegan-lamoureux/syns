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
	ListIterator(const std::unique_ptr<Node>& node);

	ListIterator& operator++();   // pre-increment
	ListIterator operator++(int); // post-increment
	bool operator!=(const ListIterator& other) const;
	bool operator==(const ListIterator& other) const;
	Car& operator*() const;

private:
	Node* previousNode;
	Node* currentNode;
};


class LinkedList {
	// A lot of ways to do this. This introduces tight coupling that I'm not a big fan 
	// of, but allows keeping the node structure and raw pointers hidden.
	//
	// I wrote a merge sort for a linked list, specifically, this linked list, instead
	// of a generic STL container, so I feel this coupling is okay. -T
	friend class MergeSort;

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
	
private:
	std::unique_ptr<Node> head;
	uint32_t maxSize;
	std::size_t listSize;
};

}
