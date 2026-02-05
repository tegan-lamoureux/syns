# Third and Fourth Question Solution

## Design Notes 

As with the previous solution I am using smart pointer features from C++11 and 14 for garbage collection of heap allocated mem. I believe I will be submitting this quite early, so if you wish for a proper raw-pointer implementation with a destructor, copy constructor, assignment operator, etc, etc, just let me know. :) I will have time to write them.

Also, I'm fully aware of the challenges and complexities of heap-allocation on embedded systems, especially high-reliability ones, in regards to fragmentation and allocation performance. It obviously depends on the operating system and implementation. 

This wasn't part of the prompt, but I felt the need to include a disclaimer due to the hiring position. 

### Testing

As with Solution 2, I used google test suite, which is downloaded and built automatically with CMake.

## Building & Running Tests (Linux)

From the solution directory:

1. Initialize cmake: `cmake -S . -B build`
2. Build the tests: `cmake --build build`
3. Run the tests: `build/linked_list_tests`

### Note: 
This should build cross-platform, but I only had a linux computer to develop on. Commands will need to be modified slightly to build under Windows.
