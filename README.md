# Advent of Code 2024

Solutions in C++ for [Advent of Code 2024](https://adventofcode.com/2024), one folder per day (`dN/`).
Each day has `part1.cpp` and `part2.cpp`, plus the puzzle input and sample input.

## Build and run

```bash
cd d14
g++ -O2 -std=c++17 -o part1 part1.cpp
./part1 < p1input.txt
```

Compiled binaries are git-ignored. Check each source file for how it reads its input
(stdin or a hard-coded filename), since the solutions were written quickly.
