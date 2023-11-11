C project main ideas


Menu :
	Insert data -> adding transactions (income or expense)
	viewing transactions(all, and in a certain time space)
    viewing account amount
	exit
 	
	using gtk




Data:

	struct type list -> date, description, ammount, type (income or expense)
	Store the data in a file, to be accessed between runs
	Assure that the input data is valid

Functions:

	1. record new transaction
	2. calculate the account balance (starting from 0 and adding and subtracting )
	3. display a list of previous transactions
	4. a function that generates a simple financial report, such as a summary of income and expenses for a specific period


Possible errors and personal tweaks:

Always store in memory the current ammount of money in the account so that it never goes below 0
Always make sure that the input data is good, int is int and char is char, make them repeat after every valuable in the struct, rather than the whole struct
When introducing a possible older transaction insert it into the list in its cronological position, by comparing with every element on its way. 
(maybe even binary search, but seems like over kill)
Maybe find out if its posible to make a table when showing the values 


TO DO:
play a bit and find errors
maybe make it into a program
a presentation