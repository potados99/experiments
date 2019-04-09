#ifndef conv_h
#define conv_h

/**
  * Convert string of digits to int.

  * @param num_out	Pointer to an integer to store result..
  			Result of strtol is stored to the number on successful work.
  * @return		Return value is zero on success.
  			On failure, it returns non-zero.
  */
int to_int(const char *digits, int base, int *num_out);

#endif /* conv_h */
