#include <iostream>
#include <string.h>
#include <fstream>

extern "C" int find(char s1[], char s2[]);

int main(int argc, char* argv[]){
    std::string s1, s2;

    if(argv[1]==NULL){
    	std::cout<<"Input File as an Argument..."<<std::endl;
    	return -1;
    }

    std::ifstream inData;
    inData.open(argv[1], std::ios::in);

    std::string line;
    getline(inData, line);
    s1=line;

    int n1 = s1.length(); 
    char str[n1+1]; 
    strcpy(str, s1.c_str());
    while(1){
        getline(inData, line);
        s2=line;

        if(s2==""){break;}

        std::cout<<"String: "<<s1<<std::endl;
        std::cout<<"Substring: "<<s2<<std::endl;

        int n2 = s2.length(); 
        char substr[n2+1]; 
        strcpy(substr, s2.c_str());

        int index=find(str, substr);

        if(index==-1){
            std::cout<<"Info: Not Found"<<std::endl;
        }
        else{
            std::cout<<"Info: Its index is "<<index<<std::endl;
        }
        std::cout<<std::endl;

    }

    inData.close();
	return 0;
}