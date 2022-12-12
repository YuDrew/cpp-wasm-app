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

void cli_create_csv(){
    cout<<"CREATE CSV IN COMMAND LINE"<<endl;

    string input;

    // Get the name of the output file
    cout<<"Please enter the relative path of the output file"<<endl;
    string outputfile;
    cin>>input;
    outputfile = input;
    while(ifstream(outputfile)){
        cout<<"That file already exists. Enter a different name"<<endl;
        cin>>input;
        outputfile = input;
    };
    ofstream fout(outputfile);

    // Get the number of columns
    cout<<"Please enter the number of columns"<<endl;
    int numColumns;
    cin>>input;
    while(!isdigit(input[0])){
        cout<<"Please enter a valid number of columns"<<endl;
        cin>>input;
    }
    numColumns = stoi(input);

    // Get the names of the columns
    vector<string> columnNames;

    for(int i=0; i<numColumns; i++){
        cout<<"Please enter the name of column "<<i+1<<endl;
        string columnName;
        cin>>columnName;
        columnNames.push_back(columnName);
    }

    // Get the number of rows
    cout<<"Please enter the number of rows"<<endl;
    int numRows;
    cin>>input;
    while(!isdigit(input[0])){
        cout<<"Please enter a valid number of rows"<<endl;
        cin>>input;
    }
    numRows = stoi(input);

    // Get the values for each row
    vector<vector<string>> rows;
    for(int i=0; i<numRows; i++){
        vector<string> row;
        for(int j=0; j<numColumns; j++){
            cout<<"Please enter the value for row "<<i+1<<" and column "<<columnNames[j]<<endl;
            string value;
            cin>>value;
            row.push_back(value);
        }
        rows.push_back(row);
    }

    // Create the DataFrame
    DataFrame df(columnNames, rows);
    df.to_csv(outputfile);
}

void merge_csvs_cli()
{
    string input, file1, file2, outputfile;

    // Get the names of the files to merge
    cout<<"Please enter the relative path of the first file you would like to merge"<<endl;
    cin>>input;
    if(!ifstream(input)){
        cout<<"Invalid file path; please enter a valid file path."<<endl;
        cin>>input;
    };
    file1 = input;

    DataFrame df1(file1);
    df1.show();

    cout<<"Please enter the relative path of the second file you would like to merge"<<endl;
    cin>>input;
    if(!ifstream(input)){
        cout<<"Invalid file path"<<endl;
        cin>>input;
    };
    file2 = input;

    DataFrame df2(file2);
    df2.show();

    // Confirm that the user wants to merge the files
    cout<<"Would you like to merge these files? Y/N"<<endl;
    cin>>input;
    while(input != "N" && input != "Y"){
        cout<<"Please enter Y or N"<<endl;
        cin>>input;
    }
    if(input == "N"){
        return;
    }

    // Get the columns to merge on
    cout<<"Please enter the name of the column to merge on for the first file"<<endl;
    cin>>input;
    while(!df1.has_column(input)){
        cout<<"That column does not exist. Please enter the name of the column to merge on for the first file"<<endl;
        cin>>input;
    }
    string column1 = input;

    cout<<"Please enter the name of the column to merge on for the second file"<<endl;
    cin>>input;
    while(!df2.has_column(input)){
        cout<<"That column does not exist. Please enter the name of the column to merge on for the second file"<<endl;
        cin>>input;
    }
    string column2 = input;

    // Get the name of the output file
    cout<<"Please enter the relative path of the output file"<<endl;
    cin>>outputfile;
    if(ifstream(outputfile)){
        cout<<"That file already exists. Would you like to overwrite it? Y/N"<<endl;
        cin>>input;
        if(input == "N"){
            outputfile = nullptr;
        }
    }

    // Merge the files
    DataFrame mergedDf = df1.inner_join(df2, column1, column2);
    mergedDf.show();

    // Confirm that the user wants to save the merged file
    cout<<"Would you like to save this file? Y/N"<<endl;
    cin>>input;
    while(input != "N" && input != "Y"){
        cout<<"Please enter Y or N"<<endl;
        cin>>input;
    }
    if(input == "N"){
        return;
    }

    // Save the merged file
    mergedDf.to_csv(outputfile);
}

