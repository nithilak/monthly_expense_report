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

  Year& year_2026 = InsertYear(2026);

  // Month& January2026 = year_2026.months[static_cast<unsigned int>(curr_month) - 1];

  std::cout << std::endl;

  for (int i = 1; i < 13; i++) {
    std::chrono::month curr_month = static_cast<std::chrono::month>(i);
    PrintExpenses(year_2026, curr_month);
  }

  // for (int i = 1; i < 13; i++) {
  //   std::chrono::month curr_month = static_cast<std::chrono::month>(i);
  //   PopulateExpenses("includes/" + year_str + "Expenses/" + std::format("{:%B}", curr_month) + year_str + ".csv", year_2026, curr_month);
  //   PrintExpenses(year_2026, curr_month);
  // }
  // Month& curr_month = year.months[static_cast<unsigned int>(month) - 1];
  // std::vector<Expense>& expenses = curr_month.expenses;

  PrintAnnualTotal(year_2026);

  return 0;
}