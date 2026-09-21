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
    std::cout << "Add expense: 6, Delete expense: 7, Update month file: 8, Update all month files: 9" << std::endl; 
    std::cout << "Print all annual totals: 10, Print annual total: 11" << std::endl;

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
          std::cout << "Add expense: 6, Delete expense: 7, Update month file: 8" << std::endl; 
          std::cout << "Print all annual totals: 9, Print annual total: 10" << std::endl;

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
              } else if (num == 10) {
                PrintTotalsFile(year);
              } else if (num == 11) {
                PrintAnnualTotal(year);
              } else if (num == 9) {
                std::chrono::month month_to_add = std::chrono::January;
                for (int i = 1; i < 13; i++) {
                  bool passed = UpdateMonthFile(year, month_to_add);
                  std::cout << std::format("{:%b}{} .csv {}updated.\n", 
                         month_to_add, 
                         year.year, 
                         passed ? "" : "not ");
                  month_to_add++;
                }
                std::cout << std::endl;
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
                } else if (num == 8) {
                  if (UpdateMonthFile(year, month_to_add)) {
                    std::cout << std::format("{:%b}", month_to_add) << year.year << ".csv updated." << std::endl;
                  }
                  std::cout << std::endl;
                }
              }
            } else {
              std::cout << "Invalid input.\n\n";
            }
            std::cout << "Year: " << year.year << std::endl;
            std::cout << "Return to all years: 0" << std::endl;
            std::cout << "Print all expenses: 4, Print month expenses: 5" << std::endl;
            std::cout << "Add expense: 6, Delete expense: 7, Update month file: 8" << std::endl; 
            std::cout << "Print all annual totals: 9, Print annual total: 10" << std::endl;
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
          } else if (num == 10) {
            PrintTotalsFile(year);
          } else if (num == 11) {
            PrintAnnualTotal(year);
          } else if (num == 9) {
            std::chrono::month month_to_add = std::chrono::January;
            for (int i = 1; i < 13; i++) {
              // // if (UpdateMonthFile(year, month_to_add)) {
              // //   std::cout << std::format("{:%b}", month_to_add) << year.year << ".csv updated." << std::endl;
              // // } else {
              // //   std::cout << std::format("{:%b}", month_to_add) << year.year << ".csv not updated." << std::endl;
              // // }
              bool passed = UpdateMonthFile(year, month_to_add);
              // std::cout << std::format("{:%b}", month_to_add) << year.year << ".csv ";
              // if (!passed) {
              //   std::cout << "not ";
              // }
              // std::cout << "updated." << std::endl;
              std::cout << std::format("{:%b}{} .csv {}updated.\n", 
                         month_to_add, 
                         year.year, 
                         passed ? "" : "not ");
              month_to_add++;
            }
            std::cout << std::endl;
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
            } else if (num == 8) {
              if (UpdateMonthFile(year, month_to_add)) {
                std::cout << std::format("{:%b}", month_to_add) << year.year << ".csv updated." << std::endl;
              }
              std::cout << std::endl;
            }
          }
        }
        break;
      } else {
        std::cout << "Invalid input.\n\n";
      }

      std::cout << "Insert year: 0, Choose year: 1, See available years: 2, Delete year: 3" << std::endl;
      std::cout << "Print all expenses: 4, Print month expenses: 5" << std::endl;
      std::cout << "Add expense: 6, Delete expense: 7, Update month file: 8" << std::endl; 
      std::cout << "Print all annual totals: 9, Print annual total: 10" << std::endl;
    }
  }

  return 0;
}