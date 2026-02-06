# Third and Fourth Question Solution

## Design Notes 

### Assumptions

For questions 2 and 3, it was assumed reentrancy and thread safety were not concerns. The solutions are absolutely neither, and in a multithreaded application, concurrency issues would immediately arise. 

This could be mitigated by adding locking into the classes with mutexes (for ex, via std::unique_lock). This does, however, require hardware support for an atomic test-and-set assembly instruction. These exist on nearly all SOCs and high powered ARM processors, but smaller ones, like the Cortex-M0, lack this. In that case, techniques such as disabling interrupts for critical sections, or using a lockless data structure, could be used.

I also didn't add nearly as many class members as could be added (appendBack(), delete(iterator&), reverse(), etc). I kept it only to the scope of the problem.

### C++ 11 Features

As with the previous solution I am using smart pointer features from C++11 for garbage collection of heap allocated mem. 

These work very well in this case, with unique pointers owning the allocated data, and sequential cleanup happening down the list automatically when the head object (the only one the "class" allocates) is destroyed in the implicit List destructor.

**Iterators**: I chose to use a custom iterator for the List class, to support a nice generic sort algorithm, and to keep it in line with modern C++. 

#### Heap Disclaimer 

Just a small note: I'm fully aware of the challenges and complexities of heap-allocation on embedded systems, especially high-reliability ones, in regards to fragmentation and allocation performance. 

### Sorting

I'm an embedded engineer, and while I know the basic sorts and their runtimes, this isn't a domain of expertise for me. So, I did my research:

I wanted a sort that didn't have heavy data structures attached to it or extreme complexity in implementation, because of my own time constraints in finishing this exercise. This led me to evaluate Quick sort and Merge sort, when targeting an average complexity of `O(n log(n))`, . 

Worst case, however, has Quick sort with `O(n^2)` versus Merge's `O(n log(n))`, and I remember favouring Merge sort from my university days, so I decided to go with that. No stronger reasons. It depends highly on system architecture and data format, [as I read in this great thread](https://stackoverflow.com/questions/70402/why-is-quicksort-better-than-mergesort), so without further information, this should be sufficient.

### Sources

I have been working a lot in C lately, so [I brushed up on my iterators](https://medium.com/geekculture/iterator-design-pattern-in-c-42caec84bfc), [iterator design](https://stackoverflow.com/questions/3582608/how-to-correctly-implement-custom-iterators-and-const-iterators) and also read [this great essay on auto and smart pointers](https://herbsutter.com/elements-of-modern-c-style/) in C++ 11. These are things I conceptually know, but after some years, the implementation details slip away.

I also referenced the wikipedia pages for Circular Buffers, Linked Lists, Merge Sort, and various other features as I came across them, along with having a constant tab to cppreference.com open. Again, I have high level knowledge here. But when writing the actual implementation, working with a reference is smart, rather than reinventing the wheel. 

I chose not to use templates, for debugging sanity and development velocity. They can be added in.

C++ development is difficult to do correctly, and very easy to do incorrectly. Working with language documentation and references is invaluable, imo.

### Testing

As with Solution 2, I used google test suite, which is downloaded and built automatically with CMake.

Assumptions made in testing were limiting the test scope to the defined problem. I did not implement extra features of the Linked List (remove, reverse, etc..), so these areas will not be tested.

## Building & Running Tests (Linux)

From the solution directory:

1. Initialize cmake: `cmake -S . -B build`
2. Build the tests: `cmake --build build`
3. Run all tests: `build/linked_list_tests`
4. Run only the sort test: `./linked_list_tests --gtest_filter="SortTests.*"`

### Note: 
This should build cross-platform, but I only had a linux computer to develop on. Commands will need to be modified slightly to build under Windows.
