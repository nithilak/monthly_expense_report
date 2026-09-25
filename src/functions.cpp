#include "constants.hpp"
#include "functions.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <format>
#include <chrono>
#include <filesystem>

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

// Parses a single CSV line, handling backslash escapes (\"), doubled quotes (""), and embedded commas
std::vector<std::string> parseCSVLine2(const std::string& line) {
    std::vector<std::string> row;
    std::string field = "";
    bool inQuotes = false;

    size_t end_size = line.length();
    for (size_t i = 0; i < end_size; ++i) {
        char c = line[i];

        if (inQuotes) {
            if (c == '"') {
                if (i + 1 < line.length() && line[i + 1] == '"') {
                    // Doubled quote escape (""): append a single quote and skip the second one
                    field += '"';
                    ++i; 
                } else {
                    // Closing quote found
                    if (!(i == end_size - 2 && i != 0)) {
                        std::cerr << "CSV not formatted properly." << std::endl;
                    }
                    inQuotes = false;
                }
            } else {
                field += c;
            }
        } 
        else {
            if (c == '"') {
                // Opening quote found
                inQuotes = true;
            } else if (c == ',') {
                // End of field reached
                row.push_back(field);
                field.clear();
            } else {
                field += c;
            }
        }
    }
    // Add the final field
    row.push_back(field);
    return row;
}

// Parses a single CSV line, handling backslash escapes (\"), doubled quotes (""), and embedded commas
std::vector<std::string> parseCSVLine3(const std::string& line) {
    std::vector<std::string> ret;
    std::string field = "";

    char c = line[0];
    if (c != '"') {
        std::cerr << "CSV not formatted properly." << std::endl;
    }

    size_t end_size = line.length();
    for (size_t i = 1; i < end_size; ++i) {
        char c = line[i];

        if (c == '"') {
            if (i + 1 < line.length() && line[i + 1] == '"') {
                // Doubled quote escape (""): append a single quote and skip the second one
                field += '"';
                ++i; 
            } else {
                // Closing quote found
                if (++i >= end_size && line[i] != ',') {
                    std::cerr << "CSV not formatted properly." << std::endl;
                }
                i++;
                ret.push_back(field);
                ret.push_back(line.substr(i, end_size - i));
                return ret;
            }
        } else {
            field += c;
        }

        // } 
        // else {
        //     if (c == ',') {
        //         // End of field reached
        //         // row.push_back(field);
        //         // field.clear();
        //         return field;
        //     } else {
        //         field += c;
        //     }
        // }
    }
    // Add the final field
    ret.push_back(field);
    return ret;
}

// Parses a single CSV line, handling backslash escapes (\"), doubled quotes (""), and embedded commas
std::vector<std::string> parseCSVLine4(const std::string& line) {
    std::vector<std::string> row;
    std::string field = "";
    bool inQuotes = false;
    int quote_count = 0;

    size_t end_size = line.length();
    for (size_t i = 0; i < end_size; ++i) {
        char c = line[i];

        if (inQuotes) {
            if (c == '"') {
                if (i + 1 < line.length() && line[i + 1] == '"') {
                    // Doubled quote escape (""): append a single quote and skip the second one
                    field += '"';
                    ++i; 
                } else {
                    // Closing quote found
                    if (!(i == end_size - 2 && i != 0)) {
                        std::cerr << "CSV not formatted properly." << std::endl;
                    }
                    inQuotes = false;
                    quote_count++;
                }
            } else {
                field += c;
            }
        } 
        else {
            if (c == '"') {
                // Opening quote found
                inQuotes = true;
                quote_count++;
            } else if (c == ',') {
                // End of field reached
                row.push_back(field);
                field.clear();
            } else {
                field += c;
            }
        }
    }
    // Add the final field
    row.push_back(field);

    if (quote_count != 2) {
        std::cerr << "CSV not formatted properly." << std::endl;
    }

    return row;
}

// Parses a single CSV line, handling backslash escapes (\"), doubled quotes (""), and embedded commas
std::string parseCSVLine5ChangeLine(std::string& line) {
    std::string field = "";

    char c = line[0];
    if (c != '"') {
        throw std::runtime_error("CSV not formatted properly.");
    }

    size_t end_size = line.length();
    for (size_t i = 1; i < end_size; ++i) {
        char c = line[i];

        if (c == '"') {
            if (i + 1 < line.length() && line[i + 1] == '"') {
                // Doubled quote escape (""): append a single quote and skip the second one
                field += '"';
                ++i; 
            } else {
                // Closing quote found
                if (++i >= end_size && line[i] != ',') {
                    throw std::runtime_error("CSV not formatted properly.");
                }
                i++;
                line = line.substr(i, end_size - i);
                return field;
            }
        } else {
            field += c;
        }

        // } 
        // else {
        //     if (c == ',') {
        //         // End of field reached
        //         // row.push_back(field);
        //         // field.clear();
        //         return field;
        //     } else {
        //         field += c;
        //     }
        // }
    }
    // Add the final field
    throw std::runtime_error("CSV not formatted properly.");
    return field;
}

std::string MakeQuoted(const std::string& line) {
    // std::cout << line << std::endl;
    std::string output;
    output += "\"";

    for (char c : line) {
        output += c;
        if (c == '"') {
            output += c;
        }
    }

    output += "\"";

    return output;
}

