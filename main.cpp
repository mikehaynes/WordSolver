/* Takes a string of characters as input from the user
 * and outputs all english words that can be made with
 * those letters.
 *
 * Michael Haynes
 * mjhaynes@umich.edu
 *
 * main.cpp
 */

#include <iostream>
#include <string>
#include <algorithm>

#include "Dictionary.h"

using namespace std;

const string DEFAULT_FILENAME = "dictionary.dic";

void get_filename(int argc, char* argv[], string& filename, size_t& min) {

    if (argc == 1) {
        filename = DEFAULT_FILENAME;
    }
    else if (argc == 2) {
        string arg = argv[1];
        if (arg[0] - '0' >= 0 && arg[0] - '0' < 10) {
            min = stoi(arg);
        }
        else {
            filename = arg;
        }
    }
    else if (argc == 3) {
        filename = argv[1];
        string number = argv[2];
        min = stoi(number);
    }
    else {
        cerr << "Error: incorrect number of arguments" << endl;
        exit(1);
    }

}

void print_header() {
    cout << "Please input the characters that you would like to use to\n"
        << "generate a list of words containing those characters.\n"
        << "Enter \"quit\" to quit the program.\n\n"
        << "Input:  ";
}

void run_IO(Dictionary& dictionary) {
    string input = "";
    print_header();

    while (cin >> input) {
        cout << endl;
        transform(input.begin(), input.end(), input.begin(), ::tolower);

        if (input == "quit") {
            cout << "Thanks for using WordSolver!\n" << endl;
            return;
        }

        dictionary.print_words(input);
        print_header();
    }
}

int main(int argc, char* argv[]) {
    string filename;
    size_t min = 0;
    get_filename(argc, argv, filename, min);

    Dictionary dict(filename);

    if (min > 0) {
        dict.set_min_length(min);
    }

    run_IO(dict);

    return 0;
}
