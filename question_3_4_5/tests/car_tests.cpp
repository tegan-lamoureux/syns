#include <gtest/gtest.h>

#include "car.h"


TEST(CarTests, SmokeTest) {
	Syn::Car car("Toyota", "GR Yaris", 2024);
}

TEST(CarTests, GetData) {
	Syn::Car car("Toyota", "GR Yaris", 2024);
	
	ASSERT_EQ("Toyota", car.getMake());
	ASSERT_EQ("GR Yaris", car.getModel());
	ASSERT_EQ(2024, car.getYear());

	ASSERT_NE("Asd", car.getMake());
	ASSERT_NE("BSD", car.getModel());
	ASSERT_NE(1984, car.getYear());
}

TEST(CarTests, GetDataEmpty) {
	Syn::Car car("", "", 0);
	
	ASSERT_EQ("", car.getMake());
	ASSERT_EQ("", car.getModel());
	ASSERT_EQ(0, car.getYear());

	ASSERT_NE("Asd", car.getMake());
	ASSERT_NE("BSD", car.getModel());
	ASSERT_NE(1984, car.getYear());
}

TEST(CarTests, Equality) {
	Syn::Car car1("Toyota", "GR Yaris", 2024);
	Syn::Car car2("Toyota", "GR Yaris", 2024);
	
	ASSERT_TRUE(car1 == car2);
}

TEST(CarTests, Inequality) {
	Syn::Car car1("Toyota", "Corolla", 1990);
	Syn::Car car2("Toyota", "Supra", 1997);
	
	ASSERT_TRUE(car1 != car2);
}
