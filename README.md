C Project by Malos Alexandru-Razvan Informatica engleza

The project opens with a menu consisting of 4 options: Insert, Show all transactions, Show transactions in a time period, Show the account balance
The whole GUI was made using the gtk library and the Glade application. For help I used the official gtk website documentation:
				https://docs.gtk.org/gtk3/
and multiple tutorials on youtube and standalone sites for making a first GUI, which I then used as a refference for this project

1. Inserting data:

	For inserting the data I use a popup called insert_popup, that appears when I press the first button, which has 6 labels and textentries and 6 other labels for errors
	While at the bottom there is a locked submit button and an exit button.
		For storing data, I used a file "data_storage.txt" in which I stored data in the form:
	year month day details ammount type
	which is then read from the file in a struct data type that contains all 6 datas.
	I store all the data while the program is running in a struct array, which has a maximum size of 1001 elements.

Saving the data:
		For saving the data, I just append the currently imputed struct to the end of the folder. While storing the data in ascending order in the file might seem
	a better choice, I had to take into account the fact that I had to insert the element into the folder every time I inserted one, thus the process becoming reduntant 
	and posing a possible storaging problem. By appending the element instantly after inputing it and pressing submit, that inserted data is protected from getting lost
	in case the user presses exit, and also makes the saving easy

Loading the data:
		When the program starts, the data from the file is read adn stored in the array, and while it's stored, we also calculate the current ammount, so we know it at all times

Error checking:
	By far the most complex part of the insert and the whole code, are the functions that check that the data is correctly imputed.
For every data I had to check that: it's the correct type, it's within a certain bound(year between 1960 and 2024, month between 1 and 12, day between 1 and 28,29,30,31, depending on
the month and year) and that it also made sense (if the type is expense but the ammount is bigger than the current ammount, the user can't submit the data)
	The most unique part of my code is how I handled the errors. Instead of letting the user press submit and crashing the program or the insert_popup, I lock the submit button, making it
available only when all 6 datas are correct. If a data is not correct, I show next to it feedback on what's wrong with the data inserted and if it's correct I show a checkmark.
The data is checked at every input(digit, letter) thus making it very efficient and user friendly

2. Showing all transactions:
	For showing the data I use a popup called show_popup which is just a text_view with an exit button at the bottom. It shows the data in the order it was inputed, without sorting it since
it was not asked and it seems more beneficial to the user to show it in this order. (Note: after a certain time the user will most likely enter only current transactions, since entering old ones won't make that much sense)

3. Show transactions in a time period:
	For showing the transactions in a certain time period, I first show the user an period_popup that's very similar to the insert_popup, but this time has 2 dates to input(day month year
so 6 in total as well) with pretty similar functions for checking for errors, but this time I also check that the first date is smaller than the second one. After the data is correctly inputed and the show button appears, the show_popup opens again and shows the transactions for that time

4. Show the account balance:
	For showing the account balance, I keep a curAmount at all times that keeps track of the account balance, and when the 4th button is pressed, a dialog is opened which shows the balance

All the functions are declared in library.h, along with the buttons and labels and the functions are constructed in library.c, later to be called in main.c when pressing a button or making a change in text entry

All the widgets used in this program are: buttons, labels, text_entries, text_views while as a storage of widgets I used boxes, grids and for the popups I used windows or dialogs

TODO:
-make the ammount be stored in float of only 2 zecimals
-try and put some colors in the program
-if able to put colors, should write the errors with red and checkmark with green
-optional: sort the transactions before showing (harder for period, so maybe just sort them when I load them and then insert at given space)
