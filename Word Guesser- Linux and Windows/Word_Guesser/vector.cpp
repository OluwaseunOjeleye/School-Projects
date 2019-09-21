#include "vector.h"

Vector::Vector()
{
    this->noOfwords=0;
    this->no_trials=0;
    this->first_word=L"";
    this->checkIfSimilar=0;

    for(int i=0; i<Ascii_char_Size; i++){
        this->characterFrequency[i]=0;
    }
}

void Vector::insert(std::wstring word){

    for(int i=0; i<word.length(); i++){
        characterFrequency[word[i]]++;
    }

    Words.resize(noOfwords+1);
    Words[noOfwords]=word;

    if(noOfwords==0){
        this->first_word=word;
    }
    else{
        if(checkIfSimilar==0){
            checkIfSimilar=wordEval(first_word, word);
        }
    }
    //std::wcout<<first_word<<" "<<word<<"--"<<checkIfSimilar<<std::endl;
    this->noOfwords++;
}

//Displaying Trie
void Vector::display(){
    for(int i=0; i<this->noOfwords; i++){
        std::wcout<<this->Words[i]<<std::endl;
    }
}


std::wstring Vector::erase(std::wstring word, wchar_t a){
    std::wstring result=L""; int c=0;
    for(int i=0; i<word.length(); i++){
        if(word[i]==a && c==0){
            c++;
        }
        else{
            result+=word[i];
        }
    }
    return result;
}

int Vector::wordEval(std::wstring word1, std::wstring word2){
    std::wstring w1=word1, w2=word2;
    for(int i=0; i<w1.length(); i++){
        for(int j=0; j<w2.length(); j++){
            if(w1[i]==w2[j]){
                w2=erase(w2, w1[i]);
                break;
            }
        }
    }
    return w2.length();
}
