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

//for the dirPath I wanted to use the file path, but that doesn't work when I do it the fancy way or use substring (0, filename.size() - number)
// std::filesystem::path p(filename);
// std::string dirPath = p.parent_path().string();
//std::string dirPath = filename.substr(0, filename.size() - 11 or 12 for month file or 21 or 22 for totals file); idk
//now I am doing it with SplitPath() but it could be done better I think
//like with reason.find_first_not_of("/")
//also the error handling for not being able to open the file seems off somehow, ctrl+f dirPath to find all instances of this
//PopulateExpenses(const std::string& filename, Month& month), UpdateMonthFile(const Year& year, std::chrono::month curr_month), UpdateTotalsFile(const Year& year)
//the only way it could fail that I can see is if SplitPath() doesn't return a valid file path in the vector
//or this, this is weird
// if (!std::filesystem::exists(filename)) {
//     std::cerr << paths[1] << " file not found. Creating file..." << std::endl;
// }

// // 1. Open the CSV file using an input file stream
// std::ofstream file(filename);

// // Best Practice: Always check if the file opened successfully
// if (!file.is_open()) {
//     std::cerr << "Error: Could not open the file!" << std::endl;
//     return 0;
// }

//could preface error messages with "Error: " like the computer code
//also std::cout vs std::cerr in some cases, up to discretion

//also could add errors for reaching unreachable places? like after a while loop with std::getline
//currently returning the quit option in those cases

//bit inconsistent with naming month vs curr_month, year vs curr_year 
//for which one is the Month or Year and which is the std::chrono::month or std::chrono::year

//incosistent use of "\n" at the end of invalid rather than std::endl; but it's ok (got it from code written not by me)
//apparently std::endl is more expensive and slower 
//google says "You should use std::endl when you absolutely need to guarantee that the user or a file sees the text right now. "

// ++i vs i++, --i vs i--, ++iter vs iter++, --iter vs iter--
//got replaced few i-- to --i by code suggestions

//for (int i = 0; i < years.size() - 1; i++) {} turns out that calls the size function each time
//has been optimized



//See available years says "deleted" when the year is "erased" by function call

//added audit files, and is "deleted" the correct term for removing an expense?

//could change the directory from "./includes" to its own folder

//some things are created as a variable, std::string date = thing; for example which I think is for readability
//when it could be passed directly, which it is done sometimes

//not added feature
// std::cout << "Update all month files and total files for all years: 11" << std::endl; 
//at this point the UI needs a sub menu if totals and years are to be separate
//this just makes the UI too cluttered
//plus what are you doing that needs this feature????
//the months get updated automatically so unless you deleted a whole bunch of them at once?
//but I mean it's kinda simple
// for (const Year& year : years) {
//     UpdateAllMonthFiles(year);
//     UpdateTotalsFile(year);
// }

//also not added feature
//print all the annual totals for all years
// for (const Year& year : years) {
//     PrintAnnualTotal(year);
// }
//or print it more in the style of PrintTotalsInternal(year)
//for each block go until 6 are printed or whatever is left is printed
// void PrintTotalsInternalYears(const Year& year) {
//     std::cout << std::string(colWidth * 6, '-') << "\n";

//     auto iter = years.begin();
//     auto iter2 = years.begin();

//     double total = 0;

//     while (iter != years.end() && iter2 != years.end()) { //should have the same value

//         std::cout << std::left;
//         for (unsigned i = 0; i < 6 && iter != years.end(); ++i) {
//             std::cout << std::setw(colWidth) << std::format("{}", iter->first);
//             iter++;
//         }
//         std::cout << std::endl;

//         std::cout << std::left;
//         for (int i = 0; i < 6 && iter2 != years.end(); ++i) {
//             double num = iter2->second.total;
//             std::cout << std::setw(colWidth) << num;
//             total += num;
//             iter2++;
//         }
//         std::cout << std::endl;

//     }

//     std::cout << std::string(colWidth * 6, '-') << "\n";
//     std::cout << "Total: \n" << total << std::endl;
//     std::cout << std::string(colWidth * 6, '-') << "\n" << std::endl;
// }
//then print the total over all the years
//not going to print the total over all the years
//we're getting into data science territory at this point
//what next? display it on a graph? calculate the average trends and spending habits?

//curently year Zero (0) is allowed to be created and is processed when stored as a directory 
//(when properly named, the directory would be 0000Expenses) 
//(and that is what it checks for, although I think 0Expenses also works but it writes to 0000Expenses when uploading
//as per the naming convention that I made for all years less than 4 digits) (not my convention really, it is the default printing of std::chrono::year)
//I could add YEARExpensesBCE
//oh wait hold on, google says
//In C++20, std::chrono::year stores BCE years using negative values and astronomical year numbering, where the year N BCE is represented mathematically as 1 - N.Because of this system, there is a year 0 in std::chrono::year, which corresponds exactly to 1 BCE in the traditional historical calendar.
//theoretically negative number years should work now
//if you really want to enter or choose the year 0, you have to enter the word "zero"

