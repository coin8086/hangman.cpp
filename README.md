# hangman.cpp
Hangman in C++

## NOTE
The project is one of a series of projects implementing the same algorithm for the [Hangman game](https://en.wikipedia.org/wiki/Hangman_(game)) in different programming languages. The purpose is to learn and show the common and difference of these languages in a practical way.

## Rerequisite

1. Download/Clone Git repo https://github.com/coin8086/hangman.resource to a local dir, say ~/hangman.resource
2. Link it to res under the project root dir like `ln -s ~/hangman.resource res`

## Build

Run `build` under project root. A C++11 compatible compiler is required. See [here](http://en.cppreference.com/w/cpp/compiler_support) for a list of supported compilers.

To check what C++ features are used in the code, search for "NOTE: C++11" in code. For example, in Bash you can(under the project root):

```
grep "NOTE: C++11" -I -A 1 -r .
```

or use `git grep` with or without Bash:

```
git grep -A 1 -I "NOTE: C++11"
```

## Play, Sample and Benchmark

The `play`, `sample` and `benchmark` scripts are what you need. Run them under the project root.
