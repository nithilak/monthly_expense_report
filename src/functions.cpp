#include "constants.hpp"
#include "functions.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <format>

void PrintFile(std::string filename) {
    // 1. Open the CSV file using an input file stream
    std::ifstream file(filename);

    // Best Practice: Always check if the file opened successfully
    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file!" << std::endl;
        return;
    }

    // This 2D vector will hold all the rows and columns
    std::vector<std::vector<std::string>> csvData;
    std::string line;

    // 2. Read the file line by line
    while (std::getline(file, line)) {
        std::vector<std::string> row;
        std::stringstream ss(line);
        std::string cell;

        // 3. Split each line by the comma delimiter
        while (std::getline(ss, cell, ',')) {
            // Trim any leading/trailing whitespace from each CSV field.
            const auto start = cell.find_first_not_of(" \t\r\n");
            const auto end = cell.find_last_not_of(" \t\r\n");
            if (start == std::string::npos) {
                row.push_back("");
            } else {
                row.push_back(cell.substr(start, end - start + 1));
            }
        }

        // Add the parsed row to our 2D vector
        csvData.push_back(row);
    }

    // 4. Close the file stream
    file.close();

    // 5. Determine the widest value in each column so the output lines up.
    std::size_t columnCount = 0;
    for (const auto& row : csvData) {
        columnCount = std::max(columnCount, row.size());
    }

    std::vector<std::size_t> columnWidths(columnCount, 0);
    for (const auto& row : csvData) {
        for (std::size_t i = 0; i < row.size(); ++i) {
            columnWidths[i] = std::max(columnWidths[i], row[i].size());
        }
    }

    // 6. Print each row using fixed-width columns.
    for (const auto& row : csvData) {
        for (std::size_t i = 0; i < columnCount; ++i) {
            std::string value = (i < row.size()) ? row[i] : "";
            std::cout << std::left << std::setw(static_cast<int>(columnWidths[i] + 2)) << value;
        }
        std::cout << "\n";
    }
}

// Function to split a CSV line by commas
std::vector<std::string> parseCSVLine(const std::string& line) {
    std::vector<std::string> row;
    std::stringstream ss(line);
    std::string cell;
    
    while (std::getline(ss, cell, ',')) {
        row.push_back(cell);
    }
    return row;
}


double PrintExpenses(const std::vector<Expense>& expenses) {
    // // Set the equal width for each column
    // const int colWidth = 20;
    // const int strWidth = 80;

    int total = 0;

    // Print top border
    std::cout << std::string(colWidth * 2 + strWidth, '-') << "\n";


    std::cout << std::left 
                    << std::setw(colWidth) << "Cost"
                    << std::setw(strWidth) << "Reason"
                    << std::setw(colWidth) << "Date" << "\n";

    std::cout << std::string(colWidth * 2 + strWidth, '-') << "\n";

    for (int i = 0; i < expenses.size(); i++) { //size_t i = 0; i < csvData.size(); ++i
        // std::vector<std::string> row = parseCSVLine(csvData[i]);
        // double local_cost = expenses[i].cost;
        total += expenses[i].cost;

        // std::string date = std::to_string(2026) + "-" + "09" + "-" + std::format("{}", expenses[i].day);
        std::string date = std::format("{}", expenses[i].day);

        // Ensure the row has exactly 3 columns to avoid out-of-bounds errors
        // if (row.size() >= 3) {
            // std::left aligns text to the left; std::setw sets fixed spacing
            std::cout << std::left 
                        << std::setw(colWidth) << expenses[i].cost
                        << std::setw(strWidth) << expenses[i].reason
                        << std::setw(colWidth) << date << "\n";
        // }

        // Print a divider under the header row
        // if (i == 0) {
        //     std::cout << std::string(colWidth * 2 + strWidth, '-') << "\n";
        // }
    }

    std::cout << std::string(colWidth * 2 + strWidth, '-') << "\n";

    std::cout << "Total" << std::endl;
    std::cout << total << std::endl;

    // Print bottom border
    std::cout << std::string(colWidth * 2 + strWidth, '-') << "\n" << std::endl;

    return total;
}

