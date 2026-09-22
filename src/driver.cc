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

  PrintMenu();

  unsigned num;

  while (std::getline(std::cin, line)) {
    if (line == "q") {
      return 0;
    }

    std::stringstream ss(line);

    if (ss >> num) {
      if (num == 0) {
        std::cout << std::endl;
        PromptInsertYear();
        std::cout << std::endl;
      } else if (num == 1) {

        std::pair<Year&, bool> get_year = PromptYear();

        std::cout << std::endl;

        if (!get_year.second) {
          PrintMenu();
          continue;
        }
        Year& year = get_year.first;


        PrintMenuYear(year.year);

        while (std::getline(std::cin, line)) {
          if (line == "q") {
            std::cout << std::endl;
            break;
          }

          std::stringstream ss(line);

          if (ss >> num) {
            if (num == 0) {
              std::cout << std::endl;
              break;
            }
            if (num == 4) {
              std::cout << std::endl;
              PrintAllExpenses(year);
            } else if (num == 11) {
              std::cout << std::endl;
              PrintTotalsInternal(year);
            } else if (num == 12) {
              std::cout << std::endl;
              PrintAnnualTotal(year);
            } else if (num == 10) {
              std::cout << std::endl;
              UpdateTotalsFile(year);
              std::cout << "Updated TotalExpenses" << year.year << ".csv\n" << std::endl;
            } else if (num == 9) {
              std::cout << std::endl;
              std::chrono::month month_to_add = std::chrono::January;
              for (int i = 1; i < 13; i++) {
                bool passed = UpdateMonthFile(year, month_to_add);
                std::cout << std::format("{:%b}{}.csv {}updated.\n", 
                        month_to_add, 
                        year.year, 
                        passed ? "" : "not ");
                month_to_add++;
              }
              std::cout << std::endl;
            } else {
              std::pair<std::chrono::month, bool> get_month = PromptMonth();
              if (!get_month.second) {
                PrintMenuYear(year.year);
                continue;
              }
              std::chrono::month month_to_add = get_month.first;

              std::cout << std::endl;
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
          PrintMenuYear(year.year);
        }
      } else if (num == 2) {
        std::cout << std::endl;
        std::cout << "Available years: ";
        auto it = years.begin();
        int years_size_goal = years.size() - 1;
        for (int i = 0; i < years_size_goal; i++) {
          std::cout << it->first << ", ";
          ++it;
        }
        std::cout << it->first << "\n" << std::endl;
      } else if (num == 3) {
        std::cout << std::endl;
        PromptYearErase();
      } else {
        std::pair<Year&, bool> get_year = PromptYear();
        
        if (!get_year.second) {
          std::cout << std::endl;
          PrintMenu();
          continue;
        }
        Year& year = get_year.first;

        if (num == 4) {
          std::cout << std::endl;
          PrintAllExpenses(year);
        } else if (num == 11) {
          std::cout << std::endl;
          PrintTotalsInternal(year);
        } else if (num == 12) {
          std::cout << std::endl;
          PrintAnnualTotal(year);
        } else if (num == 10) {
          std::cout << std::endl;
          UpdateTotalsFile(year);
          std::cout << "Updated TotalExpenses" << year.year << ".csv\n" << std::endl;
        } else if (num == 9) {
          std::cout << std::endl;
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
            std::cout << std::format("{:%b}{}.csv {}updated.\n", 
                        month_to_add, 
                        year.year, 
                        passed ? "" : "not ");
            month_to_add++;
          }
          std::cout << std::endl;
        } else {
          std::pair<std::chrono::month, bool> get_month = PromptMonth();
          if (!get_month.second) {
            std::cout << std::endl;
            PrintMenu();
            continue;
          }
          std::chrono::month month_to_add = get_month.first;

          std::cout << std::endl;
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
    } else {
      std::cout << "Invalid input.\n\n";
    }

    PrintMenu();
  }

  return 0;
}