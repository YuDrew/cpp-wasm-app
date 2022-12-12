#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <string_view>
#include <memory>
#include <type_traits>
#include <utility>
#include <chrono>
#include <thread>
#include <future>
#include <mutex>
#include "dataframe.hpp"

using namespace std;

void cli_create_csv(){
    cout<<"Please enter the relative path of the output file"<<endl;
    string outputfile;
    cin>>outputfile;
    while(ifstream(outputfile)){
        cout<<"That file already exists. Enter a different name"<<endl;
        cin>>outputfile;
    };
    ofstream fout(outputfile);

    cout<<"Please enter the number of columns"<<endl;
    int numColumns;
    cin>>numColumns;
    vector<string> columnNames;

    for(int i=0; i<numColumns; i++){
        cout<<"Please enter the name of column "<<i+1<<endl;
        string columnName;
        cin>>columnName;
        columnNames.push_back(columnName);
    }
    cout<<"Please enter the number of rows"<<endl;
    int numRows;
    cin>>numRows;
    vector<vector<string>> rows;
    for(int i=0; i<numRows; i++){
        vector<string> row;
        for(int j=0; j<numColumns; j++){
            cout<<"Please enter the value for row "<<i+1<<" and column "<<j+1<<endl;
            string value;
            cin>>value;
            row.push_back(value);
        }
        rows.push_back(row);
    }
    DataFrame df(columnNames, rows);
    df.to_csv(outputfile);
}