std::string ReturnDirPath(const std::string& filename) {
    int filename_length = filename.size();
    for (int i = filename_length - 1; i >= 0; i--) {
        std::cout << filename.at(i) << std::endl;
        if (filename.at(i) == '/') {
            return filename.substr(0, i + 1);
        }
    }
    return "";
}

std::vector<std::string> SplitPath(const std::string& filename) {
    std::vector<std::string> ret;

    if (filename.empty()) {
        return ret;
    }

    int filename_length = filename.size();
    for (int i = filename_length - 1; i >= 0; i--) {
        // std::cout << filename.at(i) << std::endl;
        if (filename.at(i) == '/') {
            ret.push_back(filename.substr(0, i + 1));
            ret.push_back(filename.substr(i + 1, filename_length - i - 1));
            return ret;
        }
    }

    // ret.push_back(filename.substr(0, i + 1));
    return ret;
}

void PrintMenu() {
    // std::cout << "Insert year: 0, Choose year: 1, See available years: 2, Delete year: 3" << std::endl;
    // std::cout << "Print all month expenses: 4, Print month expenses: 5" << std::endl;
    // std::cout << "Add expense: 6, Delete expense: 7" << std::endl;
    // std::cout << "Update month file: 8, Update all month files: 9, Update totals file: 10" << std::endl; //9 is for a year
    // // std::cout << "Update all month files and total files for all years: 11" << std::endl; 
    // std::cout << "Print all month totals: 11, Print annual total: 12" << std::endl;

    std::cout << "0: Insert year\n";
    std::cout << "1: See available years\n";
    std::cout << "2: Choose year\n";
    std::cout << "3: Delete year\n";
    std::cout << "4: Print annual total\n";
    std::cout << "5: Print all month totals in a year\n";
    std::cout << "6: Print full list of expenses in a year\n";
    std::cout << "7: Print full list of expenses in a month\n";
    std::cout << "8: Add Expense\n";
    std::cout << "9: Delete Expense\n";


}

void PrintMenuYear(std::chrono::year year) {
    // std::cout << "Year: " << year << std::endl;
    // std::cout << "Return to all years: 0" << std::endl;
    // std::cout << "Print all month expenses: 4, Print month expenses: 5" << std::endl;
    // std::cout << "Add expense: 6, Delete expense: 7" << std::endl;
    // std::cout << "Update month file: 8, Update all month files: 9, Update totals file: 10" << std::endl; 
    // std::cout << "Print all month totals: 11, Print annual total: 12" << std::endl;

    std::cout << "4: Print annual total\n";
    std::cout << "5: Print all month totals in a year\n";
    std::cout << "6: Print full list of expenses in a year\n";
    std::cout << "7: Print full list of expenses in a month\n";
    std::cout << "8: Add Expense\n";
    std::cout << "9: Delete Expense\n";
}

void PrintAvailableYears() {
    std::cout << "Available years: ";

    int years_size_goal = years.size() - 1;
    if (years_size_goal > -1) {
        auto it = years.begin();
        for (int i = 0; i < years_size_goal; i++) {
        std::cout << it->first << ", ";
        ++it;
        }
        std::cout << it->first;
    }

    std::cout << "\n" << std::endl;
}

void PrintAllExpenses(const Year& year) {
    std::chrono::month curr_month = std::chrono::January;
    for (int i = 1; i < 13; i++) {
    //   std::chrono::month curr_month = static_cast<std::chrono::month>(i);
      PrintExpenses(year, curr_month);
      curr_month++;
    }
}

void RecalculateYearTotals(Year& year) {
    year.total = 0.0;
    for (auto& month : year.months) {
        month.total = 0.0;
        for (const auto& expense : month.expenses) {
            month.total += expense.cost;
        }
        year.total += month.total;
    }
}


double PrintExpenses(const std::multiset<Expense>& expenses) {
    // // Set the equal width for each column
    // const int colWidth = 20;
    // const int strWidth = 80;

    double total = 0;

    // Print top border
    std::cout << std::string(colWidth * 2 + strWidth + idWidth, '-') << "\n";


    std::cout << std::left 
                    << std::setw(colWidth) << "Cost"
                    << std::setw(strWidth) << "Reason"
                    << std::setw(colWidth) << "Date" << "\n";

    std::cout << std::string(colWidth * 2 + strWidth + idWidth, '-') << "\n";

    auto expense = expenses.begin();
    int expenses_size_goal = expenses.size() + 1;
    for (int i = 1; i < expenses_size_goal; i++) { //const auto& expense : expenses //size_t i = 0; i < csvData.size(); ++i
        // std::vector<std::string> row = parseCSVLine(csvData[i]);

        //std::string date = std::format("{:02}-{}", curr_month, expenses[i].day);
        std::string date = std::format("{:02}", static_cast<unsigned>(expense->day));

        double cost = expense->cost;

        // Ensure the row has exactly 3 columns to avoid out-of-bounds errors
        // if (row.size() >= 3) {
            // std::left aligns text to the left; std::setw sets fixed spacing
            std::cout << std::left 
                        << std::setw(colWidth) << cost
                        << std::setw(strWidth) << expense->reason
                        << std::setw(colWidth) << date 
                        << std::setw(idWidth) << i << "\n";
        // }

        // Print a divider under the header row
        // if (i == 0) {
        //     std::cout << std::string(colWidth * 2 + strWidth, '-') << "\n";
        // }
        total += cost;
        expense++;
    }

    std::cout << std::string(colWidth * 2 + strWidth + idWidth, '-') << "\n";

    std::cout << "Total" << std::endl;

    // std::cout << std::string(colWidth * 2 + strWidth + idWidth, '-') << "\n";
    
    std::cout << total << std::endl;

    // Print bottom border
    std::cout << std::string(colWidth * 2 + strWidth + idWidth, '-') << "\n" << std::endl;

    return total;
}

