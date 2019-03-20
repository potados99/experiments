# Experiment on C errorno

## Purpose 
C is a low level language. There are no exception handling in C. But errors occured in system calls must be catched.

To acheive it, C uses errorno.

In this experiment, we will see what errorno's are there, and how to get a string of it.

## Sources 
main.c

## Conclusion

Both "error.h" and "err.h" are helpful.

"error.h" is GNU extension. It has error resporting functions like "err_at_line".

"strerror" is at "string.h". It gives description for errorno. They are stored in static memory, roughly orderd.
