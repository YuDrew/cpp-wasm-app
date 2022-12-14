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
#include "dataframe.hpp"

using namespace std;

void enrich_investors(string deals_path, string organizations_path, string outputfile)
{
    ifstream finDeals(deals_path);
    ifstream finOrganizations(organizations_path);
    ofstream fout(outputfile);
    
    DataFrame deals(finDeals);

    // Get the headers
    string header1, header2;
    getline(finDeals, header1);
    getline(finOrganizations, header2);

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
    string mergeColumn1 = Investors;
    while(mergeColumn1.empty()) {
        cout << "Please select the column you would like to merge on for the first file" << endl;
        cout << header1 << endl;
        string input;
        input = "Investors"
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

    // Get the column numbers for the merge columns
    int mergeColumn1Index = find(header1Vector.begin(), header1Vector.end(), mergeColumn1) - header1Vector.begin();
    int mergeColumn2Index = find(header2Vector.begin(), header2Vector.end(), mergeColumn2) - header2Vector.begin();

    // Get the rows
    vector<string> row1Vector;
    vector<string> row2Vector;
    vector<string> row3Vector;

    // Get the rows
    while(getline(finDeals, row1)) {
        stringstream ss(row1);
        while(getline(ss, temp, ',')) {
            row1Vector.push_back(temp);
        }
    }

    while(getline(finOrganizations, row2)) {
        stringstream ss(row2);
        while(getline(ss, temp, ',')) {
            row2Vector.push_back(temp);
        }
    }

    // Inner Join
    if(input == "1") {
        for(int i = 0; i < row1Vector.size(); i++) {
            for(int j = 0; j < row2Vector.size(); j++) {
                if(row1Vector[i] == row2Vector[j]) {
                    row3Vector.push_back(row1Vector[i]);
                }
            }
        }
    }

    // Left Outer Join 
    if(input == "2") {
        for(int i = 0; i < row1Vector.size(); i++) {
            for(int j = 0; j < row2Vector.size(); j++) {
                if(row1Vector[i] == row2Vector[j]) {
                    row3Vector.push_back(row1Vector[i]);
                }
            }
        }
    }

    // Right Outer Join
    if(input == "3") {
        for(int i = 0; i < row1Vector.size(); i++) {
            for(int j = 0; j < row2Vector.size(); j++) {
                if(row1Vector[i] == row2Vector[j]) {
                    row3Vector.push_back(row1Vector[i]);
                }
            }
        }
    }

    // Full Outer Join
    if(input == "4") {
        for(int i = 0; i < row1Vector.size(); i++) {
            for(int j = 0; j < row2Vector.size(); j++) {
                if(row1Vector[i] == row2Vector[j]) {
                    row3Vector.push_back(row1Vector[i]);
                }
            }
        }
    }

    // Write to File
    for(int i = 0; i < row3Vector.size(); i++) {
        fout << row3Vector[i] << endl;
    }
}