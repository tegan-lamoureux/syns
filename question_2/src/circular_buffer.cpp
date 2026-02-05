#include "circular_buffer.h"

namespace Syn {

CircularBuffer::CircularBuffer(uint32_t size)
	: buffer(nullptr)
{
	if (size) {
		buffer = std::make_unique<uint8_t[]>(size);
	}
}

}