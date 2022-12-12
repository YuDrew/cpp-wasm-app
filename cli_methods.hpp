#include "merge.hpp"
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

void merge_csvs_cli()
{
    string input, file1, file2, outputfile;
    cout<<"Please enter the relative path of the first file you would like to merge"<<endl;
    cin>>input;
    if(!ifstream(input)){
        cout<<"Invalid file path; please enter a valid file path."<<endl;
        cin>>input;
    };
    file1 = input;
    cout<<"Please enter the relative path of the second file you would like to merge"<<endl;
    cin>>input;
    if(!ifstream(input)){
        cout<<"Invalid file path"<<endl;
        cin>>input;
    };
    cout<<"Please enter the relative path of the output file"<<endl;
    cin>>outputfile;
    if(ifstream(outputfile)){
        cout<<"That file already exists. Would you like to overwrite it? Y/N"<<endl;
        cin>>input;
        if(input == "N"){
            outputfile = nullptr;
        }
    }
    merge(file1, file2, outputfile);
}

void read_and_display_csv_cli()
{
    cout<<"READ AND DISPLAY CSV"<<endl;
    string filename;
    cout<<"Please enter the relative path of the file you would like to display"<<endl;
    cin>>filename;
    if(!ifstream(filename)){
        cout<<"Invalid file path. Please enter the relative path of the file you would like to display"<<endl;
        cin>>filename;
    };
    DataFrame df(filename);
    df.show();
}