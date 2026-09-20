#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <fstream>
#include <string>
#include <vector>

#include "constants.hpp"

void PrintFile(std::string filename);

std::vector<std::string> parseCSVLine(const std::string& line);

double PrintExpenses(const std::vector<Expense>& expenses);
void PrintExpenses(const Month& month);
void PrintExpenses(const Month& month, std::chrono::year year);
void PrintExpenses(Year& year, std::chrono::month curr_month);


double PopulateExpenses(const std::string& filename, Month& month);
double PopulateExpenses(const std::string& filename, Year& year, std::chrono::month curr_month);

void PrintAnnualTotal(const Year& year);

#endif // FUNCTIONS_HPP