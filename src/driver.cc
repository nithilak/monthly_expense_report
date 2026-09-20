#include "constants.hpp"
#include "functions.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <ranges>
#include <string_view>
#include <sstream>
#include <format>
#include <chrono>

int main() {
  // PrintFile("includes/january.csv");
  // PrintFile("includes/total_expenses.csv");

  int year = 2026;
  std::string year_str = std::to_string(year);
  std::chrono::year year_to_insert = std::chrono::year{year};
  years.insert({year_to_insert, Year(year_to_insert)});

  Year& year_2026 = years.at(year_to_insert);

  // Month& January2026 = year_2026.months[static_cast<unsigned int>(curr_month) - 1];

  std::cout << std::endl;

  std::chrono::month curr_month = std::chrono::January;
  PopulateExpenses("includes/" + year_str + "Expenses/" + std::format("{:%B}", curr_month) + year_str + ".csv", year_2026, curr_month);
  PrintExpenses(year_2026, curr_month);

  // Month& curr_month = year.months[static_cast<unsigned int>(month) - 1];
  // std::vector<Expense>& expenses = curr_month.expenses;



  // // Mock CSV data (Cost, Reason, Date)
  //   std::vector<std::string> csvData = {
  //       "Cost,Reason,Date",
  //       "12.50,Groceries,2026-09-15",
  //       "1200.00,Rent payment,2026-09-01",
  //       "45.00,Gasoline,2026-09-18",
  //       "4.99,Streaming service,2026-09-10",
  //       "10000.00,Rememberance of the fallen people of the day it's really sad,2026-09-11"
  //   };


  curr_month = std::chrono::February;
  PopulateExpenses("includes/" + year_str + "Expenses/" + std::format("{:%B}", curr_month) + year_str + ".csv", year_2026, curr_month);
  PrintExpenses(year_2026, curr_month);

  curr_month = std::chrono::March;
  PopulateExpenses("includes/" + year_str + "Expenses/" + std::format("{:%B}", curr_month) + year_str + ".csv", year_2026, curr_month);
  PrintExpenses(year_2026, curr_month);

  PrintAnnualTotal(year_2026);

  return 0;
}