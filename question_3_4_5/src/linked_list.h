#pragma once

#include <cstdint>
#include <memory>

#include "car.h"

namespace Syn {

class LinkedList {
public:
	LinkedList();
	LinkedList(const uint32_t maxSize);

	std::size_t size() const;
	bool isEmpty() const;

	bool appendFront(const Car& car);

	// Maybe add a clear(), if so update docs

	// Add iterators for traversal
	
private:
	class Node {
	public:
		std::unique_ptr<Node> next{nullptr};
		std::unique_ptr<Car> data{nullptr};
	};

	std::unique_ptr<Node> head;
	uint32_t maxSize;
	std::size_t listSize;
};

}
