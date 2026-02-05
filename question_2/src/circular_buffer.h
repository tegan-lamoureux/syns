#pragma once

#include <memory>
#include <cstdint>

namespace Syn {

class CircularBuffer {
public:
    // Constructor/destructor
    CircularBuffer() = delete; // force size at creation
    explicit CircularBuffer(uint32_t size);
    ~CircularBuffer();

    // Copy constructor
    CircularBuffer(CircularBuffer const& copy);


private:
    std::unique_ptr<uint8_t> buffer;
};

}
