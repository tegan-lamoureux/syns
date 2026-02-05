# Prompt review:

A bit too ambiguous for my comfort. Some questions:

- Should an ERROR state prevent a transition from IDLE to RUNNING in start()? 
- There is no defined transition from RUNNING to IDLE. Only ERROR to IDLE. 
	- Does reset() handle this as well, or do we need an idle() method for safely "powering down" and going back to IDLE from a non-error state?
- How to handle overflow/negative values on `time`? 
	- They want an integer, not an unsigned integer?
	- What is our Y2K / Unix 2038 equivalent rollover strategy?
- Are we just increasing time by 1 every call? Is it tied to state change ticks? 
- Do we need atomics here? Thread safety?


# Code Review (Mock-PR Reply):

This is a great start! However, there are few immediate issues I see that we 
should address, and some stylistic advice. 

### Critical Items:

- `time` is uninitialized. There are some special cases in c++ where the memory 
is zero-initialized automatically (static scope, for instance), but this is 
not default behavior and it should be explicitly set to zero. Otherwise it will
hold  random data leftover in memory, and have a garbage value at the start.
	- Since you already have an initalizer list in the constructor's definition, adding it there would be a good idea:
	- `Device() : state(IDLE), time(0) {}`

- incrementTime() has no defined return type. Old C standards allow this and 
implicitly convert the type to int, but this is not allowed in C++, and in 
either case, it should be void, as nothing is returned:
	- `void incrementTime() {...}`

### Stylistic advice:

- `getTime()` should be made const, like `getState()`, as it does not modify anything.

- With C++, it can be better to use enum classes (scoped enumeration) instead of the C-style enums. This prevents automatic conversion to integer, and has some nice type-safety built in. If keeping the c-style enum, I personally like to give each an  explicit integer value, to prevent silent integer comparison bugs in the future if the definition order changes. 
	- Ex: a new enum is added into the middle of the list: BUSY. Now ERROR, which was previously "impicitly" == 2, evaluates to 3.
	- If switching to enum classes: `enum class DeviceState {`, and you'll need to scope the enum value when used, eg: `state = DeviceState::IDLE`


### Conclusion:

For the future: a great first-step testing strategy is just to compile the code and 
run it while observing behavior. (How I performed this review.)

Let me know if you have any questions, and I'm happy to help with anything further.