void PrintExpenses(const Month& month) {
    const std::vector<Expense>& expenses = month.expenses;
    const auto& curr_month = month.month;
    // // Set the equal width for each column
    // const int colWidth = 20;
    // const int strWidth = 80;

    std::cout << std::format("{:%B}", curr_month) << std::endl;

    // Print top border
    std::cout << std::string(colWidth * 2 + strWidth, '-') << "\n";


    std::cout << std::left 
                    << std::setw(colWidth) << "Cost"
                    << std::setw(strWidth) << "Reason"
                    << std::setw(colWidth) << "Date" << "\n";

    std::cout << std::string(colWidth * 2 + strWidth, '-') << "\n";

    for (int i = 0; i < expenses.size(); i++) { //size_t i = 0; i < csvData.size(); ++i
        // std::vector<std::string> row = parseCSVLine(csvData[i]);

        //std::string date = std::format("{:02}-{}", curr_month, expenses[i].day);
        std::string date = std::format("{:02}-{:02}", static_cast<unsigned>(curr_month), static_cast<unsigned>(expenses[i].day));

        // Ensure the row has exactly 3 columns to avoid out-of-bounds errors
        // if (row.size() >= 3) {
            // std::left aligns text to the left; std::setw sets fixed spacing
            std::cout << std::left 
                        << std::setw(colWidth) << expenses[i].cost
                        << std::setw(strWidth) << expenses[i].reason
                        << std::setw(colWidth) << date << "\n";
        // }

        // Print a divider under the header row
        // if (i == 0) {
        //     std::cout << std::string(colWidth * 2 + strWidth, '-') << "\n";
        // }
    }

    std::cout << std::string(colWidth * 2 + strWidth, '-') << "\n";

    std::cout << "Total" << std::endl;
    std::cout << month.total << std::endl;

    // Print bottom border
    std::cout << std::string(colWidth * 2 + strWidth, '-') << "\n" << std::endl;
}

void PrintExpenses(const Month& month, std::chrono::year year) {
    const std::vector<Expense>& expenses = month.expenses;
    const auto& curr_month = month.month;

    std::cout << std::format("{:%B} {}", curr_month, static_cast<int>(year)) << std::endl;


    // // Set the equal width for each column
    // const int colWidth = 20;
    // const int strWidth = 80;

    // Print top border
    std::cout << std::string(colWidth * 2 + strWidth, '-') << "\n";


    std::cout << std::left 
                    << std::setw(colWidth) << "Cost"
                    << std::setw(strWidth) << "Reason"
                    << std::setw(colWidth) << "Date" << "\n";

    std::cout << std::string(colWidth * 2 + strWidth, '-') << "\n";

    for (int i = 0; i < expenses.size(); i++) { //size_t i = 0; i < csvData.size(); ++i
        // std::vector<std::string> row = parseCSVLine(csvData[i]);

        //std::string date = std::format("{:02}-{}", curr_month, expenses[i].day);
        std::string date = std::format("{}-{:02}-{:02}", 
            static_cast<int>(year), 
            static_cast<unsigned>(curr_month), 
            static_cast<unsigned>(expenses[i].day)
        );

        // Ensure the row has exactly 3 columns to avoid out-of-bounds errors
        // if (row.size() >= 3) {
            // std::left aligns text to the left; std::setw sets fixed spacing
            std::cout << std::left 
                        << std::setw(colWidth) << expenses[i].cost
                        << std::setw(strWidth) << expenses[i].reason
                        << std::setw(colWidth) << date << "\n";
        // }

        // Print a divider under the header row
        // if (i == 0) {
        //     std::cout << std::string(colWidth * 2 + strWidth, '-') << "\n";
        // }
    }

    std::cout << std::string(colWidth * 2 + strWidth, '-') << "\n";

    std::cout << "Total" << std::endl;
    std::cout << month.total << std::endl;

    // Print bottom border
    std::cout << std::string(colWidth * 2 + strWidth, '-') << "\n" << std::endl;
}

