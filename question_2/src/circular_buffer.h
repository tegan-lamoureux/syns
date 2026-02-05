#pragma once

#include <memory>
#include <cstdint>

namespace Syn {

class CircularBuffer {
public:
	CircularBuffer() = delete; // force size at creation
	explicit CircularBuffer(uint32_t size);

	// Push value into buffer. Return false when full.
	bool push(uint8_t value);

	// Remove value from buffer. Return false when empty.
	bool pop(uint8_t& value);

private:
	std::unique_ptr<uint8_t[]> buffer;
	uint32_t head;
	uint32_t tail;
	uint32_t allocatedSize;
	uint32_t currentSize;

	void incrementHead();
	void incrementTail();

	bool isEmpty();
	bool isFull();
};

}
