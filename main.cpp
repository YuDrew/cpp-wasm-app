// create a basic hello world file

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    cout << "Hello World!" << endl;

    ifstream myfile;
    myfile.open("uploads/deals.csv");
    string line;
    while (getline(myfile, line))
    {
        cout << line << endl;
    }

    return 0;
}

// create a function that takes in a user uploaded file and returns the file name

string getFileName(string fileName)
{
    return fileName;
}

// create a function that takes in a user uploaded file and returns the file size

int getFileSize(string fileName)
{
    return 0;
}

// create a function that opens "uploads/deals.csv" and prints the first 5 lines

void printFirstFiveLines(string fileName)
{
    return;
}