//there is no 0 shortcut for PromptYearErase() because why would you want to delete the most recent year
//and having 0 choose the least recent year would 
//be confusing because 0 always means most recent year or all available years in “./includes/”

//there is a naming difference between PromptYearErase() and PromptInsertYear()

//currently there is an option in PromptInsertYear() to include all years in directory "./includes/"
//the UI is a bit cluttered for when new files are created

//running InsertYear again overwrites what is stored in memory
//it also reinserts the filename into month, not too much overhead so I don't think this is a big deal
//it acts as if creating the year from scratch
//could change the behavior to not do that using result.second
// auto result1 = myMap.insert({1, "Apple"});
// std::cout << std::boolalpha;
// std::cout << result1.second << "\n"; // Prints: true
//from google:
//true: The key was not in the map yet. The new item was added.
//false: The key was already in the map. No new item was added, and the old value stayed the same.
//but keeping this behavior allows changes from both directions without complicating the UI
//it is risky to run insert all years though (especially with the 0 shortcut button), so the user needs to be careful
//but if you don't delete the files and re-add different ones it should be ok with the automatic updates

//can't decide the insert year behavior in PromptYear()
//current behavior is the best to not have a crowded UI, unless you also want to remove the handholding insert year y or n option
//which is arguably better and has a cleaner UI

//currently expenses are stored under a multiset so that duplicate equal elenents could be added
//could change it so that elements can't be equal but that doesn't make sense

//it is possible for an expense to be 0

//AddExpense and DeleteExpense have one long continuous text when selecting no until you select yes or quit

//currently after doing AddExpense and DeleteExpense in main the month file and the totals file are automatically updated
//and main prints that the file is is updated
//could be changed
//the audit files are also automatically updated but main does not print that the file is updated

//AddExpense does not permit you to enter an empty reason or whitespace reasonn currently 
//if the reason is empty/whitespace in the CSV file when you read it in with PopulateExpenses, 
//PopulateExpenses throws an error that is caught and displayed and it does not add that specific expense
//it also does not permit you to enter "q" since "q" is the quit option
//but you can enter "q " or just any q with whitespace 
//and it can read "q" from the csv file
//csv with newlines in the reason field throws an error and does not add that specific expense
//because the csv is read with std::getline so the message gets cut
//adding support for newlines in the reason field would require a modified parsing function to replace getline to parse double quotes

//I wrote a helper function to parse the csv for writing, but now I am using std::quoted 
//I am using a helper function for reading to parse inside the double quotes
//I tried to use std::quoted for writing but it doubled the quotes at the end so I just write the small code myself
//but then it turned out that the error was me adding quotes outside of the quote function 
//so I removed those extra quotes and it worked

//press q anytime to go back a level

//can't figure out how to quit when in promptyear or promptmonth
//edit: feature has been added
//could have it based on whether the year returned was quit_year, but chose to use the std::pair to be explicit

//if you delete a month file while a session is in progress it will only be updated if you add/delete an expense
//perhaps I should add an option to update the file separately but the UI is already pretty full
//edit: added this feature, added a separate line in the UI for all update functions

//see dirPath discussion above
//currently it should be safe to run the update functions because the month.filename paths and totals file path 
//are created with code, (somewhere earlier in the code, I think PopulateExpenses and UpdateTotalsFile, 
//and PrintTotalFile calls UpdateTotalsFile if the file cannot be opened but has been replaced with PrintTotalsInternal)
//but if not you might want to run a try catch block around the function, though at that point you can't guarantee if anything changed or not


//all print functions after PrintMenuYear and AddExpense and DeleteExpense print a newline at the end
//PromptInsertYear and PromptYear and PromptMonth functions do not print a newline at the end

//not my code, prints a csv file
void PrintFile(std::string filename);

//not my code, // Function to split a CSV line by commas
std::vector<std::string> parseCSVLine(const std::string& line);

//not my code, but I edited it to not push to a vector 
// Parses a single CSV line, handling backslash escapes (\"), doubled quotes (""), and embedded commas
//originally called parseCSVLine
std::vector<std::string> parseCSVLine2(const std::string& line);

//only parses one set of quotes, assumed to be quoted when you enter
//couldn't use this because it removed the "day" part
//so I made it return the rest as the second part of the vector
std::vector<std::string> parseCSVLine3(const std::string& line);

//like 3 but it modifies line
std::string parseCSVLine5ChangeLine(std::string& line);

//like 2 but it only prints an error message if more than one set of quotes was traversed
std::vector<std::string> parseCSVLine4(const std::string& line);

//changes every " to "" and surrounds the string with double quotes
//essentially the same as std::quoted(line, '"', '"')
std::string MakeQuoted(const std::string& line);

