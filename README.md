A list of all monthly expenses.

Press q to quit anytime and go back a level.

Insert year by adding a folder in includes with the title YEARExpenses.

Then insert each month in the folder under the title MmmYEAR.csv. 
The civ headers are cost,reason,date, as an example 500.34, "reason", 05 
(The automatic file creator writes the day in zero leading format upon a file update.)

Optionally insert TotalExpensesYEAR.csv in the folder with the csv header 
Jan,Feb,Mar,Apr,May,Jun,Jul,Aug,Sep,Oct,Nov,Dec,Total 
Total being the total for the year. 
This file is updated automatically upon inserting a year into the program.

If a directory, month, or totals file is not present when inserting a year, 
or it does not have the proper name, 
it will be created upon inserting a year. 
It will also be created/updated with new internally stored data when you run an update function.

After AddExpense and DeleteExpense are run 
the month file and the totals file are updated (see driver.cc).