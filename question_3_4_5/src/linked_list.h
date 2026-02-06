#pragma once

#include <cstdint>
#include <memory>

#include "car.h"

namespace Syn {

class Node {
public:
	std::unique_ptr<Node> next{nullptr};
	std::unique_ptr<Car> data{nullptr};
};

// Custom iterator for traversing linked list
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
	const Node *previousNode;
	const Node *currentNode;
};


class LinkedList {
public:
	LinkedList();
	LinkedList(const uint32_t maxSize);

	std::size_t size() const;
	bool isEmpty() const;

	bool appendFront(const Car& car);

	// TODO:
	// Can add other nice methods, such as appendBack(), clear(), delete() ...
	// Left out for sake of scope and time. -Tegan

	ListIterator begin();
	ListIterator end();
	
private:
	std::unique_ptr<Node> head;
	uint32_t maxSize;
	std::size_t listSize;
};

}
