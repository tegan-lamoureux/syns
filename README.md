# Documentation and Build guide

Please find each question's solution in the relevant folder, along with documentation, in the respective README.md file.

All questions can be built and tested on any platform with CMake, which will automatically pull down and build the google test framework.

## Build Environment Setup

### Linux / WSL Requirements (Tested on Arch Linux)

CMake, git, build tools.

* Arch Linux: `sudo pacman -S cmake git base-devel`
* WSL/Ubuntu: `sudo apt-get install cmake git build-essential` 
  
### Windows Native Requirements (Tested on Windows 10)

* [cmake](https://cmake.org/download/)
* [git](https://git-scm.com/install/windows) (for cloning)
* [VS Community 2026](https://visualstudio.microsoft.com/vs/community/) (C++ features installed).

### Mac (Not tested)

Should be identical to Linux/WSL. Requirements can be installed with [brew](https://brew.sh/).

## Building & Running Tests (All Platforms)

From a linux terminal, or Windows Powershell, in the solutions directory (alongside CMakeLists.txt):

1. Initialize cmake: `cmake -S . -B build`
2. Build the tests: `cmake --build build`
3. Run the tests: `ctest --test-dir build`