//returns the parent path of the input string by checking for the last instance of "/"
std::string ReturnDirPath(const std::string& filename);

//returns the parent path of the input string by checking for the last instance of "/" as the first entry
//returns the rest as the second entry
std::vector<std::string> SplitPath(const std::string& filename);

//prints the menu for the UI
void PrintMenu();
void PrintMenuYear(std::chrono::year year);

//prints all the available year numbers in years
void PrintAvailableYears();

//prints out all expenses for each month the year
void PrintAllExpenses(const Year& year);

//recalculates the year total by adding the total from each month. not my code
void RecalculateYearTotals(Year& year);

//prints out all expenses for the month
//non void function returns the total for the expenses
double PrintExpenses(const std::multiset<Expense>& expenses);
void PrintExpenses(const Month& month);
// void PrintExpenses(const Month& month, std::chrono::year year); //nice but unsafe
void PrintExpenses(const Year& year, std::chrono::month curr_month);

//reads in a csv file under the folder in includes/YEARExpenses/MONTHYEAR and uses it to fill month.expenses
//creates the file and directory if it does not exist
//updates month total and returns it
double PopulateExpenses(const std::string& filename, Month& month);
//deprecated by being skipped over
//runs PopulateExpenses for that month and updates the year total
double PopulateExpenses(const std::string& filename, Year& year, std::chrono::month curr_month);
//runs PopulateExpenses for each month in the year and updates the year total
//returns the year's total
double PopulateExpenses(Year& year);

//prints the year's total cost
void PrintAnnualTotal(const Year& year);

//inserts a year with all 12 month files formatted like includes/YEARExpenses/MONTHYEAR.csv into years
//also updates includes/YEARExpenses/TotalExpensesYEAR.csv
//creates directory and file if it does not exist
//running InsertYear again overwrites what is stored in memory
Year& InsertYear(int year);

//not my code
//returns whether a string is empty/whitespace
bool is_empty_or_whitespace(const std::string& s);

//adds an expense to a month, returns 1 if made a change
int AddExpense(Year& year, std::chrono::month curr_month);

//deletes an expense from a month, returns 1 if made a change
int DeleteExpense(Year& year, std::chrono::month curr_month);
//deletes an expense from a month, returns month total if made a change
double DeleteExpense(std::chrono::year year, Month& month);

//updates the month's csv file to match its data
//creates the directory and file if it does not exist
//returns 1 if updated the file successfully
int UpdateMonthFile(const Year& year, std::chrono::month curr_month);
//does not work for some reason
//supposed to return number of successfully updated files
int UpdateAllMonthFiles(const Year& year);


//prints each total stored in each month and the year total
void PrintTotalsInternal(const Year& year);

//updates TotalExpensesYEAR.csv
//creates the directory and file if it does not exist
//returns 1 if updated the file successfully
int UpdateTotalsFile(const Year& year);
//prints TotalExpensesYEAR.csv
//creates the directory and file if it does not exist via UpdateTotalsFile
//returns 1 if csv file was opened and had both header not empty and values not empty
int PrintTotalsFile(const Year& year);


//updates TotalExpensesYEAR.csv
//creates the directory and file if it does not exist
//returns 1 if updated the file successfully
int UpdateAuditFileByFilename(std::string filename, char sign, const Expense& expense, std::chrono::year year, std::chrono::month month);
int UpdateAuditFile(char sign, const Expense& expense, std::chrono::year year, std::chrono::month month);
int UpdateMonthAuditFile(char sign, const Expense& expense, std::chrono::year year, std::chrono::month month);
int UpdateYearAuditFile(char sign, const Expense& expense, std::chrono::year year, std::chrono::month month);

//creates the directory and file if it does not exist
//returns 1 if updated the file successfully
int CreateAuditFile(const std::string& filename);
int CreateAuditFile();
int CreateMonthAuditFile(std::chrono::year year, std::chrono::month month);
int CreateYearAuditFile(std::chrono::year year);

// Print the entire file contents to the console
int PrintFile2(std::string filename);
int PrintAuditFile();
int PrintMonthAuditFile(std::chrono::year year, std::chrono::month month);
int PrintYearAuditFile(std::chrono::year year);


//for these two I could make a quit option by implementing a default year

//returns a (prompted) year from years
//if no year exists and you choose not to insert one then it returns quit option
//bool is false if quit option is desired, not a valid year
std::pair<Year&, bool> PromptYear();
//returns a valid (prompted) month
//bool is false if quit option is desired, not a valid month
std::chrono::month PromptMonth();

//returns the number of years inserted if chose to insert all years, else
//returns 1 if successfully inserted a (prompted) year into years, does not overwrite already inserted year
//has quit option
int PromptInsertYear();
//erases a (prompted) year in years
//returns 1 if erased a year
//has quit option
int PromptYearErase();

#endif // FUNCTIONS_HPP