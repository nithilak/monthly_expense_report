#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <fstream>
#include <string>
#include <vector>

#include "constants.hpp"

//I don't use const iterators but maybe they could be implemented
//also perhaps there should be less copy and pasting in main and less repeated newlines

//using int vs unsigned for month and year
//std::chrono::year{int}; accepts an int but year.months[static_cast<unsigned int>(curr_month) - 1]; is an unsigned int cast function
//could be more instances

//bit inconsistent with naming month vs curr_month, year vs curr_year 
//for which one is the Month or Year and which is the std::chrono::month or std::chrono::year

//incosistent use of "\n" at the end of invalid rather than std::endl; but it's ok (got it from code written not by me)
//apparently std::endl is more expensive and slower 
//google says "You should use std::endl when you absolutely need to guarantee that the user or a file sees the text right now. "

// ++i vs i++, --i vs i--, got replaced a few to --i from i-- by code suggestions

//for (int i = 0; i < years.size() - 1; i++) {} turns out that calls the size function each time
//has been optimized

//See available years says "deleted" when the year is "erased" by function call

//currently after doing AddExpense and DeleteExpense in main the month file and the totals file are automatically updated
//could be changed

//can't figure out how to quit when in promptyear or promptmonth
//edit: feature has been added
//could have it based on whether the year returned was quit_year, but chose to use the std::pair to be explicit

//if you delete a month file while a session is in progress it will only be updated if you add/delete an expense
//perhaps I should add an option to update the file separately but the UI is already pretty full
//edit: added this feature, added a separate line in the UI for all update functions

//not my code, prints a csv file
void PrintFile(std::string filename);

//not my code, // Function to split a CSV line by commas
std::vector<std::string> parseCSVLine(const std::string& line);

//prints the menu for the UI
void PrintMenu();
void PrintMenuYear(std::chrono::year year);

//prints out all expenses for each month the year
void PrintAllExpenses(const Year& year);

//recalculates the year total by adding the total from each month. not my code
void RecalculateYearTotals(Year& year);

//prints out all expenses for the month
double PrintExpenses(const std::set<Expense>& expenses);
void PrintExpenses(const std::set<Expense>& expenses, const Month& month);
void PrintExpenses(const std::set<Expense>& expenses, const Month& month, std::chrono::year year);
void PrintExpenses(const Month& month);
void PrintExpenses(const Month& month, std::chrono::year year);
void PrintExpenses(const Year& year, std::chrono::month curr_month);

//reads in a csv file under the folder in includes/YEARExpenses/MONTHYEAR and uses it to fill month.expenses
//also updates each month and year total
double PopulateExpenses(const std::string& filename, Month& month);
double PopulateExpenses(const std::string& filename, Year& year, std::chrono::month curr_month);
double PopulateExpenses(Year& year);

//prints the year's total cost
void PrintAnnualTotal(const Year& year);

//inserts a year with all 12 month files formatted like includes/YEARExpenses/MONTHYEAR into years
//also TotalExpensesYEAR.csv
//creates directory and file if it does not exist
//if files are deleted after inserted, running InsertYear again creates the files fresh but the memory of the old file stays
Year& InsertYear(int year);

//adds an expense to a month
int AddExpense(Year& year, std::chrono::month curr_month);

//deletes an expense from a month
int DeleteExpense(Year& year, std::chrono::month curr_month);
int DeleteExpense(std::chrono::year year, Month& month);

//updates the month's csv file to match its data
//creates the file if it does not exist
int UpdateMonthFile(const Year& year, std::chrono::month curr_month);
//does not work for some reason
int UpdateAllMonthFiles(const Year& year);


//prints each total stored in each month and the year total
void PrintTotalsInternal(const Year& year);

//updates TotalExpensesYEAR.csv
//creates the file if it does not exist
int UpdateTotalsFile(const Year& year);
//prints TotalExpensesYEAR.csv
//creates the file if it does not exist via UpdateTotalsFile
int PrintTotalsFile(const Year& year);


//for these two I could make a quit option by implementing a default year

//returns a (prompted) year from years
//no quit option unless if no year exists and you choose not to insert one then it quits the whole program
std::pair<Year&, bool> PromptYear();
//returns a valid (prompted) month
//no quit option, has one that could be implemented to quit the whole program
std::pair<std::chrono::month, bool> PromptMonth();

//true if successfully inserted a (prompted) year into years, does not overwrite already inserted year
//has quit option
int PromptInsertYear();
//erases a (prompted) year in years
//has quit option
int PromptYearErase();

#endif // FUNCTIONS_HPP