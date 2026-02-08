# Third and Fourth Question Solution

## Design Notes 

### Assumptions

For questions 2 and 3, it was assumed reentrancy and thread safety were not concerns. The solutions are absolutely neither, and in a multithreaded application, concurrency issues would immediately arise. This could be mitigated by adding locking into the classes (for ex, via std::unique_lock) on hardware that supports it (some smaller MCUs, like the Cortex-M0, do not have the silicon support for test-and-set).

I also didn't add nearly as many class members as could be added (appendBack(), delete(iterator&), reverse(), etc). I kept it only to the scope of the problem.

### C++ 11 Features

As with the previous solution I am using smart pointer features from C++11 for garbage collection of heap allocated mem. 

**Iterators**: I chose to use a custom iterator for the List class, to help quality of life in testing and to encapsulate the pointers and memory management internally.

**Heap Disclaimer**: Just a small note: I'm fully aware of the challenges and complexities of heap-allocation on embedded systems, especially high-reliability ones, in regards to fragmentation and allocation performance. 

### Sorting

I'm an embedded engineer, and while I know the basic sorts and their runtimes, this isn't a domain of expertise for me. So, I did my research:

I wanted a sort that didn't have heavy data structures attached to it or extreme complexity in implementation, because of my own time constraints in finishing this exercise. This led me to evaluate Quick sort and Merge sort, when targeting an average complexity of `O(n log(n))`, . 

Worst case, however, has Quick sort with `O(n^2)` versus Merge's `O(n log(n))`, so I decided to go with that. No stronger reasons. It depends highly on system architecture and data format for which algorithm is best, [as I read in this great thread](https://stackoverflow.com/questions/70402/why-is-quicksort-better-than-mergesort).

Also, one should take care with stack depth, re: recursion, on embedded systems. I would be extremely hesitant to use recursion on a critical system.

### Sources

I have been working a lot in C lately, so [I brushed up on my iterators](https://medium.com/geekculture/iterator-design-pattern-in-c-42caec84bfc), [iterator design](https://stackoverflow.com/questions/3582608/how-to-correctly-implement-custom-iterators-and-const-iterators) and also read [this great essay on auto and smart pointers](https://herbsutter.com/elements-of-modern-c-style/) in C++ 11. These are things I conceptually know, but after some years, the implementation details slip away.

I also referenced the wikipedia pages for Circular Buffers, Linked Lists, Merge Sort, and various other features as I came across them, along with having a constant tab to cppreference.com open. Again, I have high level knowledge here. But when writing the actual implementation, working with a reference is smart, rather than reinventing the wheel. 

I chose not to use templates, for debugging sanity and development velocity. They can be added in.

C++ development is difficult to do correctly, and very easy to do incorrectly. Working with language documentation and references is invaluable, imo.

### Testing

As with Solution 2, I used google test suite, which is downloaded and built automatically with CMake.

Assumptions made in testing were limiting the test scope to the defined problem. I did not implement extra features of the Linked List (remove, reverse, etc..), so these areas will not be tested.

### Heap Check

With dynamic memory, I like checking with valgrind. Please find the output below:

```
▶ valgrind ./question_3_4_5/build/linked_list_tests > /dev/null 
==82501== Memcheck, a memory error detector
==82501== Copyright (C) 2002-2024, and GNU GPL'd, by Julian Seward et al.
==82501== Using Valgrind-3.25.1 and LibVEX; rerun with -h for copyright info
==82501== Command: ./question_3_4_5/build/linked_list_tests
==82501== 
==82501== 
==82501== HEAP SUMMARY:
==82501==     in use at exit: 0 bytes in 0 blocks
==82501==   total heap usage: 684 allocs, 684 frees, 163,188 bytes allocated
==82501== 
==82501== All heap blocks were freed -- no leaks are possible
==82501== 
==82501== For lists of detected and suppressed errors, rerun with: -s
==82501== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```
