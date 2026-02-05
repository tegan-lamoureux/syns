#include "circular_buffer.h"

namespace Syn {

CircularBuffer::CircularBuffer(uint32_t size)
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

bool CircularBuffer::push(uint8_t value)
{
	bool result = false;

	return result;
}

bool CircularBuffer::pop(uint8_t& value)
{
	bool result = false;

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

inline bool CircularBuffer::isEmpty()
{
    return currentSize == 0;
}

inline bool CircularBuffer::isFull()
{
    return currentSize == allocatedSize;
}

}