void PrintExpenses(const Month& month) {
    std::chrono::month curr_month = month.month;
    std::cout << std::format("{:%B}", curr_month) << std::endl;


    const std::multiset<Expense>& expenses = month.expenses;


    // // Set the equal width for each column
    // const int colWidth = 20;
    // const int strWidth = 80;

    // Print top border
    std::cout << std::string(colWidth * 2 + strWidth + idWidth, '-') << "\n";


    std::cout << std::left 
                    << std::setw(colWidth) << "Cost"
                    << std::setw(strWidth) << "Reason"
                    << std::setw(colWidth) << "Date" << "\n";

    std::cout << std::string(colWidth * 2 + strWidth + idWidth, '-') << "\n";

    auto expense = expenses.begin();
    int expenses_size_goal = expenses.size() + 1;
    for (int i = 1; i < expenses_size_goal; i++) { //const auto& expense : expenses //size_t i = 0; i < csvData.size(); ++i
        // std::vector<std::string> row = parseCSVLine(csvData[i]);

        //std::string date = std::format("{:02}-{}", curr_month, expenses[i].day);
        std::string date = std::format("{:02}-{:02}", static_cast<unsigned>(curr_month), static_cast<unsigned>(expense->day));

        // Ensure the row has exactly 3 columns to avoid out-of-bounds errors
        // if (row.size() >= 3) {
            // std::left aligns text to the left; std::setw sets fixed spacing
            std::cout << std::left 
                        << std::setw(colWidth) << expense->cost
                        << std::setw(strWidth) << expense->reason
                        << std::setw(colWidth) << date 
                        << std::setw(idWidth) << i << "\n";
        // }

        // Print a divider under the header row
        // if (i == 0) {
        //     std::cout << std::string(colWidth * 2 + strWidth, '-') << "\n";
        // }
        expense++;
    }

    std::cout << std::string(colWidth * 2 + strWidth + idWidth, '-') << "\n";

    std::cout << "Total" << std::endl;

    // std::cout << std::string(colWidth * 2 + strWidth + idWidth, '-') << "\n";
    
    std::cout << month.total << std::endl;

    // Print bottom border
    std::cout << std::string(colWidth * 2 + strWidth + idWidth, '-') << "\n" << std::endl;
}

// void PrintExpenses(const Month& month, std::chrono::year year) {
//     const std::multiset<Expense>& expenses = month.expenses;
//     std::chrono::month curr_month = month.month;

//     std::cout << std::format("{:%B} {}", curr_month, static_cast<int>(year)) << std::endl;


//     // // Set the equal width for each column
//     // const int colWidth = 20;
//     // const int strWidth = 80;

//     // Print top border
//     std::cout << std::string(colWidth * 2 + strWidth + idWidth, '-') << "\n";


//     std::cout << std::left 
//                     << std::setw(colWidth) << "Cost"
//                     << std::setw(strWidth) << "Reason"
//                     << std::setw(colWidth) << "Date" << "\n";

//     std::cout << std::string(colWidth * 2 + strWidth + idWidth, '-') << "\n";

//     auto expense = expenses.begin();
//     int expenses_size_goal = expenses.size() + 1;
//     for (int i = 1; i < expenses_size_goal; i++) { //const auto& expense : expenses //size_t i = 0; i < csvData.size(); ++i
//         // std::vector<std::string> row = parseCSVLine(csvData[i]);

//         //std::string date = std::format("{:02}-{}", curr_month, expenses[i].day);
//         std::string date = std::format("{}-{:02}-{:02}", year, static_cast<unsigned>(curr_month), static_cast<unsigned>(expense->day));

//         // Ensure the row has exactly 3 columns to avoid out-of-bounds errors
//         // if (row.size() >= 3) {
//             // std::left aligns text to the left; std::setw sets fixed spacing
//             std::cout << std::left 
//                         << std::setw(colWidth) << expense->cost
//                         << std::setw(strWidth) << expense->reason
//                         << std::setw(colWidth) << date 
//                         << std::setw(idWidth) << i << "\n";
//         // }

//         // Print a divider under the header row
//         // if (i == 0) {
//         //     std::cout << std::string(colWidth * 2 + strWidth, '-') << "\n";
//         // }
//         expense++;
//     }

//     std::cout << std::string(colWidth * 2 + strWidth + idWidth, '-') << "\n";

//     std::cout << "Total" << std::endl;

//     // std::cout << std::string(colWidth * 2 + strWidth + idWidth, '-') << "\n";
    
//     std::cout << month.total << std::endl;

//     // Print bottom border
//     std::cout << std::string(colWidth * 2 + strWidth + idWidth, '-') << "\n" << std::endl;
// }

