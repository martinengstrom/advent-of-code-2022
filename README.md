# advent-of-code-2022
My first take at Advent of Code, Completion not guaranteed.

## How to build
All of the solutions are written in C++ or in some rare cases C.
Only the standard library is used except for some auxiliary classes which are included in each source folder.

> g++ main.cpp

Is usually enough. Add other cpp files if they are present in the source directory.  
I use features from c++11 or even c++17 and c++0x. If you get any compilation errors, make sure its using a modern C++ standard but the default g++ has worked for me.

## How to run
I dont expect anyone to ever download and run these source files, Im just putting them here so theres some activity on my otherwise pitful github account. However in the rare case that you do and its not immediately obvious from the sources, pipe the example or input (downloadable from adventofcode.com) into the executable

> g++ -o solution main.cpp  
> cat input | ./solution
