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

ListIterator LinkedList::begin() const
{
	return ListIterator(this->head);
}

ListIterator LinkedList::end() const
{
	return ListIterator();
}

bool LinkedList::sortDescending(LinkedList &sorted)
{
	bool result = false;

	if (this->listSize > 0 && sorted.listSize == 0) {
		// First copy into new list, which we will work from
		// This reverses order. We don't care, we will sort.
		for (auto item : *this) {
			sorted.appendFront(item);
		}

		sorted.head = mergeSort(std::move(sorted.head));
	}

    return result;
}

std::unique_ptr<Node> LinkedList::split(std::unique_ptr<Node>& head)
{
    Node* slow = head.get();
	Node* fast = head->next.get();

	// Traverse while ++slow, ++(++)fast, so that slow ends up at midpoint when fast is at end
	while (fast && fast->next.get()) {
		slow = slow->next.get();
		fast = fast->next->next.get();
	}

	std::unique_ptr<Node> secondList = std::move(slow->next);
	slow->next = nullptr; // break the list at midpoint

	return secondList;
}

std::unique_ptr<Node> LinkedList::mergeSort(std::unique_ptr<Node> list)
{
    if (!list && !list->next)
		return list; // recursion end

	std::unique_ptr<Node> secondList = split(list);

	list = mergeSort(std::move(list));
	secondList = mergeSort(std::move(secondList));

	return merge(std::move(list), std::move(secondList));
}

std::unique_ptr<Node> LinkedList::merge(std::unique_ptr<Node> left, std::unique_ptr<Node> right)
{
	// Recurse until we have one left? Then return that zippered into the other
    if (!left) return right;
	if (!right) return left;

	if (left->data->getYear() > right->data->getYear()) { // sort descending
		left->next = merge(std::move(left->next), std::move(right));
		return left;
	}
	else {
		right->next = merge(std::move(left), std::move(right->next));
		return right;
	}
}



// Iterator Definition

ListIterator::ListIterator()
	: currentNode{nullptr},
	  previousNode{nullptr}
{
}

ListIterator::ListIterator(const std::unique_ptr<Node> &node)
	: currentNode{node.get()},
	  previousNode{nullptr}
{
}

ListIterator &ListIterator::operator++()
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
	++ *this;
	return temp;
}

bool ListIterator::operator!=(const ListIterator &other) const
{
	return this->currentNode != other.currentNode;
}

bool ListIterator::operator==(const ListIterator &other) const
{
	return this->currentNode == other.currentNode;
}

Car& ListIterator::operator*() const
{
	return *this->currentNode->data;
}

}