void PrintExpenses(const Year& year, std::chrono::month curr_month) {
    int curr_year = static_cast<int>(year.year);
    const Month& month = year.months[static_cast<unsigned int>(curr_month) - 1];
    const std::multiset<Expense>& expenses = month.expenses;

    std::cout << std::format("{:%B} {}", curr_month, curr_year) << std::endl;


    // // Set the equal width for each column
    // const int colWidth = 20;
    // const int strWidth = 80;

    // Print top border
    std::cout << std::string(colWidth * 2 + strWidth + idWidth, '-') << "\n";


    std::cout << std::left 
                    << std::setw(colWidth) << "Cost"
                    << std::setw(strWidth) << "Reason"
                    << std::setw(colWidth) << "Date" << "\n";

    std::cout << std::string(colWidth * 2 + strWidth + idWidth, '-') << "\n";

    auto expense = expenses.begin();
    int expenses_size_goal = expenses.size() + 1;
    for (int i = 1; i < expenses_size_goal; i++) { //const auto& expense : expenses //size_t i = 0; i < csvData.size(); ++i
        // std::vector<std::string> row = parseCSVLine(csvData[i]);

        //std::string date = std::format("{:02}-{}", curr_month, expenses[i].day);
        std::string date = std::format("{}-{:02}-{:02}", year.year, static_cast<unsigned>(curr_month), static_cast<unsigned>(expense->day));

        // Ensure the row has exactly 3 columns to avoid out-of-bounds errors
        // if (row.size() >= 3) {
            // std::left aligns text to the left; std::setw sets fixed spacing
            std::cout << std::left 
                        << std::setw(colWidth) << expense->cost
                        << std::setw(strWidth) << expense->reason
                        << std::setw(colWidth) << date 
                        << std::setw(idWidth) << i << "\n";
        // }

        // Print a divider under the header row
        // if (i == 0) {
        //     std::cout << std::string(colWidth * 2 + strWidth, '-') << "\n";
        // }
        expense++;
    }

    std::cout << std::string(colWidth * 2 + strWidth + idWidth, '-') << "\n";

    std::cout << "Total" << std::endl;

    // std::cout << std::string(colWidth * 2 + strWidth + idWidth, '-') << "\n";
    
    std::cout << month.total << std::endl;

    // Print bottom border
    std::cout << std::string(colWidth * 2 + strWidth + idWidth, '-') << "\n" << std::endl;
}

