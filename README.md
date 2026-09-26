A list of all monthly expenses.  

do:  

`make`  

`clear` (optionally)  

`./bin/exec`  

to run the program.  

Press q to quit anytime and go back a level.  
(Except for when prompted for a text entry.)  

Insert year by adding a folder in includes with the title YEARExpenses.  
(The automatic file creator writes the year with a 4 leading zero format.)  

Then insert each month in the folder under the title MmmYEAR.csv.  
The csv headers are cost,reason,day, for example 500.34,"reason",05  
(The automatic file creator writes the day in a zero leading format upon a file update.)  
(The program does not accept an empty/whitespace only reason and will not add that expense to memory.)

Optionally insert TotalExpensesYEAR.csv in the folder with the csv header  
Jan,Feb,Mar,Apr,May,Jun,Jul,Aug,Sep,Oct,Nov,Dec,Total  
Total being the total for the year.  
This file is updated automatically upon inserting a year into the program.  

If a directory, month file, or totals file is not present when inserting a year, 
or it does not have the proper name, 
it will be created upon inserting a year. 
It will also be created/updated with new internally stored data when you run an update function.  

After AddExpense and DeleteExpense are run 
the month file and the totals file are automatically updated (see driver.cc).  

Note: Inserting a year after it has already been inserted will overwrite the data in memory with the data in the csv file.  
