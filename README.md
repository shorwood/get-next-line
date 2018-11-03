## get_next_line
## Reading a line on a fd is way too tedious

# get_next_line
The aim of this project is to make you code a function that returns a line
ending with a newline, read from a file descriptor

# Introduction

# Objectives
 - This project will not only allow you to add a very convenient function to your collection, but it will also allow you to learn a highly interesting new concept in C programming: static variables.

- You will also gain a deeper understanding of allocations, whether they happen on the stack memory or in the heap memory the manipulation and the life cycle of a buffer, the unexpected complexity implied in the use of one or many static variables.

- Your respect of the Norm will improve the rigor of your programming. We also suspect that your approach to coding will change when you will discover that the initial state of a variable in a function can vary depending on the call of that very function.

# Mandatory
- Write a function that returns a line read from a file descriptor.

- What we call a “line” is a succession of characters that end with ’\n’ (ascii code 0x0a) or with End Of File (EOF).
[X]

# Bonus
The project get_next_line is straight forward and leaves very little room for bonuses, but I am sure that you have a lot of imagination. If you ace perfectly the mandatory part, then by all means complete this bonus part to go furher. I repeat, no bonus will be taken into consideration if the mandatory part isn’t perfect.
- To succeed get_next_line with a single static variable.
- To be able to manage multiple file descriptor with your get_next_line. For example, if the file descriptors 3, 4 and 5 are accessible for reading, then you can call get_next_line once on 3, once on 4, once again on 3 then once on 5 etc. without losing the reading thread on each of the descriptors.
[X]

# Final Mark