double PopulateExpenses(const std::string& filename, Month& month) {
    month.filename = filename;

    std::vector<std::string> paths = SplitPath(filename);

    if (paths.size() != 2) {
        std::cerr << filename << " filename for month " << std::format("{:%b}", month.month) << " could not be read." << std::endl;
        return 0;
    }

    // std::cout << paths[0] << std::endl;
    // std::cout << paths[1] << std::endl;

    std::string dirPath = paths[0];

    if (dirPath.empty()) {
        std::cerr << filename << " directory could not be read." << std::endl;
        return 0;
    }

    if (std::filesystem::create_directories(dirPath)) {
        std::cerr << "Directory " << dirPath << " not found. Creating directory..." << std::endl;
    }

    if (paths[1].empty()) {
        std::cerr << filename << " file name could not be read." << std::endl;
        return 0;
    }

    // 1. Open the CSV file using an input file stream
    std::ifstream file(filename);

    // Best Practice: Always check if the file opened successfully
    if (!file.is_open()) {
        std::cerr << paths[1] << " file not found. Creating file..." << std::endl;
        std::ofstream file(filename);
        file << "cost,reason,day\n";
        return 0;
    }

    std::multiset<Expense>& expenses = month.expenses;

    expenses.clear(); //just to make sure

    double& total = month.total;
    month.total = 0; //just to make sure
    std::string line;
    std::getline(file, line); //the header
    // std::cout << line << std::endl;

    while (std::getline(file, line)) {
        // std::cout << line << std::endl;
        std::string cost;
        std::string reason;
        std::string day;

        try {
            std::stringstream ss(line);
            std::getline(ss, cost, ',');
            std::getline(ss, line);

            reason = parseCSVLine5ChangeLine(line);
            if (reason.find_first_not_of(" \t\n\v\f\r") == std::string::npos) {
                throw std::runtime_error("Reason cannot be empty.");
            }
            //day = line; //could just use line

            // std::vector<std::string> contents = parseCSVLine3(line);

            // std::string reason = contents[0];

            // if (reason.empty()) {
            //     std::cerr << "Reason cannot be empty." << std::endl;
            // }

            // std::string day = contents[1];
            
            // std::cout << cost << std::endl;
            // std::cout << reason << std::endl;
            // std::cout << line << std::endl; //std::cout << day << std::endl;

            double costd = std::stod(cost);
            total += costd;
            expenses.insert(Expense(costd, reason, std::chrono::day(std::stoi(line))));
        } catch (const std::exception& e) {
            std::cerr << "Error in " << filename << "\n" << e.what() << std::endl;
        }
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

double PopulateExpenses(Year& year) {
    std::string year_str = std::format("{}", year.year);
    year.total = 0; //just to make sure

    std::chrono::month curr_month = std::chrono::January;
    for (int i = 1; i < 13; i++) {
        year.total += PopulateExpenses("includes/" + year_str + "Expenses/" + std::format("{:%b}", curr_month) + year_str + ".csv", year.months[static_cast<unsigned int>(curr_month) - 1]);
        //PrintExpenses(year, curr_month);
        curr_month++;
    }

    return year.total;
}

void PrintAnnualTotal(const Year& year) {
    std::cout << std::format("Year {}", static_cast<int>(year.year)) << std::endl;
    std::cout << std::string(colWidth * 2 + strWidth, '-') << "\n";
    std::cout << "Total Annual Expense: \n" << year.total << std::endl;
    std::cout << std::string(colWidth * 2 + strWidth, '-') << "\n" << std::endl;
}

Year& InsertYear(int year) {
    // std::string year_str = std::format("{:04}", year);
    std::chrono::year year_to_insert = std::chrono::year{year};
    years.insert({year_to_insert, Year(year_to_insert)});

    Year& year_return = years.at(year_to_insert); //should not cause an error because the year was just inserted

    PopulateExpenses(year_return);
    
    UpdateTotalsFile(year_return);

    return year_return;
}

bool is_empty_or_whitespace(const std::string& s) {
    return std::all_of(s.begin(), s.end(), [](unsigned char ch) {
        return std::isspace(ch);
    });
}

int AddExpense(Year& year, std::chrono::month curr_month) {
    Month& month = year.months[static_cast<unsigned int>(curr_month) - 1];

    std::cout << "Adding expense to: " << std::format("{:%B} {}", curr_month, static_cast<int>(year.year)) << std::endl;

    std::cout << "Enter q to quit." << std::endl;

    std::string line;

    double num{};

    // std::cout << "Enter a number, a word, and a day (1-31): ";
    std::cout << "Enter a cost: ";

    while (std::getline(std::cin, line)) {
        if (line == "q") {
            std::cout << std::endl;
            return 0;
        }

        std::stringstream ss(line);

        if (ss >> num) {
            std::cout << "Cost: " << num << "\n";
            break;
        } else {
            std::cout << "Invalid input.\n";
        }

        std::cout << "Enter a cost: ";
    }

    std::string text;

    std::cout << "Enter a reason: ";

    while (std::getline(std::cin, text)) {
        if (text == "q") {
            std::cout << std::endl;
            return 0;
        }

        if (text.find_first_not_of(" \t\n\v\f\r") != std::string::npos) {
            std::cout << "Reason: " << text << "\n";
            break;
        } else {
            std::cout << "Reason cannot be empty.\n";
        }

        std::cout << "Enter a reason: ";
    }

    unsigned day_value{};
    std::chrono::day d{};
    auto mdl = curr_month / std::chrono::last; // Last day of any February
    auto ymdl = year.year / mdl;             // Resolves leap year (29 days)

    std::chrono::day last_day = ymdl.day(); 
    unsigned last_day_num = static_cast<unsigned>(last_day);
    std::string date;

    std::cout << "Enter a day (1-" << last_day_num << "): ";

    while (std::getline(std::cin, line)) {
        if (line == "q") {
            std::cout << std::endl;
            return 0;
        }

        // Parse the numeric cost, reason text, and day manually.
        // std::chrono::parse is not available in this standard library implementation.
        std::stringstream ss(line);
        if (ss >> day_value) {
            if (day_value >= 1 && day_value <= last_day_num) {
                d = std::chrono::day{static_cast<unsigned>(day_value)};
                date = std::format("{}-{:02}-{:02}", 
                    static_cast<int>(year.year), 
                    static_cast<unsigned>(curr_month), 
                    static_cast<unsigned>(d)
                );
                std::cout << "Day: " << date << "\n";
                break;
            } else {
                std::cout << "Invalid day. Please enter a value from 1 to 31.\n";
            }
        } else {
            std::cout << "Invalid input.\n";
        }

        std::cout << "Enter a day (1-" << last_day_num << "): ";
    }

    std::cout << "Add Expense: " << num << ", " << text << ", " << date << std::endl;
    std::cout << "Press y or n" << std::endl;

    while (std::getline(std::cin, line)) {
        if (line == "q") {
            std::cout << std::endl;
            return 0;
        }

        if (line == "y") {
            month.expenses.insert(Expense(num, text, d));
            month.total += num;
            year.total += num;
            // month.changed = true;
            std::cout << "Expense added.\n" << std::endl;
            return 1;
        }

        if (line == "n") {
            return AddExpense(year, curr_month);
        }

        std::cout << "Invalid input.\n";

    }

    return 0;
}

int DeleteExpense(Year& year, std::chrono::month curr_month) {
    Month& month = year.months[static_cast<unsigned int>(curr_month) - 1];
    std::multiset<Expense>& expenses = month.expenses; 
    // PrintExpenses(expenses, month, year.year);

    std::cout << "Deleting expense from: " << std::format("{:%B} {}", curr_month, static_cast<int>(year.year)) << std::endl;

    std::cout << "Enter q to quit." << std::endl;

    std::string line;

    unsigned num{};

    // std::cout << "Enter a number, a word, and a day (1-31): ";
    std::cout << "Enter a line number: ";

    while (std::getline(std::cin, line)) {
        if (line == "q") {
            std::cout << std::endl;
            return 0;
        }

        std::stringstream ss(line);

        if (ss >> num) {
            if (num - 1 < expenses.size()) {
                auto it = std::next(expenses.begin(), num - 1);
                const Expense& expense = *it;
                std::string date = std::format("{}-{:02}-{:02}", 
                    static_cast<int>(year.year), 
                    static_cast<unsigned>(curr_month), 
                    static_cast<unsigned>(expense.day)
                );
                std::cout << "Delete expense: " << expense.cost << ", " << expense.reason << ", " << date << std::endl;
                std::cout << "Press y or n" << std::endl;

                while (std::getline(std::cin, line)) {
                    if (line == "q") {
                        std::cout << std::endl;
                        return 0;
                    }

                    if (line == "y") {
                        //const double deleted_cost = expense.cost;
                        month.total -= expense.cost;
                        year.total -= expense.cost;
                        expenses.erase(it);
                        // month.changed = true;
                        std::cout << "Expense deleted.\n" << std::endl;
                        return 1;
                    }

                    if (line == "n") {
                        return DeleteExpense(year, curr_month);
                    }

                    std::cout << "Invalid input.\n";

                }
            } else {
                std::cout << "Line number not found.\n";
            }
        } else {
            std::cout << "Invalid input.\n";
        }

        std::cout << "Enter a line number: ";
    }

    return 0;
}

int DeleteExpense(std::chrono::year year, Month& month) {
    std::multiset<Expense>& expenses = month.expenses; 
    std::chrono::month curr_month = month.month;
    // PrintExpenses(expenses, month);

    std::cout << "Deleting expense from: " << std::format("{:%B} {}", curr_month, static_cast<int>(year)) << std::endl;

    std::cout << "Enter q to quit." << std::endl;

    std::string line;

    unsigned num{};

    // std::cout << "Enter a number, a word, and a day (1-31): ";
    std::cout << "Enter a line number: ";

    while (std::getline(std::cin, line)) {
        if (line == "q") {
            std::cout << std::endl;
            return 0;
        }

        std::stringstream ss(line);

        if (ss >> num) {
            if (num - 1 < expenses.size()) {
                auto it = std::next(expenses.begin(), num - 1);
                const Expense& expense = *it;
                std::string date = std::format("{}-{:02}-{:02}", 
                    static_cast<int>(year), 
                    static_cast<unsigned>(curr_month), 
                    static_cast<unsigned>(expense.day)
                );
                std::cout << "Delete expense: " << expense.cost << ", " << expense.reason << ", " << date << std::endl;
                std::cout << "Press y or n" << std::endl;

                while (std::getline(std::cin, line)) {
                    if (line == "q") {
                        std::cout << std::endl;
                        return 0;
                    }

                    if (line == "y") {
                        month.total -= expense.cost;
                        expenses.erase(it);
                        // month.changed = true;
                        std::cout << "Expense deleted.\n" << std::endl;
                        return 1;
                    }

                    if (line == "n") {
                        return DeleteExpense(year, month);
                    }

                    std::cout << "Invalid input.\n";

                }
            } else {
                std::cout << "Line number not found.\n";
            }
        } else {
            std::cout << "Invalid input.\n";
        }

        std::cout << "Enter a line number: ";
    }

    return 0;
}

int UpdateMonthFile(const Year& year, std::chrono::month curr_month) {
    const Month& month = year.months[static_cast<unsigned int>(curr_month) - 1];
    std::string filename = month.filename;

    std::vector<std::string> paths = SplitPath(filename);

    if (paths.size() != 2) {
        std::cerr << filename << " filename for " << std::format("{}-{:%b}", year.year, month.month) << " could not be read." << std::endl;
        return 0;
    }

    std::string dirPath = paths[0];

    if (dirPath.empty()) {
        std::cerr << filename << " directory could not be read." << std::endl;
        return 0;
    }

    if (std::filesystem::create_directories(dirPath)) {
        std::cerr << "Directory " << dirPath << " not found. Creating directory..." << std::endl;
    }

    if (paths[1].empty()) {
        std::cerr << filename << " file name could not be read." << std::endl;
        return 0;
    }

    if (!std::filesystem::exists(filename)) {
        std::cerr << paths[1] << " file not found. Creating file..." << std::endl;
    }

    // 1. Open the CSV file using an input file stream
    std::ofstream file(filename);

    // Best Practice: Always check if the file opened successfully
    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file!" << std::endl;
        return 0;
    }

    const std::multiset<Expense>& expenses = month.expenses;

    file << "cost,reason,day\n";

    for (const auto& expense : expenses) {
        file << expense.cost << ",";


        file << std::quoted(expense.reason, '"', '"') << ",";


        file << std::format("{:02}", static_cast<unsigned>(expense.day)) << "\n";
    }

    // month.changed = false;

    return 1;
}

int UpdateAllMonthFiles(const Year& year) {
    int count = 0;
    std::chrono::month month_to_add = std::chrono::January;
    for (int i = 1; i < 13; i++) {
        count += UpdateMonthFile(year, month_to_add);
        month_to_add++;
    }
    return count;
}

int UpdateTotalsFile(const Year& year) {
    std::string year_str = std::format("{}", year.year);
    std::string filename = "includes/" + year_str + "Expenses/TotalExpenses" + year_str + ".csv";

    std::vector<std::string> paths = SplitPath(filename);

    if (paths.size() != 2) {
        std::cerr << filename << " filename for year " << std::format("{}", year.year) << " could not be read." << std::endl;
        return 0;
    }

    std::string dirPath = paths[0];

    if (dirPath.empty()) {
        std::cerr << filename << " directory could not be read." << std::endl;
        return 0;
    }

    if (std::filesystem::create_directories(dirPath)) {
        std::cerr << "Directory " << dirPath << " not found. Creating directory..." << std::endl;
    }

    if (paths[1].empty()) {
        std::cerr << filename << " file name could not be read." << std::endl;
        return 0;
    }

    if (!std::filesystem::exists(filename)) {
        std::cerr << paths[1] << " file not found. Creating file..." << std::endl;
    }
    
    // 1. Open the CSV file using an output file stream
    std::ofstream file(filename);

    // Best Practice: Always check if the file opened successfully
    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file!" << std::endl;
        return 0;
    }

    file << "Jan,Feb,Mar,Apr,May,Jun,Jul,Aug,Sep,Oct,Nov,Dec,Total\n";

    for (const auto& month : year.months) {
        file << month.total << ",";
        // month.changed = false;
    }
    file << year.total << "\n";

    return 1;
}

