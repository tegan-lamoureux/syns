#include "circular_buffer.h"

namespace Syn {

CircularBuffer::CircularBuffer(const uint32_t size)
	: buffer{nullptr},
	  head{0},
	  tail{0},
	  allocatedSize{size},
	  currentSize{0}
{
	if (size) {
		buffer = std::make_unique<uint8_t[]>(size);
	}
}

bool CircularBuffer::push(const uint8_t value)
{
	bool result = false;

	if (buffer && !isFull()) {
		buffer[head] = value;
		incrementHead();
		currentSize++;

		result = true;
	}

	return result;
}

bool CircularBuffer::pop(uint8_t& value)
{
	bool result = false;

	if (buffer && !isEmpty()) {
		value = buffer[tail];
		incrementTail();
		currentSize--;

		result = true;
	}

	return result;
}

inline void CircularBuffer::incrementHead()
{
	if (head < (allocatedSize - 1)) {
		head++;
	}
	else {
		head = 0;
	}
}

inline void CircularBuffer::incrementTail()
{
	if (tail < (allocatedSize - 1)) {
		tail++;
	}
	else {
		tail = 0;
	}
}

inline bool CircularBuffer::isEmpty() const
{
    return currentSize == 0;
}

inline bool CircularBuffer::isFull() const
{
    return currentSize == allocatedSize;
}

}