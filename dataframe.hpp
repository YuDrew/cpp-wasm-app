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
        for (int i = 0; i < column_names.size(); i++)
        {
            // Create a vector to store the column data
            std::vector<std::string> column_data;

            // Add the column data to the vector
            for (int j = 0; j < rows.size(); j++)
            {
                column_data.push_back(rows[j][i]);
            }

            // Add the column to the DataFrame
            add_column(column_names[i], column_data);
        }
    }

    // Adds a column with a given name and data to the DataFrame
    void add_column(std::string column_name, std::vector<std::string> column_data)
    {
        // Store the column data in the columns map, using the column name as the key
        columns[column_name] = column_data;
    }

    // Prints the DataFrame to the console
    void print()
    {
        // Print the column names
        for (const auto &column : columns)
        {
            std::cout << column.first << " ";
        }
        std::cout << std::endl;

        // Print the rows
        for (int i = 0; i < columns.begin()->second.size(); i++)
        {
            for (const auto &column : columns)
            {
                std::cout << column.second[i] << " ";
            }
            std::cout << std::endl;
        }
    }

    void to_csv(std::string filename)
    {
        // Open the file
        std::ofstream file(filename);

        // Print the column names
        for (const auto &column : columns)
        {
            file << column.first;
            if (column.first != columns.rbegin()->first)
            {
                file << ",";
            }
        }
        file << std::endl;

        // Print the rows
        for (int i = 0; i < columns.begin()->second.size(); i++)
        {
            for (const auto &column : columns)
            {
                file << column.second[i];
                if (column.first != columns.rbegin()->first)
                {
                    file << ",";
                }
            }
            file << std::endl;
        }

        // Close the file
        file.close();
    }   

private:
    // Map that stores the column data for the DataFrame, using the column name as the key
    std::map<std::string, std::vector<std::string>> columns;
};
