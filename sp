COP 3502 - Programming Assignment #5

Assigned: 7/15/10 (Thursday)
Due: 7/29/10 (Thursday) at 11:55 PM WebCourses time

Objective
1. Learn how to utilize binary search trees.

Problem: Spell Checker 
A simple approach to writing a spell checker is to store the correct spellings of every known word in a binary search tree. Any words not appearing in the binary search tree, then, are considered to be incorrectly spelled. For this assignment, you must write such a spell checker.

You must have two functions that act on your binary search tree. Your insert function should take in a string and a tree node, and insert the word represented by that string into the tree rooted at that node. You should use the strcmp function in string.h to compare words. Your search function should take in a string and a tree node and should return a value indicating whether or not the word is present in the tree rooted at that node.
	
A binary search tree by itself is all well and good, but it’s not a spellchecker. You must use the BST to implement a spellchecker. First, you must read in a dictionary file specified by the user. The dictionary should just be a flat text file containing all words that are recognized. An appropriate dictionary file is provided on WebCourses as part of this assignment. Then, the program should read in a text file to spellcheck, also specified by the user. For each word in the text file that isn’t recognized, print the word and the line it was found on to the screen (hint: use the fgets function to read entire lines at once). You may assume that the file being checked will only contain alphanumeric characters, whitespace (including ‘\n’, ‘\r’, and ‘\t’), and the following punctuation characters: 
~!@#$%^&*()-_=+[]{}\|;:’”,.<>/?
Some of those characters need escape sequences, so be careful when you type them in to your program. Any contiguous string of alphanumeric characters should be viewed as being a word. You should treat punctuation characters as being equivalent to whitespace for the purposes of this assignment (hint: use the strtok function in string.h). Note that the rules above prevent contractions from being recognized as words. This is okay for the purposes of this assignment.
	
Regarding the dictionary, any word that is capitalized should be considered a proper name. Thus, if the word “Douglass” is in the dictionary, “douglass” should be considered to be misspelled because the first letter must be capitalized. On the other hand, the English language allows the first letter of normal words to be capitalized. Thus if the word “computer” is in the dictionary, then both “computer” and “Computer” should be considered to be spelled correctly. In other words, if you are trying to spellcheck a word that begins with a capital letter, your program should search in the binary search tree for both that word exactly, and that word except with the first character lowercase before deciding that it’s misspelled. If you are trying to spellcheck a word that begins with a lowercase letter, then your program should only check for the presence of that exact word. Since a normal alphabetical listing of words would result in an extremely skewed binary tree, the order of words in the provided dictionary file will be jumbled. Additionally, the provided dictionary is far from complete and some common words may be absent. Be sure that a given word is actually present in the dictionary before you reach the conclusion that your program is incorrectly recognizing that word as misspelled.

Sample run (User input in italics, program output in bold)
What is the name of your dictionary file?
dictionary.txt
What is the name of the text file you wish to spellcheck?
text.txt
The following words were not recognized:
Line 5 - compter
Line 8 - sciance
Line 23 – oone
Line 28 – discreate
Line 28 - sturctres

Deliverables
You must submit the source code (The .c file, not the .exe file) for this program over WebCourses by 11:55 PM on Thursday, July 29th, 2010.  You must send your source file as an attachment using the "Add Attachments" button. Assignments that are e-mailed or typed into the submission box will not be accepted. 

Restrictions
Your program must compile using Dev-C++. It’s okay to develop your program using the IDE of your choice, but make sure that it will compile under Dev-C++. Your program should include a header comment with the following information: your name, course number, section number, assignment title, and date. Also, make sure you include ample comments throughout your code describing the major steps in solving the problem.

Grading Details
Your program will be graded upon the following criteria:

1) Correctness
2) Your programming style, comments, and use of white space. (Even if you have a plan and your program works perfectly, if your programming style is poor or your use of white space is poor you could get 10% or 15% deducted from your grade. We won’t be super-picky on this point, but your code should look reasonable.)
3) Use of binary search trees. This functionality could be implemented any number of ways, but the purpose of this assignment is to learn about binary search trees, so you must implement one for this program.
