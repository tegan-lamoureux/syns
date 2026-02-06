#include "linked_list.h"

namespace Syn {

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

bool LinkedList::appendFront(const Car &car)
{
	bool result = false;

	if (listSize < maxSize) {
		// Make a new node,
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

		listSize++;
		result = true;
	}

    return result;
}

}