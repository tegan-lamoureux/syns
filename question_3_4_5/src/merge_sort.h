#pragma once

#include <memory>

#include "linked_list.h"

namespace Syn {

// State-less, static, merge-sort for Syn::LinkedList.
class MergeSort {
public:

	// Per the requirements, this takes in an empty list and fills that list with all data from
	// this list, but sorted in descending order. This means it *does* allocate memory.
	//
	// Returns false if the input list is not empty or this list is empty. True otherwise.
	static bool sortDescending(const LinkedList& original, LinkedList& sorted)
	{
		bool result = false;

		if (original.listSize > 0 && sorted.listSize == 0) {
			// First copy into new list, which we will work from
			// This reverses order. We don't care, we will sort.
			for (auto item : original) {
				sorted.appendFront(item);
			}

			sorted.head = mergeSort(std::move(sorted.head));

			result = true;
		}

		return result;
	}

private:

	// Required since we need to traverse to find list midpoint (&head b/c head is modified)
	static std::unique_ptr<Node> split(std::unique_ptr<Node>& head)
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

	// Recursive merge sort
	static std::unique_ptr<Node> mergeSort(std::unique_ptr<Node> list)
	{
		if (!list || !list->next)
			return list; // recursion end

		std::unique_ptr<Node> secondList = split(list);

		list = mergeSort(std::move(list));
		secondList = mergeSort(std::move(secondList));

		return merge(std::move(list), std::move(secondList));
	}
	
	// Merge two already sorted lists
	static std::unique_ptr<Node> merge(std::unique_ptr<Node> left, std::unique_ptr<Node> right)
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
};

}