#ifndef VECTOR_H
#define VECTOR_H

#define Ascii_char_Size 500

#include <vector>
#include <string>
#include <iostream>

class Vector
{
public:
    Vector();

    std::vector<std::wstring> Words;
    int characterFrequency[Ascii_char_Size];
    int noOfwords;
    int checkIfSimilar; //Check if all words in list are with same no of letters but diff words
    int no_trials;

    void insert(std::wstring);
    void display();

private:
    std::wstring first_word;
    std::wstring erase(std::wstring word, wchar_t a);
    int wordEval(std::wstring word1, std::wstring word2);
};

#endif // VECTOR_H