void PrintTotalsInternal(const Year& year) {
    std::cout << std::format("Year {}", static_cast<int>(year.year)) << std::endl;
    std::cout << std::string(colWidth * 6, '-') << "\n";

    std::cout << std::left;
    for (unsigned i = 1; i < 7; ++i) {
        std::cout << std::setw(colWidth) << std::format("{:%B}", std::chrono::month{i});
    }
    std::cout << std::endl;

    std::cout << std::left;
    for (int i = 0; i < 6; ++i) {
        std::cout << std::setw(colWidth) << year.months[i].total;
    }
    std::cout << std::endl;

    std::cout << std::string(colWidth * 6, '-') << "\n";
    std::cout << std::left;
    for (unsigned i = 7; i < 13; ++i) {
        std::cout << std::setw(colWidth) << std::format("{:%B}", std::chrono::month{i});
    }
    std::cout << std::endl;

    std::cout << std::left;
    for (int i = 6; i < 12; ++i) {
        std::cout << std::setw(colWidth) << year.months[i].total;
    }
    std::cout << std::endl;

    std::cout << std::string(colWidth * 6, '-') << "\n";
    std::cout << "Total: \n" << year.total << std::endl;
    std::cout << std::string(colWidth * 6, '-') << "\n" << std::endl;
}

