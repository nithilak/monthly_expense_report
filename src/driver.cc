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
  std::string line;

  std::cout << "Enter q to quit." << std::endl;
  
  if (!PromptInsertYear()) {
    return 0;
  }

  std::cout << std::endl;

  while (true) {
    std::cout << "Insert year: 0, Choose year: 1, See available years: 2, Delete year: 3" << std::endl;
    std::cout << "Print all expenses: 4, Print month expenses: 5" << std::endl;
    std::cout << "Add expense: 6, Delete expense: 7" << std::endl; 
    std::cout << "Print all annual totals: 8, Print annual total: 9" << std::endl;

    unsigned num;

    while (std::getline(std::cin, line)) {
      if (line == "q") {
        return 0;
      }

      std::stringstream ss(line);

      if (ss >> num) {
        if (num == 0) {
          PromptInsertYear();
          std::cout << std::endl;
        } else if (num == 1) {

          Year& year = PromptYear();
          std::cout << std::endl;
          // std::chrono::year curr_year = year.year;

          std::cout << "Year: " << year.year << std::endl;
          std::cout << "Return to all years: 0" << std::endl;
          std::cout << "Print all expenses: 4, Print month expenses: 5" << std::endl;
          std::cout << "Add expense: 6, Delete expense: 7" << std::endl; 
          std::cout << "Print all annual totals: 8, Print annual total: 9" << std::endl;

          while (std::getline(std::cin, line)) {
            if (line == "q") {
              return 0;
            }

            std::stringstream ss(line);

            if (ss >> num) {
              if (num == 0) {
                std::cout << std::endl;
                break;
              }
              std::cout << std::endl;
              if (num == 4) {
                PrintAllExpenses(year);
              } else if (num == 8) {
                PrintTotalsFile(year);
              } else if (num == 9) {
                PrintAnnualTotal(year);
              } else {
                std::chrono::month month_to_add = PromptMonth();

                if (num == 5) {
                  PrintExpenses(year, month_to_add);
                } else if (num == 6) {
                  if (AddExpense(year, month_to_add)) {
                    UpdateMonthFile(year, month_to_add);
                    UpdateTotalsFile(year);
                  }
                } else if (num == 7) {
                  if (DeleteExpense(year, month_to_add)) {
                    UpdateMonthFile(year, month_to_add);
                    UpdateTotalsFile(year);
                  }
                }
              }
            } else {
              std::cout << "Invalid input.\n\n";
            }
            std::cout << "Year: " << year.year << std::endl;
            std::cout << "Return to all years: 0" << std::endl;
            std::cout << "Print all expenses: 4, Print month expenses: 5" << std::endl;
            std::cout << "Add expense: 6, Delete expense: 7" << std::endl;
            std::cout << "Print all annual totals: 8, Print annual total: 9" << std::endl;
          }
        } else if (num == 2) {
          std::cout << std::endl;
          std::cout << "Available years: ";
          for (const auto& [key, value] : years) {
            std::cout << key << " ";
          }
          std::cout << "\n" << std::endl;
        } else if (num == 3) {
          PromptYearErase();
        } else {
          Year& year = PromptYear();

          std::cout << std::endl;
          if (num == 4) {
            PrintAllExpenses(year);
          } else if (num == 8) {
            PrintTotalsFile(year);
          } else if (num == 9) {
            PrintAnnualTotal(year);
          } else {
            std::chrono::month month_to_add = PromptMonth();

            if (num == 5) {
              PrintExpenses(year, month_to_add);
            } else if (num == 6) {
              if (AddExpense(year, month_to_add)) {
                UpdateMonthFile(year, month_to_add);
                UpdateTotalsFile(year);
              }
              // std::cout << std::endl; //temp
            } else if (num == 7) {
              if (DeleteExpense(year, month_to_add)) {
                UpdateMonthFile(year, month_to_add);
                UpdateTotalsFile(year);
              }
              // std::cout << std::endl; //temp
            }
          }
        }
        break;
      } else {
        std::cout << "Invalid input.\n\n";
      }

      std::cout << "Insert year: 0, Choose year: 1, See available years: 2, Delete year: 3" << std::endl;
      std::cout << "Print all expenses: 4, Print month expenses: 5" << std::endl;
      std::cout << "Add expense: 6, Delete expense: 7" << std::endl; 
      std::cout << "Print all annual totals: 8, Print annual total: 9" << std::endl;
    }
  }

  return 0;
}