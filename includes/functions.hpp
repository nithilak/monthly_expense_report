#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <fstream>
#include <string>
#include <vector>

#include "constants.hpp"

void PrintFile(std::string filename);

std::vector<std::string> parseCSVLine(const std::string& line);

double PrintExpenses(const std::set<Expense>& expenses);
void PrintExpenses(const std::set<Expense>& expenses, const Month& month);
void PrintExpenses(const std::set<Expense>& expenses, std::chrono::month curr_month, std::chrono::year year);
void PrintExpenses(const Month& month);
void PrintExpenses(const Month& month, std::chrono::year year);
void PrintExpenses(Year& year, std::chrono::month curr_month);


double PopulateExpenses(const std::string& filename, Month& month);
double PopulateExpenses(const std::string& filename, Year& year, std::chrono::month curr_month);
double PopulateExpenses(Year& year);

void PrintAnnualTotal(const Year& year);

Year& InsertYear(int year);

int AddExpense(Year& year, std::chrono::month curr_month);

int DeleteExpense(Year& year, std::chrono::month curr_month);
int DeleteExpense(std::chrono::year year, Month& month);

int UpdateMonthFile(Year& year, std::chrono::month curr_month);

#endif // FUNCTIONS_HPP