#include "circular_buffer.h"

namespace Syn {

explicit CircularBuffer::CircularBuffer(uint32_t size)
    : buffer(nullptr)
{
    if (size) {
        buffer = new uint32_t[size];
    }
}

CircularBuffer::CircularBuffer()
    : buffer(nullptr)
{
}


}