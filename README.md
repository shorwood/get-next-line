# Summary
The aim of this project is to make you code a function that returns a line
ending with a newline, read from a file descriptor

# Introduction
- You are now starting to understand that it will get tricky to read data from a file descriptor if you don’t know its size beforehand. What size should your buffer be? How many times do you need to read the file descriptor to retrieve the data ?

- It is perfectly normal and natural that, as a programmer, you would want to read a “line” that ends with a line break from a file descriptor. For example each command that you type in your shell or each line read from a flat file.

- Thanks to the project get_next_line, you will finally be able to write a function that will allow you to read a line ending with a newline character from a file descriptor. You’ll be able to add this function to your libft if you feel like it and most importantly, use it in all the future projects that will require it.

 - This project will not only allow you to add a very convenient function to your collection, but it will also allow you to learn a highly interesting new concept in C programming: static variables.

- You will also gain a deeper understanding of allocations, whether they happen on the stack memory or in the heap memory the manipulation and the life cycle of a buffer, the unexpected complexity implied in the use of one or many static variables.

- Your respect of the Norm will improve the rigor of your programming. We also suspect that your approach to coding will change when you will discover that the initial state of a variable in a function can vary depending on the call of that very function.

# Objective
- [x] Write a function that returns a line read from a file descriptor.

- [x] What we call a “line” is a succession of characters that end with **’\n’** (ascii code 0x0a) or with **End Of File (EOF)**.

- [x] Your function must be prototyped as follow :
```c
int get_next_line(const int fd, char **line);
```

- The first parameter is the file descriptor that will be used to read.

- The second parameter is the address of a pointer to a character that will be used to save the line read from the file descriptor.

- The return value can be **1, 0 or -1** depending on whether a line has been read, when the reading has been completed, or if an error has happened respectively.

- Your function **get_next_line** must return its result __without__ **’\n’**.

- Calling your function **get_next_line** in a loop will then allow you to read the text available on a file descriptor one line at a time until the end of the text, no matter the size of either the text or one of its lines.

- Make sure that your function behaves well when it reads from a file, from the standard output, from a redirection etc.

- In you header file get_next_line.h you must have at least the prototype of the function **get_next_line** and a macro that allows to choose the size of the reading

# Bonus
The project get_next_line is straight forward and leaves very little room for bonuses, but I am sure that you have a lot of imagination. If you ace perfectly the mandatory part, then by all means complete this bonus part to go furher. I repeat, no bonus will be taken into consideration if the mandatory part isn’t perfect.
- [X] To succeed get_next_line with a single static variable.
- [X] To be able to manage multiple file descriptor with your get_next_line. For example, if the file descriptors 3, 4 and 5 are accessible for reading, then you can call get_next_line once on 3, once on 4, once again on 3 then once on 5 etc. without losing the reading thread on each of the descriptors.

# Final Mark
__Awaiting Evaluation__