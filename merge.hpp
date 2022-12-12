#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <string_view>
#include <memory>
#include <type_traits>
#include <utility>

using namespace std;

void merge(string file1, string file2, string outputfile)
{
    ifstream fin1(file1);
    ifstream fin2(file2);
    ofstream fout(outputfile);
    
    string row1;
    string row2;
    string row3;

    // Get the headers
    string header1, header2;
    getline(fin1, header1);
    getline(fin2, header2);

    vector<string> header1Vector;
    vector<string> header2Vector;
    stringstream ss1(header1);
    stringstream ss2(header2);
    string temp;
    while(getline(ss1, temp, ',')) {
        header1Vector.push_back(temp);
    }
    while(getline(ss2, temp, ',')) {
        header2Vector.push_back(temp);
    }

    // Prompt User to Select Headers to Merge
    string mergeColumn1;
    while(mergeColumn1.empty()) {
        cout << "Please select the column you would like to merge on for the first file" << endl;
        cout << header1 << endl;
        string input;
        cin >> input;
        if(find(header1Vector.begin(), header1Vector.end(), input) != header1Vector.end()) {
            mergeColumn1 = input;
        }else{
            cout << "Invalid input" << endl;
        }
    }
    string mergeColumn2;
    while(mergeColumn2.empty()) {
        cout << "Please select the column you would like to merge on for the first file" << endl;
        cout << header2 << endl;
        string input;
        cin >> input;
        if(find(header2Vector.begin(), header2Vector.end(), input) != header2Vector.end()) {
            mergeColumn2 = input;
        }else{
            cout << "Invalid input" << endl;
        }
    }

    // Present Options for Merges
    cout << "Please select the type of merge you would like to perform" << endl;
    cout << "1. Inner Join" << endl;
    cout << "2. Left Outer Join" << endl;
    cout << "3. Right Outer Join" << endl;
    cout << "4. Full Outer Join" << endl;
    string input;

    // Get User Input
    while(input.empty()) {
        cin >> input;
        if(input == "1" || input == "2" || input == "3" || input == "4") {
            break;
        }else{
            cout << "Invalid input" << endl;
            input.clear();
        }
    }

    // Get the rows
    vector<string> row1Vector;
    vector<string> row2Vector;
    vector<string> row3Vector;

    // Get the rows
    while(getline(fin1, row1)) {
        stringstream ss(row1);
        while(getline(ss, temp, ',')) {
            row1Vector.push_back(temp);
        }
    }

    while(getline(fin2, row2)) {
        stringstream ss(row2);
        while(getline(ss, temp, ',')) {
            row2Vector.push_back(temp);
        }
    }

    // Inner Join
    if(input == "1") {
        for(size_t i = 0; i < row1Vector.size(); i++) {
            for(size_t j = 0; j < row2Vector.size(); j++) {
                if(row1Vector[i] == row2Vector[j]) {
                    row3Vector.push_back(row1Vector[i]);
                }
            }
        }
    }

    // Left Outer Join 
    if(input == "2") {
        for(size_t i = 0; i < row1Vector.size(); i++) {
            for(size_t j = 0; j < row2Vector.size(); j++) {
                if(row1Vector[i] == row2Vector[j]) {
                    row3Vector.push_back(row1Vector[i]);
                }
            }
        }
    }

    // Right Outer Join
    if(input == "3") {
        for(size_t i = 0; i < row1Vector.size(); i++) {
            for(size_t j = 0; j < row2Vector.size(); j++) {
                if(row1Vector[i] == row2Vector[j]) {
                    row3Vector.push_back(row1Vector[i]);
                }
            }
        }
    }

    // Full Outer Join
    if(input == "4") {
        for(size_t i = 0; i < row1Vector.size(); i++) {
            for(size_t j = 0; j < row2Vector.size(); j++) {
                if(row1Vector[i] == row2Vector[j]) {
                    row3Vector.push_back(row1Vector[i]);
                }
            }
        }
    }

    // Write to File
    for(size_t i = 0; i < row3Vector.size(); i++) {
        fout << row3Vector[i] << endl;
    }
}

