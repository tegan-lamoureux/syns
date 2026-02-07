# Second Question Solution

## Design Notes 

### Complexity 

The question sheet said to not use structures from std library, so instead of using a vector here for internal storage, I am using a pointer and heap-allocated memory. I am, however, using C++11 smart pointers and heap allocation helpers (make_unique...). This means the class can not be copied trivially with an assignment operator, but must use the std::move paradigm.

I thought this was an okay compromise. Using raw pointers would have required me to follow [the rule of 5](https://en.cppreference.com/w/cpp/language/rule_of_three.html), which massively increases complexity.

~ Tegan

### Testing

Tests weren't required for this solution per the prompt, but I find test-driven-development easiest in domains like this, so I also included the gtest suite here. This also allows you to easily evaluate the solution, and add your own tests, if you desire.

The google test suite is downloaded and built automatically with CMake.

### Heap Check

With dynamic memory, I like checking with valgrind. Please find the output below:

```
▶ valgrind ./question_2/build/circular_buffer_test > /dev/null              
==81897== Memcheck, a memory error detector
==81897== Copyright (C) 2002-2024, and GNU GPL'd, by Julian Seward et al.
==81897== Using Valgrind-3.25.1 and LibVEX; rerun with -h for copyright info
==81897== Command: ./question_2/build/circular_buffer_test
==81897== 
==81897== 
==81897== HEAP SUMMARY:
==81897==     in use at exit: 0 bytes in 0 blocks
==81897==   total heap usage: 549 allocs, 549 frees, 147,678 bytes allocated
==81897== 
==81897== All heap blocks were freed -- no leaks are possible
==81897== 
==81897== For lists of detected and suppressed errors, rerun with: -s
==81897== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

### Sources
I used the gtest quick-start documentation for fast bringup of my CMakeLists.txt, [found here](https://google.github.io/googletest/quickstart-cmake.html).


## Building & Running Tests (Linux)

From the solution directory:

1. Initialize cmake: `cmake -S . -B build`
2. Build the tests: `cmake --build build`
3. Run the tests: `build/circular_buffer_test`

### Note: 
This should build cross-platform, but I only had a linux computer to develop on. Commands will need to be modified slightly to build under Windows.