#pragma once

#include <memory>
#include <cstdint>

namespace Syn {

class CircularBuffer {
public:
	CircularBuffer() = delete; // force size at creation
	explicit CircularBuffer(uint32_t size);


private:
	std::unique_ptr<uint8_t[]> buffer;
};

}
