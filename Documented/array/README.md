# Experiment on array

## Purpose

To learn and understand: 
- Differences between array and pointer.
- Reason why array and address of the array has same value
- Ways of passing array to other functions
- Decaying of array to pointer
- Size of types

## Sources

- main.c
- analysis.h
- analysis.c

main.c including analysis.h

## Conclusion

int *a[]        -> int **

int *a[4]       -> int **

int a[][4]      -> int (*)[4]

int a[][]       -> Compile error

int (*a)[4]     -> int (*)[4]

int (*a)[]      -> Not good
