#include <iostream>
#include <vector>
#include <string>
#include "cli_methods.hpp"

using namespace std;

int main()
{
    bool sessionEnd = false;
    string input;
    vector<string> inputVector = {};
    vector<string> fileVector = {};
    system("clear");
    while(!sessionEnd){
        cout<<"Welcome to the CSV Manipulator"<<endl;
        cout<<"What would you like to do today?"<<endl;
        cout<<"Menu:\n"
            "0. Exit\n"
            "1. Display a CSV\n"
            "2. Filter a CSV\n"
            "3. Sort a CSV\n"
            "4. Create a CSV in the command line\n"
            "5. Merge two CSVs\n"
            "6. Enrich Affinity Investor Ecosystem Data\n"
        <<endl;
        cin>>input;
        inputVector.push_back(input);
        switch(stoi(input)) {
            case 0: // Exit
                cout<<"EXIT"<<endl;
                sessionEnd = true;
                break;
            case 1: // Display CSV
                read_and_display_csv_cli();
                break;
            case 2: // Filter CSVs
                filter_csv_cli();
                break;
            case 3: // Sort CSVs
                cout<<"SORT CSVs"<<endl;
                cout<<"This feature is not yet implemented."<<endl;
                break;
            case 4: // Create CSV in command line
                cout<<"CREATE CSV IN COMMAND LINE"<<endl;
                cli_create_csv();
                break;
            case 5: // Merge two CSVs
                merge_csvs_cli();
                break;
            case 6: // Enrich Affinity Investor Ecosystem Data
                cout<<"ENRICH AFFINITY INVESTOR ECOSYSTEM DATA"<<endl;
                cout<<"This feature is not yet implemented."<<endl;
                break;
            default:
                cout<<"Invalid Input"<<endl;
                break;
        } // end switch
        if (sessionEnd) break;
        cout<<"\n\nPress any key to continue..."<<endl;
        cin.ignore();
        cin.get();
        system("clear");
    } // end while
    return 0;
} // end main