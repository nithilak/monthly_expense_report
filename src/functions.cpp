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

    for (const auto& expense : expenses) { //size_t i = 0; i < csvData.size(); ++i
        // std::vector<std::string> row = parseCSVLine(csvData[i]);

        //std::string date = std::format("{:02}-{}", curr_month, expenses[i].day);
        std::string date = std::format("{:02}", static_cast<unsigned>(expense.day));

        // Ensure the row has exactly 3 columns to avoid out-of-bounds errors
        // if (row.size() >= 3) {
            // std::left aligns text to the left; std::setw sets fixed spacing
            std::cout << std::left 
                        << std::setw(colWidth) << expense.cost
                        << std::setw(strWidth) << expense.reason
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
    std::cout << std::string(colWidth * 2 + strWidth, '-') << "\n";

    return total;
}

void PrintExpenses(const Month& month) {
    const std::set<Expense>& expenses = month.expenses;
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

    for (const auto& expense : expenses) { //size_t i = 0; i < csvData.size(); ++i
        // std::vector<std::string> row = parseCSVLine(csvData[i]);

        //std::string date = std::format("{:02}-{}", curr_month, expenses[i].day);
        std::string date = std::format("{:02}-{:02}", static_cast<unsigned>(curr_month), static_cast<unsigned>(expense.day));

        // Ensure the row has exactly 3 columns to avoid out-of-bounds errors
        // if (row.size() >= 3) {
            // std::left aligns text to the left; std::setw sets fixed spacing
            std::cout << std::left 
                        << std::setw(colWidth) << expense.cost
                        << std::setw(strWidth) << expense.reason
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
    std::cout << std::string(colWidth * 2 + strWidth, '-') << "\n";
}

void PrintExpenses(const Month& month, std::chrono::year year) {
    const std::set<Expense>& expenses = month.expenses;
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

    for (const auto& expense : expenses) { //size_t i = 0; i < csvData.size(); ++i
        // std::vector<std::string> row = parseCSVLine(csvData[i]);

        //std::string date = std::format("{:02}-{}", curr_month, expenses[i].day);
        std::string date = std::format("{}-{:02}-{:02}", year, static_cast<unsigned>(curr_month), static_cast<unsigned>(expense.day));

        // Ensure the row has exactly 3 columns to avoid out-of-bounds errors
        // if (row.size() >= 3) {
            // std::left aligns text to the left; std::setw sets fixed spacing
            std::cout << std::left 
                        << std::setw(colWidth) << expense.cost
                        << std::setw(strWidth) << expense.reason
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
    std::cout << std::string(colWidth * 2 + strWidth, '-') << "\n";
}

void PrintExpenses(Year& year, std::chrono::month curr_month) {
    int curr_year = static_cast<int>(year.year);
    Month& month = year.months[static_cast<unsigned int>(curr_month) - 1];
    const std::set<Expense>& expenses = month.expenses;

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

    for (const auto& expense : expenses) { //size_t i = 0; i < csvData.size(); ++i
        // std::vector<std::string> row = parseCSVLine(csvData[i]);

        //std::string date = std::format("{:02}-{}", curr_month, expenses[i].day);
        std::string date = std::format("{}-{:02}-{:02}", year.year, static_cast<unsigned>(curr_month), static_cast<unsigned>(expense.day));

        // Ensure the row has exactly 3 columns to avoid out-of-bounds errors
        // if (row.size() >= 3) {
            // std::left aligns text to the left; std::setw sets fixed spacing
            std::cout << std::left 
                        << std::setw(colWidth) << expense.cost
                        << std::setw(strWidth) << expense.reason
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
    std::cout << std::string(colWidth * 2 + strWidth, '-') << "\n";
}

double PopulateExpenses(const std::string& filename, Month& month) {
    month.filename = filename;

    // 1. Open the CSV file using an input file stream
    std::ifstream file(filename);

    // Best Practice: Always check if the file opened successfully
    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file!" << std::endl;
    }

    std::set<Expense>& expenses = month.expenses;

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
        expenses.insert(Expense(std::stod(cost), reason.substr(1, reason.size() - 2), std::chrono::day(std::stoi(day))));
        
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
    std::string year_str = std::to_string(static_cast<int>(year.year));
    for (int i = 1; i < 13; i++) {
        std::chrono::month curr_month = static_cast<std::chrono::month>(i);
        PopulateExpenses("includes/" + year_str + "Expenses/" + std::format("{:%B}", curr_month) + year_str + ".csv", year, curr_month);
        //PrintExpenses(year, curr_month);
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
    std::string year_str = std::to_string(year);
    std::chrono::year year_to_insert = std::chrono::year{year};
    years.insert({year_to_insert, Year(year_to_insert)});

    Year& year_return = years.at(year_to_insert);

    PopulateExpenses(year_return);

    return year_return;
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
            return 0;
        }

        std::stringstream ss(line);

        if (ss >> num) {
            std::cout << "Cost: " << num << "\n";
            break;
        } else {
            std::cout << "Invalid input.\n";
        }
    }

    std::string text;

    std::cout << "Enter a reason: ";

    while (std::getline(std::cin, text)) {
        if (text == "q") {
            return 0;
        }

        if (!line.empty()) {
            std::cout << "Reason: " << text << "\n";
            break;
        } else {
            std::cout << "Reason cannot be empty.\n";
        }

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

    }

    std::cout << "Add Expense: " << num << ", " << text << ", " << date << std::endl;
    std::cout << "Press y or n" << std::endl;

    while (std::getline(std::cin, line)) {
        if (line == "q") {
            return 0;
        }

        if (line == "y") {
            month.expenses.insert(Expense(num, text, d));
            month.total += num;
            std::cout << "Expense added." << std::endl;
            return 1;
        }

        if (line == "n") {
            return AddExpense(year, curr_month);
        }

        std::cout << "Invalid input.\n";

    }

    return 0;
}

int UpdateMonthFile(Year& year, std::chrono::month curr_month) {
    Month& month = year.months[static_cast<unsigned int>(curr_month) - 1];
    std::string filename = month.filename;

    // 1. Open the CSV file using an input file stream
    std::ofstream file(filename);

    // Best Practice: Always check if the file opened successfully
    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file!" << std::endl;
        return 1;
    }

    std::set<Expense>& expenses = month.expenses;

    file << "cost,reason,date\n";

    for (const auto& expense : expenses) {
        file << expense.cost << ",\"" << expense.reason << "\"," << std::format("{:02}", static_cast<unsigned>(expense.day)) << "\n";
    }

    return 0;
}