int PrintTotalsFile(const Year& year) {
    std::string year_str = std::format("{}", year.year);
    std::string filename = "includes/" + year_str + "Expenses/TotalExpenses" + year_str + ".csv";

    std::ifstream file(filename);
    if (!file.is_open()) {
        UpdateTotalsFile(year);
        std::cout << std::endl;

        file.clear();
        file.open(filename);

        if (!file.is_open()) {
            std::cerr << "Error: Could not open the file!" << std::endl;
            std::cout << std::endl;
            return 0;
        }
    }

    std::string line;
    std::vector<std::string> header;
    std::vector<std::string> values;

    if (std::getline(file, line)) {
        std::stringstream header_stream(line);
        std::string cell;
        while (std::getline(header_stream, cell, ',')) {
            header.push_back(cell);
        }
    }

    if (std::getline(file, line)) {
        std::stringstream values_stream(line);
        std::string cell;
        while (std::getline(values_stream, cell, ',')) {
            values.push_back(cell);
        }
    }

    if (header.empty() || values.empty()) {
        std::cerr << "Error: No totals data found in the CSV file." << std::endl;
        std::cout << std::endl;
        return 0;
    }

    std::cout << std::format("Year {}", static_cast<int>(year.year)) << std::endl;
    std::cout << std::string(colWidth * 6, '-') << "\n";

    std::cout << std::left;
    for (int i = 0; i < 6 && i < static_cast<int>(header.size()); ++i) {
        std::cout << std::setw(colWidth) << header[i];
    }
    std::cout << std::endl;

    std::cout << std::left;
    for (int i = 0; i < 6 && i < static_cast<int>(values.size()); ++i) {
        std::cout << std::setw(colWidth) << values[i];
    }
    std::cout << std::endl;

    std::cout << std::string(colWidth * 6, '-') << "\n";
    std::cout << std::left;
    for (int i = 6; i < 12 && i < static_cast<int>(header.size()); ++i) {
        std::cout << std::setw(colWidth) << header[i];
    }
    std::cout << std::endl;

    std::cout << std::left;
    for (int i = 6; i < 12 && i < static_cast<int>(values.size()); ++i) {
        std::cout << std::setw(colWidth) << values[i];
    }
    std::cout << std::endl;

    std::cout << std::string(colWidth * 6, '-') << "\n";
    std::cout << "Total: \n" << (values.size() > 12 ? values[12] : "0") << std::endl;
    std::cout << std::string(colWidth * 6, '-') << "\n" << std::endl;

    return 1;
}