void read_and_display_csv_cli()
{
    string filename;
    cout<<"READ AND DISPLAY CSV"<<endl;

    // Get the name of the file to display
    cout<<"Please enter the relative path of the file you would like to display"<<endl;
    cin>>filename;
    if(!ifstream(filename)){
        cout<<"Invalid file path. Please enter the relative path of the file you would like to display"<<endl;
        cin>>filename;
    };

    // Create the DataFrame and display it
    DataFrame df(filename);
    df.show();
}

void filter_csv_cli()
{
    string filename, outputfile, input;
    cout<<"FILTER CSV"<<endl;

    // Get the name of the file to filter
    cout<<"Please enter the relative path of the file you would like to filter"<<endl;
    cin>>filename;
    if(!ifstream(filename)){
        cout<<"Invalid file path. Please enter the relative path of the file you would like to filter"<<endl;
        cin>>filename;
    };

    // Preview the DataFrame
    DataFrame df(filename);
    df.show();

    // Get the column to filter by
    cout<<"Please enter the name of the column you would like to filter by"<<endl;
    string column;
    cin>>column;
    while (!df.has_column(column)){
        cout<<"That column does not exist. Please enter the name of the column you would like to filter by"<<endl;
        cin>>column;
    }

    // Get the value to filter by
    cout<<"Please enter the value you would like to filter by"<<endl;
    string value;
    cin>>value;

    // Filter the DataFrame and display it
    DataFrame filteredDf = df.filter(column, value);
    filteredDf.show();

    // Confirm that the user wants to save the filtered DataFrame
    cout<<"Would you like to save the filtered DataFrame? Y/N"<<endl;
    cin>>input;
    while(input != "N" && input != "Y"){
        cout<<"Please enter Y or N"<<endl;
        cin>>input;
    }
    if(input == "N"){
        return;
    }

    // Get the name of the output file
    cout<<"Please enter the relative path of the output file"<<endl;
    cin>>outputfile;
    if(ifstream(outputfile)){
        cout<<"That file already exists. Would you like to overwrite it? Y/N"<<endl;
        cin>>input;
        if(input == "N"){
            outputfile = nullptr;
        }
    }

    // Save the filtered DataFrame
    filteredDf.to_csv(outputfile);
}

void sort_csv_cli(){
    cout<<"SORT CSV"<<endl;
    string filename, outputfile, input;

    // Get the name of the file to sort
    cout<<"Please enter the relative path of the file you would like to sort"<<endl;
    cin>>filename;
    if(!ifstream(filename)){
        cout<<"Invalid file path. Please enter the relative path of the file you would like to sort"<<endl;
        cin>>filename;
    };

    // Preview the DataFrame
    DataFrame df(filename);
    df.show();

    // Get the column to sort by
    cout<<"Please enter the name of the column you would like to sort by"<<endl;
    string column;
    cin>>column;
    while (!df.has_column(column)){
        cout<<"That column does not exist. Please enter the name of the column you would like to sort by"<<endl;
        cin>>column;
    }

    // determine ascending or descending
    bool ascending = true;
    cout<<"Would you like to sort in ascending or descending order? A/D"<<endl;
    cin>>input;
    while(input != "A" && input != "D"){
        cout<<"Please enter A or D"<<endl;
        cin>>input;
    }
    if(input == "D"){
        ascending = false;
    }

    // Sort the DataFrame and display it
    df.sort_in_place(column, ascending);
    df.show();

    // Confirm that the user wants to save the sorted DataFrame
    cout<<"Would you like to save the sorted DataFrame? Y/N"<<endl;
    cin>>input;
    while(input != "N" && input != "Y"){
        cout<<"Please enter Y or N"<<endl;
        cin>>input;
    }
    if(input == "N"){
        return;
    }

    // Get the name of the output file
    cout<<"Please enter the relative path of the output file"<<endl;
    cin>>outputfile;
    if(ifstream(outputfile)){
        cout<<"That file already exists. Would you like to overwrite it? Y/N"<<endl;
        cin>>input;
        if(input == "N"){
            outputfile = nullptr;
        }
    }

    // Save the sorted DataFrame
    df.to_csv(outputfile);
}