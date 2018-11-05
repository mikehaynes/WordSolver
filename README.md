# WordSolver
A command line program that finds words using input letters.


# Makefile
Makefile uses GCC 6.2

Command:   make   makes the release version of WordSolver

Command:   make debug   makes a version of WordSovler for debugging

Command:   make clean   cleans out the files made by the Makefile


# Usage
./WordSolver   Uses the default dictionary

./WordSolver <positive number>   Only generates words that are at least as long as <positive number>.

./WordSolver <filename>   Uses a newline delimited dictinary contained in <filename>.

./WordSolver <filename> <positive number>   Does the same as the two above combined.


# main.cpp
The main driver for the program.  Sets up a Dictinary object and then runs the program using it.


# Dictionary.h
Contains the Dictinary class that does all of the heavy lifting for the program.

The dictionary is stored in an unordered map whose key is the alphabetical sorting of
a word.  For example, "ordered" is sorted to the key "ddeeorr".  The value of each key is
a list of all of the words that sort to that key.  For example, "last" and "salt" are
both in a list that is the value of the key "alts".

When the user inputs a string of letters, the string is passed to the dictionary.
The dictionary sorts the string and then generates all permutations of that string.
If the user inputs "dab", then the following strings a permuted:

"abd", "ab", "ad", "bd", "a", "b", "d"

Each of these permutations are checked against the dictionary's keys and if
any of them match, the key's list is added to a set that is sorted by length with
ties broken by alphabetical order.  The set is then output to standard output.

Permutation is done recursively with memoization to make it run as quickly as possible.