void PrintExpenses(Year& year, std::chrono::month curr_month) {
    int curr_year = static_cast<int>(year.year);
    Month& month = year.months[static_cast<unsigned int>(curr_month) - 1];
    const std::vector<Expense>& expenses = month.expenses;

    std::cout << std::format("{:%B} {}", curr_month, curr_year) << std::endl;


    // // Set the equal width for each column
    // const int colWidth = 20;
    // const int strWidth = 80;

    // Print top border
    std::cout << std::string(colWidth * 2 + strWidth, '-') << "\n";


    std::cout << std::left 
                    << std::setw(colWidth) << "Cost"
                    << std::setw(strWidth) << "Reason"
                    << std::setw(colWidth) << "Date" << "\n";

    std::cout << std::string(colWidth * 2 + strWidth, '-') << "\n";

    for (int i = 0; i < expenses.size(); i++) { //size_t i = 0; i < csvData.size(); ++i
        // std::vector<std::string> row = parseCSVLine(csvData[i]);

        //std::string date = std::format("{:02}-{}", curr_month, expenses[i].day);
        std::string date = std::format("{}-{:02}-{:02}", 
            static_cast<int>(curr_year), 
            static_cast<unsigned>(curr_month), 
            static_cast<unsigned>(expenses[i].day)
        );

        // Ensure the row has exactly 3 columns to avoid out-of-bounds errors
        // if (row.size() >= 3) {
            // std::left aligns text to the left; std::setw sets fixed spacing
            std::cout << std::left 
                        << std::setw(colWidth) << expenses[i].cost
                        << std::setw(strWidth) << expenses[i].reason
                        << std::setw(colWidth) << date << "\n";
        // }

        // Print a divider under the header row
        // if (i == 0) {
        //     std::cout << std::string(colWidth * 2 + strWidth, '-') << "\n";
        // }
    }

    std::cout << std::string(colWidth * 2 + strWidth, '-') << "\n";

    std::cout << "Total" << std::endl;
    std::cout << month.total << std::endl;

    // Print bottom border
    std::cout << std::string(colWidth * 2 + strWidth, '-') << "\n" << std::endl;;
}

double PopulateExpenses(const std::string& filename, Month& month) {
    month.filename = filename;

    // 1. Open the CSV file using an input file stream
    std::ifstream file(filename);

    // Best Practice: Always check if the file opened successfully
    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file!" << std::endl;
    }

    std::vector<Expense>& expenses = month.expenses;

    double& total = month.total;
    std::string line;
    std::getline(file, line);
    // std::cout << line << std::endl;

    while (std::getline(file, line)) {
        // std::cout << line << std::endl;
        // std::ranges::split_view result = std::views::split(line, ',');

        std::stringstream ss(line);

        std::string cost;
        std::string reason;
        std::string day;
        
        // Split by the comma delimiter
        std::getline(ss, cost, ',');
        std::getline(ss, reason, ',');
        std::getline(ss, day, '\n');

        // std::cout << cost << std::endl;
        // std::cout << reason << std::endl;
        // std::cout << day << std::endl;
        total += std::stod(cost);
        expenses.push_back(Expense(std::stod(cost), reason.substr(1, reason.size() - 2), std::chrono::day(std::stoi(day))));
        
    }

    file.close();

    return total;
}

double PopulateExpenses(const std::string& filename, Year& year, std::chrono::month curr_month) {
    Month& month = year.months[static_cast<unsigned int>(curr_month) - 1];
    month.filename = filename;
    double total = PopulateExpenses(filename, month);
    year.total += total;
    return total;
}

void PrintAnnualTotal(const Year& year) {
    std::cout << std::format("Year {}", static_cast<int>(year.year)) << std::endl;
    std::cout << std::string(colWidth * 2 + strWidth, '-') << "\n";
    std::cout << "Total Annual Expense: \n" << year.total << std::endl;
    std::cout << std::string(colWidth * 2 + strWidth, '-') << "\n" << std::endl;
}