# c-password-generator
A atrong password generator made in C.

## Installation
To compile with GNU compiler, run the following command:
```
gcc -o passgen.exe passgen.c -lm
```

## Trouble-shooting
If you are running the program on the Linux command line and the special characters in the generated passwords do not print properly then you may not be using UTF-8 encoding in your Linux terminal. You can enable it by typing the following in the Linux command line:

```
export LANG=en_US.UTF-8
```