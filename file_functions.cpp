#include <emscripten.h>
#include <emscripten/bind.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string changeFileName(string fileName)
{
    return fileName + "_changed.csv";
}

int getNumLines(string fileName)
{
    ifstream myfile;
    myfile.open(fileName);
    string line;
    int i = 0;
    while (getline(myfile, line))
    {
        i++;
    }
    return i;
}

EMSCRIPTEN_BINDINGS(file_functions) {
    emscripten::function("changeFileName", &changeFileName);
    emscripten::function("getNumLines", &getNumLines);
}