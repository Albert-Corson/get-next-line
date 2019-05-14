#get-next-line
A recode of the [getline()](https://linux.die.net/man/3/getline) function in C

*This is a school project*

#### Description
The goal of this project was to recode the [getline](https://linux.die.net/man/3/getline) function, but with some limitations:
- Up to five functions of 20 lines or less were alowed
- The READ_SIZE had to be variable (defined in the header file)
- The only authorized functions were: [read](https://linux.die.net/man/2/read), [malloc](https://linux.die.net/man/3/malloc) and [free](https://linux.die.net/man/3/free)
- A static variable was alowed
- It had to be fast

#### How to test it
For testing purposes, a `main.c` file is in the project's repository in order to test the get_next_line() function.

First you need to compile the source files:
`gcc main.c get_next_line.c`

Then you can execute the `a.out` binary by giving it a text file as argument:
`./a.out file.txt`

It will may print ,on the standard output, the file's content line by line until there is nothing left to read.

You can easily change READ_SIZE by going into the header file `get_next_line.h` and changing it's value.