int PromptInsertYear() {

    std::string line;

    std::cout << "Press 0 to insert all years in directory \"./includes/\"" << std::endl;
    std::cout << "Insert year: ";

    while (std::getline(std::cin, line)) {
        if (line == "q") {
            return 0;
        } 

        if (line == "zero") {
            std::cout << "Are you sure you want to enter year 0?" << std::endl;
            std::cout << "Press y or n" << std::endl;

            while (std::getline(std::cin, line)) {
                if (line == "q") {
                    return 0;
                } else if (line == "y") {
                    std::cout << "Inserted year: " << 0 << "\n";
                    InsertYear(0);
                    return 1;
                } else if (line == "n") {
                    break;
                } else {
                    std::cout << "Invalid input\n";
                }
            }

            std::cout << "Insert year: ";
            continue;
        }

        int num;

        std::stringstream ss(line);

        if (ss >> num) {
            if (num == 0) { //so you can't insert a 0 year
                std::cout << std::endl;
                std::filesystem::path targetDir = "./includes/"; 
                int count = 0;
                try {
                    if (std::filesystem::exists(targetDir) && std::filesystem::is_directory(targetDir)) {
                        for (const auto& entry : std::filesystem::directory_iterator(targetDir)) {
                            // Check if the current entry is a folder
                            if (entry.is_directory()) {
                                std::string path = entry.path().filename().string();
                                std::stringstream ss(path);
                                int year_num;
                                std::string word;
                                if ((ss >> year_num)) {
                                    if (ss >> word && word == "Expenses") {
                                        // if (year_num == 0) {
                                        //     std::cout << "Zero year not allowed.\n";
                                        // } else {
                                            std::cout << "Inserted year: " << year_num << "\n";
                                            InsertYear(year_num);
                                            count++;
                                        // }
                                    }
                                }
                            }
                        }
                    } else {
                        std::cerr << "Provided path does not exist or is not a directory." << std::endl;
                    }
                } catch (const std::filesystem::filesystem_error& e) {
                    std::cerr << "Error: " << e.what() << std::endl;
                }

                return count; //should I really return count of inserted years, or should I return 1?
                
            } else {
                // std::cout << std::endl; //only because it becomes hard to read
                std::cout << "Inserted year: " << num << "\n";
                InsertYear(num);
                return 1;
            }
        } else {
            std::cout << "Invalid input.\n";
        }

        std::cout << "Insert year: ";

    }
    
    std::cerr << "Year(s) could not be inserted." << std::endl;
    // std::exit(1);
    return 0; //return -1;
}

std::pair<Year&, bool> PromptYear() {
    std::string line;
    std::cout << "Enter 0 for latest year. Choose year: ";

    int num;

    while (std::getline(std::cin, line)) {
        std::stringstream ss(line);
        if (line == "q") {
            return {quit_year, false};
        }

        bool choose_zero = false;


        if (line == "zero") {
            choose_zero = true;
            // 1. Clear the contents
            ss.str(""); 
            
            // 2. Reset error flags (like EOF), allowing you to write/read again safely
            ss.clear(); 

            ss << "0";
        }

        if (ss >> num) {
            if (years.empty()) {
                std::cerr << "No years are available." << std::endl;

                std::cout << "Insert year?" << std::endl;
                std::cout << "Press y or n" << std::endl;

                while (std::getline(std::cin, line)) {
                    if (line == "y") {
                        // if (num == 0) {
                        //     if (PromptInsertYear()) {
                        //         return {years.begin()->second, true};
                        //     } else {
                        //         return {quit_year, false};
                        //     }
                        // } else {
                        //     if (InsertYear(num)) {
                        //         return {years.begin()->second, true};
                        //     } else {
                        //         return {quit_year, false};
                        //     }

                        // if (PromptInsertYear()) {
                        //     return {years.begin()->second, true};
                        // } else {
                        //     return {quit_year, false};
                        // }

                        PromptInsertYear();
                        return {quit_year, false};


                    } else if (line == "n" || line == "q") {
                        return {quit_year, false};
                    }
                }

            }

            if (num == 0 && !choose_zero) {
                auto it = years.end();
                --it;
                return {it->second, true};
            } else {
                std::chrono::year year_to_insert = std::chrono::year{num};
                auto it = years.find(year_to_insert);
                if (it != years.end()) {
                    return {it->second, true};
                } else {
                    std::cout << "Year not found.\n";
                }
            }
        } else {
            std::cout << "Invalid input.\n";
        }

        std::cout << "Enter 0 for latest year. Choose year: ";
    }

    std::cerr << "Year could not be chosen." << std::endl;
    std::cout << std::endl;
    // std::exit(1);
    return {quit_year, false};
}

std::chrono::month PromptMonth() {
    std::string line;
    std::cout << "Choose month (1-12): ";

    unsigned num;

    while (std::getline(std::cin, line)) {
        if (line == "q") {
            return std::chrono::month{0};
        }

        std::stringstream ss(line);

        if (ss >> num) {
            if (0 < num && num < 13) {
                return static_cast<std::chrono::month>(num);
            } else {
                std::cout << "Please choose a number between 1-12.\n";
            }
        } else {
            std::cout << "Invalid input.\n";
        }
        std::cout << "Choose month (1-12): ";
    }

    std::cerr << "Month could not be chosen." << std::endl;
    std::cout << std::endl;
    // std::exit(1);
    return std::chrono::month{0};
}

int PromptYearErase() {
    std::string line;
    std::cout << "Enter q to quit. Choose year: ";

    int num;

    while (std::getline(std::cin, line)) {
        if (line == "q") {
            std::cout << std::endl;
            return 0;
        }
        std::stringstream ss(line);

        if (line == "zero") { //in case you are used to entering zero to mean choose year 0
            // 1. Clear the contents
            ss.str(""); 
            
            // 2. Reset error flags (like EOF), allowing you to write/read again safely
            ss.clear(); 

            ss << "0";
        }

        if (ss >> num) {
            std::chrono::year year_to_insert = std::chrono::year{num};
            bool erased = years.erase(year_to_insert);
            if (erased) {
                std::cout << "Deleted year " << year_to_insert << std::endl; //"Erased year"
            } else {
                std::cout << "Year " << year_to_insert << " was not found." << std::endl;
            }
            std::cout << std::endl;
            return erased;
        } else {
            std::cout << "Invalid input.\n";
        }

        std::cout << "Enter q to quit. Choose year: ";
    }

    std::cerr << "Year could not be chosen." << std::endl;
    std::cout << std::endl;
    // std::exit(1);
    return 0;
}