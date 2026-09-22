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

void PrintMenu() {
    std::cout << "Insert year: 0, Choose year: 1, See available years: 2, Delete year: 3" << std::endl;
    std::cout << "Print all month expenses: 4, Print month expenses: 5" << std::endl;
    std::cout << "Add expense: 6, Delete expense: 7" << std::endl;
    std::cout << "Update month file: 8, Update all month files: 9, Update totals file: 10" << std::endl; 
    std::cout << "Print all annual totals: 11, Print annual total: 12" << std::endl;
}

void PrintMenuYear(std::chrono::year year) {
    std::cout << "Year: " << year << std::endl;
    std::cout << "Return to all years: 0" << std::endl;
    std::cout << "Print all month expenses: 4, Print month expenses: 5" << std::endl;
    std::cout << "Add expense: 6, Delete expense: 7" << std::endl;
    std::cout << "Update month file: 8, Update all month files: 9, Update totals file: 10" << std::endl; 
    std::cout << "Print all annual totals: 10, Print annual total: 11" << std::endl;
}

void PrintAllExpenses(const Year& year) {
    for (int i = 1; i < 13; i++) {
    //   std::chrono::month curr_month = static_cast<std::chrono::month>(i);
      PrintExpenses(year.months[i - 1], year.year);
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


double PrintExpenses(const std::set<Expense>& expenses) {
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

void PrintExpenses(const std::set<Expense>& expenses, const Month& month) {
    std::chrono::month curr_month = month.month;
    std::cout << std::format("{:%B}", curr_month) << std::endl;


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


void PrintExpenses(const std::set<Expense>& expenses, const Month& month, std::chrono::year year) {
    std::chrono::month curr_month = month.month;
    std::cout << std::format("{:%B} {}", curr_month, static_cast<int>(year)) << std::endl;


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
        std::string date = std::format("{}-{:02}-{:02}", year, static_cast<unsigned>(curr_month), static_cast<unsigned>(expense->day));

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

void PrintExpenses(const Month& month) {
    const std::set<Expense>& expenses = month.expenses;
    std::chrono::month curr_month = month.month;
    // // Set the equal width for each column
    // const int colWidth = 20;
    // const int strWidth = 80;

    std::cout << std::format("{:%B}", curr_month) << std::endl;

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

void PrintExpenses(const Month& month, std::chrono::year year) {
    const std::set<Expense>& expenses = month.expenses;
    std::chrono::month curr_month = month.month;

    std::cout << std::format("{:%B} {}", curr_month, static_cast<int>(year)) << std::endl;


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
        std::string date = std::format("{}-{:02}-{:02}", year, static_cast<unsigned>(curr_month), static_cast<unsigned>(expense->day));

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

void PrintExpenses(const Year& year, std::chrono::month curr_month) {
    int curr_year = static_cast<int>(year.year);
    const Month& month = year.months[static_cast<unsigned int>(curr_month) - 1];
    const std::set<Expense>& expenses = month.expenses;

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

    // 1. Open the CSV file using an input file stream
    std::ifstream file(filename);

    std::string dirPath = filename.substr(0, filename.size() - 11);
    if (std::filesystem::create_directories(dirPath)) {
        std::cerr << "Directory " << filename.substr(0, 21) << " not found. Creating directory..." << std::endl;
    }

    // Best Practice: Always check if the file opened successfully
    if (!file.is_open()) {
        std::cerr << filename.substr(filename.size() - 11, 11) << " file not found. Creating file..." << std::endl;
        std::ofstream file(filename);
        file << "cost,reason,date\n";
        return 0;
    }

    month.expenses.clear();

    std::set<Expense>& expenses = month.expenses;

    double& total = month.total;
    month.total = 0;
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
    year.total = 0;

    std::chrono::month curr_month = std::chrono::January;
    for (int i = 1; i < 13; i++) {
        PopulateExpenses("includes/" + year_str + "Expenses/" + std::format("{:%b}", curr_month) + year_str + ".csv", year, curr_month);
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
    std::string year_str = std::to_string(year);
    std::chrono::year year_to_insert = std::chrono::year{year};
    years.insert({year_to_insert, Year(year_to_insert)});

    Year& year_return = years.at(year_to_insert);

    PopulateExpenses(year_return);
    
    UpdateTotalsFile(year_return);

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
    }

    std::string text;

    std::cout << "Enter a reason: ";

    while (std::getline(std::cin, text)) {
        if (text == "q") {
            std::cout << std::endl;
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
    std::set<Expense>& expenses = month.expenses; 
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
            }
        } else {
            std::cout << "Invalid input.\n";
        }
    }

    return 0;
}

int DeleteExpense(std::chrono::year year, Month& month) {
    std::set<Expense>& expenses = month.expenses; 
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
            }
        } else {
            std::cout << "Invalid input.\n";
        }
    }

    return 0;
}

int UpdateMonthFile(const Year& year, std::chrono::month curr_month) {
    const Month& month = year.months[static_cast<unsigned int>(curr_month) - 1];
    std::string filename = month.filename;

    if (!std::filesystem::exists(filename)) {
        std::cerr << filename.substr(filename.size() - 11, 11) << " file not found. Creating file..." << std::endl;
    }

    // 1. Open the CSV file using an input file stream
    std::ofstream file(filename);

    // Best Practice: Always check if the file opened successfully
    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file!" << std::endl;
        return 0;
    }

    const std::set<Expense>& expenses = month.expenses;

    file << "cost,reason,date\n";

    for (const auto& expense : expenses) {
        file << expense.cost << ",\"" << expense.reason << "\"," << std::format("{:02}", static_cast<unsigned>(expense.day)) << "\n";
    }

    // month.changed = false;

    return 1;
}

int UpdateAllMonthFiles(const Year& year) {
    int count = 0;
    std::chrono::month curr_month = std::chrono::January;
    for (int i = 1; i < 13; i++) {
        // std::cout << "reaches" << std::endl;
        count += UpdateMonthFile(year.year, curr_month);
        curr_month++;
    }
    return count;
}

int UpdateTotalsFile(const Year& year) {
    std::string year_str = std::to_string(static_cast<int>(year.year));
    std::string filename = "includes/" + year_str + "Expenses/TotalExpenses" + year_str + ".csv";

    if (!std::filesystem::exists(filename)) {
        std::cout << filename.substr(filename.size() - 21, 21) << " file not found. Creating file...\n";
    }
    
    // 1. Open the CSV file using an output file stream
    std::ofstream file(filename);

    // Best Practice: Always check if the file opened successfully
    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file!" << std::endl;
        return 0;
    }

    file << "January,February,March,April,May,June,July,August,September,October,November,December,Total\n";

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
    std::string year_str = std::to_string(static_cast<int>(year.year));
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
    std::cout << "Insert year: ";

    unsigned num;

    while (std::getline(std::cin, line)) {
        if (line == "q") {
            return 0;
        }

        std::stringstream ss(line);

        if (ss >> num) {
            std::cout << "Inserted year: " << num << "\n";
            InsertYear(num);
            return 1;
        } else {
            std::cout << "Invalid input.\n";
        }
    }
    
    return -1;
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

        if (ss >> num) {
            if (years.empty()) {
                std::cerr << "No years are available.\n";

                std::cout << "Insert year?" << std::endl;
                std::cout << "Press y or n" << std::endl;

                while (std::getline(std::cin, line)) {
                    if (line == "y") {
                        PromptInsertYear();
                        return PromptYear();
                    } else if (line == "n" || line == "q") {
                        return {quit_year, false};
                    }
                }

            }

            if (num == 0) {
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
    std::exit(1);
}

std::pair<std::chrono::month, bool> PromptMonth() {
    std::string line;
    std::cout << "Choose month (1-12): ";

    unsigned num;

    while (std::getline(std::cin, line)) {
        if (line == "q") {
            return {std::chrono::January, false};
        }

        std::stringstream ss(line);

        if (ss >> num) {
            if (0 < num && num < 13) {
                return {static_cast<std::chrono::month>(num), true};
            } else {
                std::cout << "Please choose a number between 1-12.\n";
            }
        } else {
            std::cout << "Invalid input.\n";
        }
        std::cout << "Choose month (1-12): ";
    }

    std::cerr << "Month could not be chosen." << std::endl;
    std::exit(1);
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

        std::cout << "Enter q to quit.\nChoose year: ";
    }

    std::cerr << "Year could not be chosen." << std::endl;
    std::exit(1);
}