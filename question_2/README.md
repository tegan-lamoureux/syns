# Second Question Solution

## Design Notes 

### Complexity 

The question sheet said to not use structures from std library, so instead of using a vector here for internal storage, I am using a pointer and heap-allocated memory. I am, however, using C++14 smart pointers and heap allocation helpers (make_unique...). This means the class can not be copied trivially with an assignment operator, but must use the std::move paradigm.

I thought this was an okay compromise. Using raw pointers would have required me to follow [the rule of 5](https://en.cppreference.com/w/cpp/language/rule_of_three.html), which massively increases complexity.

~ Tegan

### Testing

Tests weren't required for this solution per the prompt, but I find test-driven-development easiest in domains like this, so I also included the gtest suite here. This also allows you to easily evaluate the solution, and add your own tests, if you desire.

### Sources
I used the gtest documentation for fast bringup, [found here](https://google.github.io/googletest/quickstart-cmake.html).


## Building & Running Tests (Linux)

From the solution directory:

1. `cmake -S . -B build`
2. `cmake --build build`
3. `build/circular_buffer_test`

### Note: 
This should build cross-platform, but I only had a linux computer to develop on. Commands will need to be modified slightly to build under Windows.