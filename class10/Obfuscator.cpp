#include "Obfuscator.h"
#include <fstream>
#include <iostream>
#include "vector"
using namespace std;
//global variable for me to save the number of the lines in the file.
int linesNum = 0;
//method returns a random variable.
string Obfuscator :: generateRandomVar(){
    string res = "";
    //random length 3-10 characters.
    int len = (rand()%10) + 3;
    int chance = rand()%3;
    for(int i = 0; i < len; i++){
        switch (chance) {
            case 0:
                //underscore char.
                res += '_';
                break;
            case 1:
                //small litters.
                res += 'a' + (rand()%25);
                break;
            case 2:
                //capital litters.
                res += 'A' + (rand()%25);
                break;
            case 3:
                //numbers.
                res += '1' + (rand()%9);
                break;
        }
        chance = rand()%4;
    }
    return res;
}
//method that read from file and put the lines in a dynamic string array.
string* Obfuscator :: parseFile(string filename){
    string line;
    ifstream myfile (filename);
    linesNum = 0;
    //counting the lines number..
    while(getline(myfile,line))
        linesNum++;
    string *res = new string[linesNum];
    myfile.close();
    myfile.open(filename);
    //reading from file and copy to the array.
    if (myfile.is_open())
    {
        int i = 0;
        while ( getline (myfile,line) )
        {
            if(line.compare(""))
              res[i] = line;
            i++;
        }
        myfile.close();
        return res;
    }
    else cout << "Unable to open file"; return NULL;
}
void Obfuscator :: writeToFile(string* codeArray){
    ofstream newCode;
    //opening the new file.
    newCode.open(OUT);
    if(!newCode.is_open()) {
        cout << "Unable to open the new file";
        return;
    }
    //writing the array to the file.
    int i = 0;
    while (i < linesNum){
        if(codeArray[i].compare(""))
            newCode<<codeArray[i]<<endl;
        i++;
    }
    newCode.close();
}
//class method adds a new random variable and sum of two random integers.
void LineObfuscator :: obfuscate(string fileName){
    //get the array.
    string *lines = Obfuscator ::parseFile(fileName);
    int i = 0;
    int start = 0;
    //get a random name.
    string strangeVar = Obfuscator::generateRandomVar();
    //defining a new int after the main() line.
    while(i < linesNum){
        if(lines[i].find("main()") != string::npos){
            lines[i] += "\n   int " + strangeVar + ';';
            start = i;
            break;
        }
        i++;
    }
    //adding the sum of two random integers.
    int randLine = start + rand()%(linesNum-start);
    int randNum1 = 100 + rand()%10000;
    int randNum2 = 100 + rand()%10000;
    lines[randLine] += "\n   " + strangeVar + " = " + to_string(randNum1) + " + " + to_string(randNum2) + ';';
    Obfuscator::writeToFile(lines);
}
//private method that check if a char is valid to c variable.
int Obfuscator ::validChar(char c) {
    if((c >= 'a' && c <= 'z')||(c >= 'A' && c <= 'Z')||(c >= '0' && c <= '9')|| c == '_')
        return 1;
    if(c == '[' || c == ']')
        return 2;
    return 0;
}
//private method to cut and return the name of the variable.
string Obfuscator :: cutVariable(string line) {
    string var = "";
    for(int i = 0; i < line.length(); i++){
        if(validChar(line.at(i)) == 0){
            var = line.substr(0,i);
            break;
        }
        if(validChar(line.at(i)) == 2){
            return "";
        }
    }
    return var;
}
//class method that chose one of the int variables and change it to a random name.
void VarObfuscator :: obfuscate(string fileName){
    //string vector to put all the variables.
    vector<string> vars;
    //get the array.
    string *lines = Obfuscator ::parseFile(fileName);
    int i = 0;
    int begin,end;
    string tmp, var;
    cout<<linesNum;
    //passing on the lines and collect the variables.
    while(i < linesNum) {
        if (lines[i].find(" int ") != string::npos) {
            begin = lines[i].find(" int ");
            tmp = lines[i].substr(begin+5);
            var = cutVariable(tmp);
            if(var != "")
              vars.push_back(var);
        }
        i++;
    }
    //chose a random variable to change.
    string randVar = vars[rand()%vars.size()];
    string strangeVar = Obfuscator :: generateRandomVar();
    i = 0;
    //passing on the lines and change all the places that include that name.
    while(i < linesNum){
        if (lines[i].find(randVar) != string::npos) {
            begin = lines[i].find(randVar);
            end = randVar.length();
            lines[i].replace(begin,end,strangeVar);
        }
        i++;
    }
    Obfuscator::writeToFile(lines);
}
//class method that delete all the comments from the code and put a random comments.
void CommentObfuscator :: obfuscate(string fileName){
    //get the array.
    string *lines = Obfuscator ::parseFile(fileName);
    int i = 0;
    //pass on the lines and delete the comments.
    while(i < linesNum){
        if (lines[i].find("//") != string::npos) {
            lines[i].replace(lines[i].find("//"),lines[i].length(),"");
        }
        i++;
    }
    //put a new random comments at random places.
    int randPlace =rand()%(linesNum-2);
    int begin = 0, randCom;
    i = 0;
    while(i < comments.size()){
        randCom = rand()%comments.size();
        lines[randPlace] += "\n" + comments[randCom];
        //comments.erase(comments.begin()+randCom);
        begin = randPlace;
        randPlace =rand()%(linesNum);
        i++;
    }
    Obfuscator::writeToFile(lines);
}