#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <fstream>
#include <string>
#include <vector>

#include "constants.hpp"

//I don't use const iterators but maybe they could be implemented
//also perhaps there should be less copy and pasting in main

//not my code, prints a csv file
void PrintFile(std::string filename);

//not my code, // Function to split a CSV line by commas
std::vector<std::string> parseCSVLine(const std::string& line);

//prints out all expenses for each month the year
void PrintAllExpenses(const Year& year);

//prints out all expenses for the month
double PrintExpenses(const std::set<Expense>& expenses);
void PrintExpenses(const std::set<Expense>& expenses, const Month& month);
void PrintExpenses(const std::set<Expense>& expenses, std::chrono::month curr_month, std::chrono::year year);
void PrintExpenses(const Month& month);
void PrintExpenses(const Month& month, std::chrono::year year);
void PrintExpenses(const Year& year, std::chrono::month curr_month);

//reads in a csv file under the folder in includes/YEARExpenses/MONTHYEAR and uses it to fill month.expenses
//also updates each month and year total
double PopulateExpenses(const std::string& filename, Month& month);
double PopulateExpenses(const std::string& filename, Year& year, std::chrono::month curr_month);
double PopulateExpenses(Year& year);

void PrintAnnualTotal(const Year& year);

//inserts a year with all 12 month files formatted like includes/YEARExpenses/MONTHYEAR into years
Year& InsertYear(int year);

//adds an expense to a month
int AddExpense(Year& year, std::chrono::month curr_month);

//deletes an expense from a month
int DeleteExpense(Year& year, std::chrono::month curr_month);
int DeleteExpense(std::chrono::year year, Month& month);

//updates the month's csv file to match its data
int UpdateMonthFile(const Year& year, std::chrono::month curr_month);
int UpdateTotalsFile(const Year& year);

int PrintTotalsFile(const Year& year);

int PromptInsertYear();
Year& PromptYear();
std::chrono::month PromptMonth();
int PromptYearErase();

#endif // FUNCTIONS_HPP