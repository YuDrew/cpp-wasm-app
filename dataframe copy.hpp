#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
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

    // Returns the number of rows in the DataFrame
    size_t n_rows()
    {
        return columns.begin()->second.size();
    }

    // Returns the number of columns in the DataFrame
    size_t n_columns()
    {
        return columns.size();
    }

    // Returns the column names in the DataFrame
    std::vector<std::string> column_names()
    {
        // Create a vector to hold the column names
        std::vector<std::string> column_names;

        // Add the column names to the vector
        for (const auto &column : columns)
        {
            column_names.push_back(column.first);
        }

        // Return the vector
        return column_names;
    }

    // Returns the data in a given column
    std::vector<std::string> column_data(std::string column_name)
    {
        return columns[column_name];
    }

    // Returns the data in a given row
    std::vector<std::string> row_data(size_t row_index)
    {
        // Create a vector to hold the row data
        std::vector<std::string> row_data;

        // Add the row data to the vector
        for (const auto &column : columns)
        {
            row_data.push_back(column.second[row_index]);
        }

        // Return the vector
        return row_data;
    }

    // Returns the data in a given cell
    std::string cell_data(std::string column_name, size_t row_index)
    {
        return columns[column_name][row_index];
    }

    // Returns a sorted DataFrame by the given column and order
    DataFrame sort(std::string column_name, bool ascending = true)
    {
        // Create a vector to hold the column names
        std::vector<std::string> column_names;

        // Add the column names to the vector
        for (const auto &column : columns)
        {
            column_names.push_back(column.first);
        }

        // Create a vector to hold the row data
        std::vector<std::vector<std::string>> row_data;

        // Add the row data to the vector
        for (size_t i = 0; i < n_rows(); i++)
        {
            row_data.push_back(this->row_data(i));
        }

        // Create a DataFrame to hold the sorted data
        DataFrame sorted_df(column_names, row_data);

        // Sort the DataFrame
        sorted_df.sort_in_place(column_name, ascending);

        // Return the sorted DataFrame
        return sorted_df;
    }

    // Sorts the DataFrame by the given column and order
    void sort_in_place(std::string column_name, bool ascending = true)
    {
        // Create a vector to hold the row indices
        std::vector<size_t> row_indices(n_rows());

        // Initialize the row indices
        for (size_t i = 0; i < n_rows(); i++)
        {
            row_indices[i] = i;
        }

        // Sort the row indices
        std::sort(row_indices.begin(), row_indices.end(), [&](size_t a, size_t b) {
            if (ascending)
            {
                return columns[column_name][a] < columns[column_name][b];
            }
            else
            {
                return columns[column_name][a] > columns[column_name][b];
            }
        });

        // Create a vector to hold the column names
        std::vector<std::string> column_names;

        // Add the column names to the vector
        for (const auto &column : columns)
        {
            column_names.push_back(column.first);
        }

        // Create a vector to hold the row data
        std::vector<std::vector<std::string>> row_data;

        // Add the row data to the vector
        for (size_t i = 0; i < n_rows(); i++)
        {
            row_data.push_back(this->row_data(row_indices[i]));
        }

        // Create a DataFrame to hold the sorted data
        DataFrame sorted_df(column_names, row_data);

        // Replace the DataFrame with the sorted DataFrame
        *this = sorted_df;
    }

    // Returns a DataFrame with the given columns
    DataFrame select(std::vector<std::string> column_names)
    {
        // Create a vector to hold the column data
        std::vector<std::vector<std::string>> column_data;

        // Add the column data to the vector
        for (const auto &column_name : column_names)
        {
            column_data.push_back(columns[column_name]);
        }

        // Create and return the DataFrame
        return DataFrame(column_names, column_data);
    }

    // Returns a DataFrame with the given rows
    DataFrame select(size_t start_row, size_t end_row)
    {
        // Create a vector to hold the column names
        std::vector<std::string> column_names;

        // Add the column names to the vector
        for (const auto &column : columns)
        {
            column_names.push_back(column.first);
        }

        // Create a vector to hold the row data
        std::vector<std::vector<std::string>> row_data;

        // Add the row data to the vector
        for (size_t i = start_row; i < end_row; i++)
        {
            row_data.push_back(this->row_data(i));
        }

        // Create and return the DataFrame
        return DataFrame(column_names, row_data);
    }

    // Returns a DataFrame with the given rows and columns
    DataFrame select(std::vector<std::string> column_names, size_t start_row, size_t end_row)
    {
        // Create a vector to hold the row data
        std::vector<std::vector<std::string>> row_data;

        // Add the row data to the vector
        for (size_t i = start_row; i < end_row; i++)
        {
            row_data.push_back(this->row_data(i));
        }

        // Create and return the DataFrame
        return DataFrame(column_names, row_data);
    }

    // Join two DataFrames
    DataFrame inner_join(DataFrame &df, std::string left_on, std::string right_on)
    {
        // Create a vector to hold the column names
        std::vector<std::string> column_names;
        int count = 0, left_col_index, right_col_index;


        // Add the column names to the vector
        for (const auto &column : columns)
        {
            column_names.push_back(column.first);
        }
        count = 0;
        for (const auto &column : df.columns)
        {
            if (column.first != right_on)
            {
                column_names.push_back(column.first);
            }
        }

        // Create a vector to hold the row data
        std::vector<std::vector<std::string>> row_data;

        // Add the row data to the vector
        for (size_t i = 0; i < n_rows(); i++)
        {
            for (size_t j = 0; j < df.n_rows(); j++)
            {
                if (columns[left_on][i] == df.columns[right_on][j])
                {
                    std::vector<std::string> row;
                    for (const auto &column : columns)
                    {
                        row.push_back(column.second[i]);
                    }
                    for (const auto &column : df.columns)
                    {
                        if (column.first != right_on)
                        {
                            row.push_back(column.second[j]);
                        }
                    }
                    row_data.push_back(row);
                }
            }
        }

        // Create and return the DataFrame
        return DataFrame(column_names, row_data);
    }

    // Checks if the DataFrame contains a given column
    bool has_column(std::string column_name)
    {
        return columns.find(column_name) != columns.end();
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
            out << column.first.substr(0, displayWidth) << (isCout ? std::string(displayWidth - min(column.first.length(), displayWidth), ' ') : "");
            if (column.first != columns.rbegin()->first)
            {
                out << isCout ? "\t|" : ",";
            }
        }
        out << std::endl;

        if(isCout){
            // Print the separator
            for (const auto &column : columns)
            {
                cout << std::string(displayWidth, '-');
                if (column.first != columns.rbegin()->first)
                {
                    cout << "\t|";
                }
            }
            cout << std::endl;
        }

        // Print the rows
        for (size_t i = 0; i < columns.begin()->second.size(); i++)
        {
            for (const auto &column : columns)
            {
                out << column.second[i].substr(0, displayWidth) << (isCout ? std::string(displayWidth - min(column.second[i].length(), displayWidth), ' ') : "");
                if (column.first != columns.rbegin()->first)
                {
                    out << (isCout ? "\t|" : ",");
                }
            }
            out << std::endl;
        }
    }

    // filter the DataFrame by a given column and value
    DataFrame filter(std::string column_name, std::string value)
    {
        // Create a vector to hold the column names
        std::vector<std::string> column_names;

        // Create a vector to hold the rows
        std::vector<std::vector<std::string>> rows;

        // Get the column data for the given column
        std::vector<std::string> column_data = columns[column_name];

        // Get the index of the column
        int column_index = 0;
        for (const auto &column : columns)
        {
            if (column.first == column_name)
            {
                break;
            }
            column_index++;
        }

        // Add the column names to the vector
        for (const auto &column : columns)
        {
            column_names.push_back(column.first);
        }

        // Add the rows to the vector
        for (size_t i = 0; i < column_data.size(); i++)
        {
            if (column_data[i] == value)
            {
                // Create a vector to hold the row data
                std::vector<std::string> row_data;

                // Add the row data to the vector
                for (const auto &column : columns)
                {
                    row_data.push_back(column.second[i]);
                }

                // Add the row to the vector of rows
                rows.push_back(row_data);
            }
        }

        // Create the DataFrame
        return DataFrame(column_names, rows);
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
