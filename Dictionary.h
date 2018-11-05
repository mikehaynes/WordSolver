/* A class that loads and stores the specified
 * dictionary file.
 *
 * Michael Haynes
 * mjhaynes@umich.edu
 *
 * Dictionary.h
 */

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <set>

class Dictionary {
public:
    
    Dictionary() {
        std::cerr << "Error: Dictionary class requires either the file name\n"
                  << "of a dictionary or a vector of strings as input to\n"
                  << "its constructor" << std::endl;
        exit(1);
    }

    Dictionary(const std::string& filename) {
        std::ifstream infile(filename);

        if (infile.fail()) {
            std::cerr << "Error in opening file " << filename << std::endl;
            exit(1);
        }

        print_load_statement();

        std::string word;
        longest = 0;

        while (infile >> word) {
            std::transform(word.begin(), word.end(), word.begin(), ::tolower);
            std::string key;
            sorter(word, key);
            longest = (word.size() > longest) ? word.size() : longest;
            dictionary[key].push_back(word);
        }

        longest *= 2;
        infile.close();
        set_min_length();
        print_loaded_statement();
    }

    Dictionary(const std::vector<std::string>& input_dictionary) {
        print_load_statement();
        longest = 0;

        for (int i = 0; i < (int)input_dictionary.size(); ++i) {
            std::string word;
            word.resize(input_dictionary[i].size());
            std::string key;
            std::transform(input_dictionary[i].begin(),
                           input_dictionary[i].end(),
                           word.begin(), ::tolower);
            sorter(word, key);
            longest = (word.size() > longest) ? word.size() : longest;
            dictionary[key].push_back(input_dictionary[i]);
        }

        longest *= 2;
        set_min_length();
        print_loaded_statement();
    }

    Dictionary(const std::list<std::string>& input_dictionary) {
        print_load_statement();
        longest = 0;

        for (auto iter = input_dictionary.begin();
             iter != input_dictionary.end(); ++iter) {
            std::string word;
            word.resize(iter->size());
            std::string key;
            std::transform(iter->begin(), iter->end(),
                           word.begin(), ::tolower);
            sorter(word, key);
            longest = (word.size() > longest) ? word.size() : longest;
            dictionary[key].push_back(*iter);
        }

        longest *= 2;
        set_min_length();
        print_loaded_statement();
    }

    void print_words(const std::string& input) {

        if (input.size() >= longest) {
            std::cout << "Try a shorter input.\n" << std::endl;
            return;
        }
        std::string s_input = input;  // s_input = sorted_input
        std::sort(s_input.begin(), s_input.end());

        std::set<std::string, SizeSorter> words;
        std::unordered_set<std::string> used;

        permute(s_input, used, words);

        if (words.empty()) {
            std::cout << "No words found.\n" << std::endl;
            return;
        }

        for (auto iter = words.begin(); iter != words.end(); ++iter) {
            std::cout << *iter << std::endl;
        }

        std::cout << std::endl;
    }

    void set_min_length(size_t min = 0) {
        this->min = min;
    }

private:

    /* The key is the word with its characters sorted, the value
       is a list of the words in their unscrambled form */
    std::unordered_map<std::string, std::list<std::string>> dictionary;

    size_t longest;
    size_t min;


    class SizeSorter {
    public:
        bool operator() (const std::string& str1, const std::string& str2) const {
            if (str1.size() == str2.size()) {
                return str1 < str2;
            }
            return str1.size() > str2.size();
        }
    };


    void sorter(const std::string& original, std::string& sorted) const {
        sorted = original;
        std::sort(sorted.begin(), sorted.end());
    }

    void permute(const std::string& word, std::unordered_set<std::string>& used,
                 std::set<std::string, SizeSorter>& word_set) {

        if (used.find(word) != used.end() || word.size() < min || word.empty()) {
            return;
        }

        used.insert(word);
        
        auto iter = dictionary.find(word);

        if (iter != dictionary.end()) {
            std::list<std::string>& ref = iter->second;

            for (auto i = ref.begin(); i != ref.end(); ++i) {
                word_set.insert(*i);
            }

        }

        char prev = '\0';

        for (int i = 0; i < (int)word.size(); ++i) {
            std::string new_word = "";

            if (word[i] != prev) {

                for (int j = 0; j < (int)word.size(); ++j) {
                    if (j != i) {
                        new_word += word[j];
                    }
                }

                permute(new_word, used, word_set);
            }

            prev = word[i];
        }

        return;
    }

    void print_load_statement() const {
        std::cout << "Loading dictionary..." << std::endl;
    }

    void print_loaded_statement() const {
        std::cout << "Dictionary loaded!\n" << std::endl;
    }
};

#endif
