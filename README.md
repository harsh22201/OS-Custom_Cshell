# OS-Custom_Cshell
Making a special unix system, with three specific commands for c shell (c program that acts as a shell for your system) to be used in it.

1) word: It is a built-in (internal) command, Reads the number of words (assume word is a “space-separated” string) in a text file, and throws an error if the file does not exist.
   
Syntax: word [-option] [file_name]

Note: if no option is passed then there should be only one file, the number of files may vary as per option and the same would reflect in syntax .
It should additionally also cater 2 options:

-n : ignores new line character

-d : difference between the word sizes of two text files

Note: Only one of the options (-n or -d) can be used at a time with the word command.

2) dir: It creates a directory, and then changes the path to that directory. It is an external command, throw an error if that directory already exists.

Syntax: dir [-option] [dir_name]

It should additionally also cater 2 options:

-r : removes if the directory already exists and create a new directory instead of throwing an error  

-v : print a message for each step in the running of this command

3) date: It returns the last modified date and time of a particular file.  It is an external command

Syntax: date [-option] [file_name]

It should additionally also cater 2 options:

-d : display time described by STRING 

-R : output date and time in RFC 5322 format


