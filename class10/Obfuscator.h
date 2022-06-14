#ifndef CLASS10_OBFUSCATOR_H
#define CLASS10_OBFUSCATOR_H
#include "iostream"
#include "vector"
using namespace std;

class Obfuscator {
public:
    const string OUT = "newCode.c";
    virtual void obfuscate(string fileName) = 0;
    string generateRandomVar();
    string* parseFile(string filename);
    void writeToFile(string* codeArray);
//a private methods for me.
protected:
    int validChar(char c);
    string cutVariable(string line);
};
class LineObfuscator : public Obfuscator{
public:
    LineObfuscator(){

    }
    void obfuscate(string fileName);
};
class VarObfuscator : public Obfuscator{
public:
    VarObfuscator(){

    }
    void obfuscate(string fileName);
};
class CommentObfuscator : public Obfuscator{
public:
    //defining a string vector to put many random comments.
    vector<string> comments;
    CommentObfuscator(){
        comments.push_back("//check if the number is prime.");
        comments.push_back("//defining a new double array.");
        comments.push_back("//print the list.");
        comments.push_back("//check the corner cases.");
        comments.push_back("//Up Casting.");
        comments.push_back("//initializing a new class object.");
    }
    void obfuscate(string fileName);
};

#endif //CLASS10_OBFUSCATOR_H
