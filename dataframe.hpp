#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
class DataFrame
{
public:
    // Constructor
    DataFrame() {}

    // Constructor that takes a vector of column names and a vector of rows
    DataFrame(std::vector<std::string> column_names, std::vector<std::vector<std::string>> rows)
    {
        // Add the columns to the DataFrame
        for (size_t i = 0; i < column_names.size(); i++)
        {
            // Create a vector to store the column data
            std::vector<std::string> column_data;

            // Add the column data to the vector
            for (size_t j = 0; j < rows.size(); j++)
            {
                column_data.push_back(rows[j][i]);
            }

            // Add the column to the DataFrame
            add_column(column_names[i], column_data);
        }
    }

    // Constructor that takes a CSV file
    DataFrame(std::string filename)
    {
        // Open the file
        ifstream file(filename);

        // Create a string to hold each line
        std::string line;

        // Create a vector to hold the column names
        std::vector<std::string> column_names;

        // Create a vector to hold the rows
        std::vector<std::vector<std::string>> rows;

        // Read the file line by line

        // Read the first line and store the column names
        
        getline(file, line);
        std::stringstream ss(line);
        std::string column_name;
        while (getline(ss, column_name, ','))
        {
            column_names.push_back(column_name);
        }

        // Read the rest of the lines and store the rows
        while (getline(file, line))
        {
            // Create a vector to hold the row data
            std::vector<std::string> row_data;

            // Create a string stream from the line
            std::stringstream ss(line);

            // Create a string to hold each value
            std::string value;

            // Read the line and store the values
            while (getline(ss, value, ','))
            {
                row_data.push_back(value);
            }

            // Add the row to the vector of rows
            rows.push_back(row_data);
        }

        // Create the DataFrame
        *this = DataFrame(column_names, rows);

        // Close the file
        file.close();
    }

    // Adds a column with a given name and data to the DataFrame
    void add_column(std::string column_name, std::vector<std::string> column_data)
    {
        // Store the column data in the columns map, using the column name as the key
        columns[column_name] = column_data;
    }

    // Prints the DataFrame to the console or a file
    void print(ostream &out = std::cout)
    {
        // If the output is the console, enforce display width of characters per column
        bool isCout = &out == &std::cout;
        long unsigned int displayWidth = isCout ? maxDisplayWidth : string::npos;

        // Print the column names
        for (const auto &column : columns)
        {
            out << column.first.substr(0, displayWidth);
            if (isCout && column.first.length() < displayWidth)
            {
                out << std::string(displayWidth - column.first.length(), ' ');
            }
            if (column.first != columns.rbegin()->first)
            {
                if (isCout) {
                    out << "\t|";
                } else {
                    out << ",";
                }
            }
        }
        out << std::endl;

        // Print the separator
        for (const auto &column : columns)
        {
            out << std::string(displayWidth, '-');
            if (column.first != columns.rbegin()->first)
            {
                if (isCout) {
                    out << "\t|";
                } else {
                    out << ",";
                }
            }
        }
        out << std::endl;

        // Print the rows
        for (size_t i = 0; i < columns.begin()->second.size(); i++)
        {
            for (const auto &column : columns)
            {
                out << column.second[i].substr(0, displayWidth);
                if (isCout && column.second[i].length() < displayWidth)
                {
                    out << std::string(displayWidth - column.second[i].length(), ' ');
                }
                if (column.first != columns.rbegin()->first)
                {
                    if (isCout) {
                        out << "\t|";
                    } else {
                        out << ",";
                    }
                }
            }
            out << std::endl;
        }
    }

    void to_csv(std::string filename)
    {
        // Open the file
        std::ofstream file(filename);

        // Print the DataFrame to the file
        print(file);

        // Close the file
        file.close();
    }

    void show()
    {
        print();
    }

private:
    // Map that stores the column data for the DataFrame, using the column name as the key
    std::map<std::string, std::vector<std::string>> columns;
    int maxDisplayWidth = 10;
};
