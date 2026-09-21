#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <array>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <chrono>

struct Expense {
    double cost;
    std::string reason;
    std::chrono::day day;

    Expense(double enter_cost, std::string enter_reason, std::chrono::day enter_day) {
        cost = enter_cost;
        reason = enter_reason;
        day = enter_day;
    }

    std::string toString() const {
        return std::format("{:.2f}, {}, {}\n", cost, reason, day);
    }

    // Sort by date first, then cost, then reason so same-day entries stay distinct.
    bool operator<(const Expense& other) const {
        if (this->day != other.day) {
            return this->day < other.day;
        }
        if (this->cost != other.cost) {
            return this->cost < other.cost;
        }
        return this->reason < other.reason;
    }

    bool operator>(const Expense& other) const {
        return other < *this;
    }

    // Overloading the == operator as a member function
    bool operator==(const Expense& other) const {
        return (this->cost == other.cost) && (this->reason == other.reason) && (this->day == other.day);
    }
    // Overloading the != operator as a member function
    bool operator!=(const Expense& other) const {
        return (this->cost != other.cost) || (this->reason != other.reason) || (this->day != other.day);
    }

    // // Default equality operator
    // bool operator==(const Expense&) const = default;
};
class Month {
  public:
    // std::chrono::year year;
    std::chrono::month month;
    std::set<Expense> expenses;
    double total = 0;
    std::string filename;
    // bool changed = false;

    Month(std::chrono::month enter_month) { //, std::chrono::year enter_year
        month = enter_month;
        // year = enter_year;
    }

    Month(std::string enter_filename, std::chrono::month enter_month) { //, std::chrono::year enter_year
        month = enter_month;
        // year = enter_year;
        filename = enter_filename;
    }

    // Overloading the < operator as a member function
    bool operator<(const Month& other) const {
        return this->month < other.month;
    }
};

class Year {
  public:
    std::chrono::year year;
    std::array<Month, 12> months = {Month(std::chrono::January), Month(std::chrono::February), Month(std::chrono::March), Month(std::chrono::April), Month(std::chrono::May), Month(std::chrono::June), Month(std::chrono::July), Month(std::chrono::August), Month(std::chrono::September), Month(std::chrono::October), Month(std::chrono::November), Month(std::chrono::December)};
    double total = 0;

    Year(std::chrono::year enter_year) {
        year = enter_year;
    }

    // Overloading the < operator as a member function
    bool operator<(const Year& other) const {
        return this->year < other.year;
    }
};

//doing this to avoid implementing multiple lookups with binary search using set when looking for the year
inline std::map<std::chrono::year, Year> years; 

// Set the equal width for each column
constexpr int colWidth = 20;

constexpr int strWidth = 80;
constexpr int idWidth = 3;


#endif // CONSTANTS_HPP