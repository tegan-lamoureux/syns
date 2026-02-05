#pragma once

#include <cstdint>

namespace Syn {

class LinkedList {
public:
	LinkedList() = delete; // force details at creation
	explicit LinkedList(const uint32_t size);
	
private:
};

}
