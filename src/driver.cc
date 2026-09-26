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
  entry_timezone = GetComputerTimezone();


  std::string line;

  std::cout << "Enter q to quit." << std::endl;
  
  if (!PromptInsertYear()) {
    std::cout << std::endl;
    return 0;
  }

  std::cout << std::endl;

  PrintMenu();

  int num; //unsigned num;

  while (std::getline(std::cin, line)) {
    if (line == "q") {
      std::cout << std::endl;
      return 0;
    }

    std::stringstream ss(line);

    if (ss >> num) {
      if (num == 0) {
        std::cout << std::endl;
        PromptInsertYear();
        std::cout << std::endl;
      } else if (num == 2) {

        std::pair<Year&, bool> get_year = PromptYear();

        if (!get_year.second) {
          std::cout << std::endl;
          PrintMenu();
          continue;
        }
        Year& year = get_year.first;

        std::cout << std::endl;

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
            if (num == 6) {
              std::cout << std::endl;
              PrintAllExpenses(year);
            } else if (num == 5) {
              std::cout << std::endl;
              PrintTotalsInternal(year);
            } else if (num == 4) {
              std::cout << std::endl;
              PrintAnnualTotal(year);
            } else if (num == 9) {
              std::cout << std::endl;
              std::cout << "Audit file for " << year.year << std::endl;
              PrintYearAuditFile(year.year);
            }
            //else if (num == temp10) {
              // std::cout << std::endl;
              // UpdateTotalsFile(year);
              // std::cout << "Updated TotalExpenses" << year.year << ".csv\n" << std::endl;
            //} else if (num == temp9) {
              // std::cout << std::endl;
              // std::chrono::month month_to_add = std::chrono::January;
              // for (int i = 1; i < 13; i++) {
              //   bool passed = UpdateMonthFile(year, month_to_add);
              //   std::cout << std::format("{:%b}{}.csv {}updated.\n", 
              //           month_to_add, 
              //           year.year, 
              //           passed ? "" : "not ");
              //   month_to_add++;
              // }
              // std::cout << std::endl;
            //} 
            else {
              std::chrono::month get_month = PromptMonth();
              if (!get_month.ok()) {
                std::cout << std::endl;
                PrintMenuYear(year.year);
                continue;
              }
              std::chrono::month month_to_add = get_month; //old code was checking a bool first out of a pair and assigning the second element here

              std::cout << std::endl;
              if (num == 7) {
                PrintExpenses(year, month_to_add);
              } else if (num == 11) {
                if (AddExpense(year, month_to_add)) {
                  bool passed = UpdateMonthFile(year, month_to_add);
                  std::cout << std::format("{:%b}{}.csv {}updated.\n", 
                        month_to_add, 
                        year.year, 
                        passed ? "" : "not ");
                  UpdateTotalsFile(year);
                  std::cout << "Updated TotalExpenses" << year.year << ".csv\n" << std::endl;
                  std::cout << std::endl;
                }
              } else if (num == 12) {
                if (DeleteExpense(year, month_to_add)) {
                  bool passed = UpdateMonthFile(year, month_to_add);
                  std::cout << std::format("{:%b}{}.csv {}updated.\n", 
                        month_to_add, 
                        year.year, 
                        passed ? "" : "not ");
                  UpdateTotalsFile(year);
                  std::cout << "Updated TotalExpenses" << year.year << ".csv\n" << std::endl;
                  std::cout << std::endl;
                }
              } else if (num == 10) {
                std::cout << "Audit file for " << std::format("{:%B}", month_to_add) << " " << year.year << std::endl;
                PrintMonthAuditFile(year.year, month_to_add);
              } //else if (num == temp8) {
                // if (UpdateMonthFile(year, month_to_add)) {
                //   std::cout << std::format("{:%b}", month_to_add) << year.year << ".csv updated." << std::endl;
                // }
                // std::cout << std::endl;
              //}
            }
          } else {
            std::cout << "Invalid input.\n\n";
          }
          PrintMenuYear(year.year);
        }
      } else if (num == 1) {
        std::cout << std::endl;
        PrintAvailableYears();
      } else if (num == 3) {
        std::cout << std::endl;
        PromptYearErase();
      } else if (num == 8) {
        std::cout << std::endl;
        std::cout << "Audit file" << std::endl;
        PrintAuditFile();
      } else {
        std::pair<Year&, bool> get_year = PromptYear();
        
        if (!get_year.second) {
          std::cout << std::endl;
          PrintMenu();
          continue;
        }
        Year& year = get_year.first;

        if (num == 6) {
          std::cout << std::endl;
          PrintAllExpenses(year);
        } else if (num == 5) {
          std::cout << std::endl;
          PrintTotalsInternal(year);
        } else if (num == 4) {
          std::cout << std::endl;
          PrintAnnualTotal(year);
        } else if (num == 9) {
          std::cout << std::endl;
          std::cout << "Audit file for " << year.year << std::endl;
          PrintYearAuditFile(year.year);
        }//else if (num == temp10) {
          // std::cout << std::endl;
          // UpdateTotalsFile(year);
          // std::cout << "Updated TotalExpenses" << year.year << ".csv\n" << std::endl;
        //} //else if (num == temp9) {
          // std::cout << std::endl;
          // std::chrono::month month_to_add = std::chrono::January;
          // for (int i = 1; i < 13; i++) {
          //   // // if (UpdateMonthFile(year, month_to_add)) {
          //   // //   std::cout << std::format("{:%b}", month_to_add) << year.year << ".csv updated." << std::endl;
          //   // // } else {
          //   // //   std::cout << std::format("{:%b}", month_to_add) << year.year << ".csv not updated." << std::endl;
          //   // // }
          //   bool passed = UpdateMonthFile(year, month_to_add);
          //   // std::cout << std::format("{:%b}", month_to_add) << year.year << ".csv ";
          //   // if (!passed) {
          //   //   std::cout << "not ";
          //   // }
          //   // std::cout << "updated." << std::endl;
          //   std::cout << std::format("{:%b}{}.csv {}updated.\n", 
          //               month_to_add, 
          //               year.year, 
          //               passed ? "" : "not ");
          //   month_to_add++;
          // }
          // std::cout << std::endl;
        //} 
        else {
          std::chrono::month get_month = PromptMonth();
          if (!get_month.ok()) {
            std::cout << std::endl;
            PrintMenuYear(year.year);
            continue;
          }
          std::chrono::month month_to_add = get_month; //old code was checking a bool first out of a pair and assigning the second element here

          std::cout << std::endl;
          if (num == 7) {
            PrintExpenses(year, month_to_add);
          } else if (num == 11) {
            if (AddExpense(year, month_to_add)) {
              bool passed = UpdateMonthFile(year, month_to_add);
              std::cout << std::format("{:%b}{}.csv {}updated.\n", 
                    month_to_add, 
                    year.year, 
                    passed ? "" : "not ");
              UpdateTotalsFile(year);
              std::cout << "Updated TotalExpenses" << year.year << ".csv\n" << std::endl;
              std::cout << std::endl;
            }
          } else if (num == 12) {
            if (DeleteExpense(year, month_to_add)) {
              bool passed = UpdateMonthFile(year, month_to_add);
              std::cout << std::format("{:%b}{}.csv {}updated.\n", 
                    month_to_add, 
                    year.year, 
                    passed ? "" : "not ");
              UpdateTotalsFile(year);
              std::cout << "Updated TotalExpenses" << year.year << ".csv\n" << std::endl;
              std::cout << std::endl;
            }
          } else if (num == 10) {
            std::cout << "Audit file for " << std::format("{:%B}", month_to_add) << " " << year.year << std::endl;
            PrintMonthAuditFile(year.year, month_to_add);
          } //else if (num == temp8) {
            // if (UpdateMonthFile(year, month_to_add)) {
            //   std::cout << std::format("{:%b}", month_to_add) << year.year << ".csv updated." << std::endl;
            // }
            // std::cout << std::endl;
          //}
        }
      }
    } else {
      std::cout << "Invalid input.\n\n";
    }

    PrintMenu();
  }

  return 0;
}