#include <iostream>
#include <vector>
#include "merge.hpp"
#include "create_csv.hpp"

using namespace std;

int main()
{
    bool sessionEnd = false;
    string input;
    vector<string> inputVector = {};
    vector<string> fileVector = {};
    while(!sessionEnd){
        cout<<"Welcome to the CSV Manipulator"<<endl;
        cout<<"What would you like to do today?"<<endl;
        cout<<"Menu:\n"
            "1. Merge CSVs\n"
            "2. Filter CSVs\n"
            "3. Sort CSVs\n"
            "4. Output your current directory\n"
            "5. Create a CSV in the command line\n"
            "6. Exit\n"
            "7. Repeat menu list of commands\n"
        <<endl;
        cin>>input;
        inputVector.push_back(input);
        switch(stoi(input)) {
            case 1: // Merge CSVs
                cout<<"MERGE CSVs"<<endl;
                cout<<"Please enter the relative path of the first file you would like to merge"<<endl;
                cin>>input;
                inputVector.push_back(input);
                if(!ifstream(input)){
                    cout<<"Invalid file path"<<endl;
                    break;
                };
                fileVector.push_back(input);
                cout<<"Please enter the relative path of the second file you would like to merge"<<endl;
                cin>>input;
                inputVector.push_back(input);
                if(!ifstream(input)){
                    cout<<"Invalid file path"<<endl;
                    break;
                };
                fileVector.push_back(input);
                cout<<"Please enter the relative path of the output file"<<endl;
                cin>>input;
                inputVector.push_back(input);
                if(ifstream(input)){
                    cout<<"That file already exists."<<endl;
                    break;
                };
                merge(fileVector[fileVector.size()-2], fileVector[fileVector.size()-1], inputVector[inputVector.size()-1]);
                break;
            case 2: // Filter CSVs
                cout<<"FILTER CSVs"<<endl;
                cout<<"Please enter the relative path of the file you would like to filter"<<endl;
                cin>>input;
                inputVector.push_back(input);
                if(!ifstream(input)){
                    cout<<"Invalid file path"<<endl;
                    break;
                };
                fileVector.push_back(input);
                cout<<"Please enter the relative path of the output file"<<endl;
                cin>>input;
                inputVector.push_back(input);
                if(ifstream(input)){
                    cout<<"That file already exists."<<endl;
                    break;
                };
                break;
            case 3: // Sort CSVs
                cout<<"SORT CSVs"<<endl;
                cout<<"Please enter the relative path of the file you would like to sort"<<endl;
                cin>>input;
                inputVector.push_back(input);
                if(!ifstream(input)){
                    cout<<"Invalid file path"<<endl;
                    break;
                };
                fileVector.push_back(input);
                cout<<"Please enter the relative path of the output file"<<endl;
                cin>>input;
                inputVector.push_back(input);
                if(ifstream(input)){
                    cout<<"That file already exists."<<endl;
                    break;
                };
                break;
            case 4: // Output current directory
                cout<<"OUTPUT CURRENT DIRECTORY"<<endl;
                system("ls");
                break;
            case 5: // Create CSV in command line
                cout<<"CREATE CSV IN COMMAND LINE"<<endl;
                cli_create_csv();
                break;
            case 6: // Exit
                cout<<"EXIT"<<endl;
                sessionEnd = true;
                break;
            case 7: // Repeat menu list of commands
                cout<<"REPEAT MENU LIST OF COMMANDS"<<endl;
                break;
            default:
                cout<<"Invalid Input"<<endl;
                break;
        } // end switch
    } // end while
    return 0;
} // end main