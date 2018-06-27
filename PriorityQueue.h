#ifndef _PR_QUEUE_H
#define _PR_QUEUE_H

/*
 * Some headers that may be useful.
 * The utility header is included for the
 * std::pair<X,Y> class, used below.
 */
#include <vector>
#include <list>
#include <utility>
#include <iostream>

 /*
  * This class implements a priority queue ADT
  * with priorities specified in ints.
  * Lower priority values precede higher values in
  * the ordering.
  * The template type E is the element type.
  * See the tests for examples.
  */
template <typename E>
class PriorityQueue {

private:

	 // The min-heap of paired priority and element, stored in a vector.
	std::vector<std::pair<int, E> > heap;

public:

	/*
	 * A constructor, if you need it.
	 */
	PriorityQueue() {}

	/*
	 * Returns the index of the parent.
	 */
	int getParent(int child) {
		return (child - 1) / 2;
	}

	/*
	 * Returns the index of the left child.
	 */
	int getLeftChild(int parent) {
		return 2 * parent + 1;
	}

	/*
	 * Returns the index of the right child.
	 */
	int getRightChild(int parent) {
		return 2 * parent + 2;
	}

	/*
	 * Recursive up-heap operation to test the violation of
	 * the min-heap rule between the child and parent.
	 *
	 * Algorithm:
	 * Compare the child (the new element) with its parent.
	 * If the child is smaller, swap it with its parent.
	 * Continue the process until either:
	 *	-the new element's parent is smaller than its child.
	 *	-the new element reaches the root (index 0 of the vector).
	 */
	void bubbleUp(int child) {
		int parent = getParent(child);

		if (child == 0)
			return;

		if (heap[child] < heap[parent]) {
			std::swap(heap[child], heap[parent]);
			bubbleUp(parent);
		}
	}

	/*
	 * This function adds a new element "element" to the queue
	 * with priority "priority".
	 *
	 * Algorithm:
	 * Check to ensure that the priority parameter is a non-negative integer.
	 * Add the paired priority and element into the bottom of the heap (last element in the vector).
	 * Perform up-heap operation (bubbleUp) from the bottom to satisfy the min-heap property.
	 */
	void insert(int priority, E element) {
		if (priority >= 0) {
			heap.push_back(std::make_pair(priority, element));
			bubbleUp(heap.size() - 1);
		}
	}

	/*
	 * Similar to insert, but takes a whole vector of new things to
	 * add.
	 */
	void insert_all(std::vector<std::pair<int, E> > new_elements) {
		// Iterate through the vector and add each element using the insert function.
		for (typename std::vector<std::pair<int, E> >::iterator it = new_elements.begin(); it != new_elements.end(); ++it) {
			insert(it->first, it->second);
		}
	}

	/*
	 * Recursive down-heap operation to test the violation of
	 * the min-heap rule between the parent and its left and right child.
	 *
	 * Algorithm:
	 * Remove the parent (root) element.
	 * Get left and right child of node at parent index.
	 * Compare the parent with its left and right child,
	 * and find the smallest index.
	 * If the child is smaller, swap with its parent.
	 * Continue the process until the smallest index is in the root element.
	 */
	void bubbleDown(int parent) {
		int length = heap.size();
		int left = getLeftChild(parent);
		int right = getRightChild(parent);
		int minIndex = parent;

		if (left < length && heap[left] < heap[minIndex])
			minIndex = left;

		if (right < length && heap[right] < heap[minIndex])
			minIndex = right;

		if (minIndex != parent) {
			std::swap(heap[minIndex], heap[parent]);
			bubbleDown(minIndex);
		}
	}

	/*
	 * Takes the lowest priority value element off the queue,
	 * and returns it.
	 *
	 * Algorithm:
	 * Check if the heap is not empty.
	 *	Place the root element (first element) in a variable to return later.
	 *	Replace the last element in the deepest level with the root and delete the element.
	 *	Perform down-heap operation (bubbleDown) from the root to satisfy the min-heap property.
	 *	Return the original root that was saved.
	 * If heap is empty, return an empty element.
	 */
	E remove_front() {
		if (!empty()) {
			E element = peek();

			heap.front() = heap.back();
			heap.pop_back();

			bubbleDown(0);

			return element;
		}
		else
			return E();
	}

	/*
	 * Returns the lowest priority value element in the queue, but leaves
	 * it in the queue.
	 *
	 * Algorithm:
	 * Check if the heap is not empty.
	 *	Return the first value element in the queue,
	 *	because the heap already satisfies the min-heap property (sorted).
	 * If heap is empty, return an empty element.
	 */
	E peek() {
		if (!empty())
			return heap.front().second;
		else
			return E();
	}

	/*
	 * Returns a vector containing all the elements in the queue.
	 */
	std::vector<E> get_all_elements() {
		// Iterate through the heap and add each elements into the output vector.
		std::vector<E> output;
		for (typename std::vector<std::pair<int, E> >::iterator it = heap.begin(); it != heap.end(); ++it) {
			output.push_back(it->second);
		}
		return output;
	}

	/*
	 * Returns true if the queue contains element "element", false
	 * otherwise.
	 */
	bool contains(E element) {
		// Iterate through the heap to check if it contains the "element"
		for (typename std::vector<std::pair<int, E> >::iterator it = heap.begin(); it != heap.end(); ++it) {
			if (it->second == element) {
				return true;
			}
		}
		return false;
	}

	/*
	 * Returns the priority of the element that matches
	 * "element". If there is more than one, it returns
	 * the lowest priority value.
	 * If no element matches, return -1.
	 */
	int get_priority(E element) {
		// Iterate through the heap to find the matched element.
		for (typename std::vector<std::pair<int, E> >::iterator it = heap.begin(); it != heap.end(); ++it) {
			if (it->second == element) {
				return it->first;
			}
		}
		return -1;
	}

	/*
	 * Returns a vector containing all the priorities.
	 * The ordering of the vector should match that of the
	 * return from get_all_elements().
	 * That is, the priority of the element
	 * get_all_elements()[i] should be get_all_priorities()[i].
	 */
	std::vector<int> get_all_priorities() {
		// Iterate through the heap and add each priority into the output vector.
		std::vector<int> output;
		for (typename std::vector<std::pair<int, E> >::iterator it = heap.begin(); it != heap.end(); ++it) {
			output.push_back(it->first);
		}
		return output;
	}

	/*
	 * Finds the first (in priority order) element that matches
	 * "element", and changes its priority to "new_priority".
	 *
	 * Algorithm:
	 * Iterate through the heap, if the first element matches "element",
	 * Remove it from the heap.
	 * Re-insert it with the "new_priority".
	 * This way the min-heap property remains true after a priority change.
	 */
	void change_priority(E element, int new_priority) {
		bool foundElement = false;
		typename std::vector<std::pair<int, E> >::iterator it = heap.begin();
		while (it != heap.end()) {
			if (it->second == element) {
				it = heap.erase(it);
				foundElement = true;
			}
			else
				++it;
		}

		if (foundElement) {
			insert(new_priority, element);
		}
	}

	/*
	 * Returns the number of elements in the queue.
	 */
	int size() {
		return heap.size();
	}

	/*
	 * Returns true if the queue has no elements, false otherwise.
	 */
	bool empty() {
		return heap.size() == 0;
	}

};

#endif
