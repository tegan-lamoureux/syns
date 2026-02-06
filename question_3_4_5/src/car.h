#pragma once

#include <cstdint>
#include <string>

namespace Syn {

class Car {
public:
	Car() = delete; // force details at creation
	explicit Car(const std::string make, const std::string model, const uint32_t year)
		: make(make), model(model), year(year) {}

	// Equality operator overload, QOL improvement
	bool operator!=(const Car &other) const
	{ return make != other.make || model != other.model || year != other.year; }
	bool operator==(const Car &other) const
	{ return make == other.make && model == other.model && year == other.year; }

	std::string getMake() const { return make; }
	std::string getModel() const { return model; }
	uint32_t getYear() const { return year; }
	
private:
	std::string make;
	std::string model;
	uint32_t year;
};

}
