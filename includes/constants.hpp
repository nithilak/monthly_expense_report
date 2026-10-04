#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <array>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <chrono>
#include <decimal.hh>

using namespace decimal;

struct Expense {
    Decimal cost;
    std::string reason;
    std::chrono::day day;

    Expense(Decimal enter_cost, std::string enter_reason, std::chrono::day enter_day) {
        cost = enter_cost;
        reason = enter_reason;
        day = enter_day;
    }

    std::string toString() const;

    // Sort by date first, then cost, then reason so same-day entries stay distinct.
    bool operator<(const Expense& other) const;

    bool operator>(const Expense& other) const;

    // Overloading the == operator as a member function
    bool operator==(const Expense& other) const;

    // Overloading the != operator as a member function
    bool operator!=(const Expense& other) const;

    // // Default equality operator
    // bool operator==(const Expense&) const = default;
};
class Month {
  public:
    // std::chrono::year year;
    std::chrono::month month;
    std::multiset<Expense> expenses;
    Decimal total = 0;
    std::string filename;
    // bool changed = false;

    Month(std::chrono::month enter_month);

    Month(std::string enter_filename, std::chrono::month enter_month);

    // Overloading the < operator as a member function
    bool operator<(const Month& other) const;
};

class Year {
  public:
    std::chrono::year year;
    std::array<Month, 12> months = {Month(std::chrono::January), Month(std::chrono::February), Month(std::chrono::March), Month(std::chrono::April), Month(std::chrono::May), Month(std::chrono::June), Month(std::chrono::July), Month(std::chrono::August), Month(std::chrono::September), Month(std::chrono::October), Month(std::chrono::November), Month(std::chrono::December)};
    Decimal total = 0;

    Year();

    Year(std::chrono::year enter_year);

    // Overloading the < operator as a member function
    bool operator<(const Year& other) const;
};

//doing this to avoid implementing multiple lookups with binary search using set when looking for the year
inline std::map<std::chrono::year, Year> years;
inline Year quit_year; //why does it have to be inline

//the length is currently the length of "includes/YEARExpenses"
//csv_dir_prefix_length
//fixed_csv_dir_size
constexpr int fixed_csv_file_prefix_length = 21;

// Set the equal width for each column
constexpr int colWidth = 20;

constexpr int strWidth = 80;
constexpr int lineNumWidth = 3; //6 //2

inline std::string entry_timezone;


#endif // CONSTANTS_HPP