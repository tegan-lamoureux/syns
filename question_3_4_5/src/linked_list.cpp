#include "linked_list.h"

namespace Syn {


// LinkedList Definition

LinkedList::LinkedList()
	: head{nullptr},
	  maxSize{UINT32_MAX},
	  listSize{0}
{
}

LinkedList::LinkedList(const uint32_t size)
	: head{nullptr},
	  maxSize{size},
	  listSize{0}
{
}

std::size_t LinkedList::size() const
{
	return listSize;
}

bool LinkedList::isEmpty() const
{
	return head == nullptr;
}

bool LinkedList::appendFront(const Car& car)
{
	bool result = false;

	if (listSize < maxSize) {
		// Make a new node, then..
		std::unique_ptr<Node> newNode = std::make_unique<Node>();
		newNode->data = std::make_unique<Car>(car.getMake(), car.getModel(), car.getYear());

		if (isEmpty()) {
			// Move to head
			head = std::move(newNode);
		}
		else {
			// Move head to new node's next pointer, and move new node to head pointer
			newNode->next = std::move(head);
			head = std::move(newNode);
		}

		++listSize;
		result = true;
	}

	return result;
}

ListIterator LinkedList::begin() const
{
	return ListIterator(this->head);
}

ListIterator LinkedList::end() const
{
	return ListIterator(); // last_node->next == empty iterator
}



// Iterator Definition

ListIterator::ListIterator()
	: currentNode{nullptr},
	  previousNode{nullptr}
{
}

ListIterator::ListIterator(const std::unique_ptr<Node>& node)
	: currentNode{node.get()},
	  previousNode{nullptr}
{
}

ListIterator& ListIterator::operator++()
{
	// Move down the list by 1 list item
	if (currentNode != nullptr) {
		previousNode = currentNode;
		currentNode = currentNode->next.get();
	}
	return *this;
}

ListIterator ListIterator::operator++(int)
{
	ListIterator temp = *this; // save un-iterated copy for returning (this is post-increment)
	++ *this; // cheat with our already defined preincrement
	return temp;
}

bool ListIterator::operator!=(const ListIterator& other) const
{
	return this->currentNode != other.currentNode;
}

bool ListIterator::operator==(const ListIterator& other) const
{
	return this->currentNode == other.currentNode;
}

Car& ListIterator::operator*() const
{
	return *this->currentNode->data;
}

}