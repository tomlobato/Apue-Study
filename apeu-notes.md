1.2 UNIX Architecture
---------------------

In a strict sense, an operating system can be defined as the software that controls the hardware resources of the computer and provides an environment under which programs can run.

The interface to the kernel is a layer of software called the system calls


1.3 Logging in
---------------------

The shell is a special application that provides an interface for running other applications.

A shell is a command-line interpreter that reads user input and executes commands

The user input to a shell is normally from the terminal (an interactive shell) or sometimes from a file (called a shell script)


1.4 Files and Directories
---------------------

The only two characters that cannot appear in a filename are the slash character (/) and the null character

for portability, POSIX.1 recommends restricting filenames to consist of the following characters: letters (a-z, A-Z), numbers (0-9), period (.), dash (-), and underscore (_).

```c
#include <dirent.h>

DIR             *dp;
struct dirent   *dirp;

dp = opendir str
dirp = readdir dp
dirp->d_name
closedir dp
```

### SideNote: man

```
man on Research Unix, BSD, OS X and Linux:

Section	Description

1.	General commands
2.	System calls
3.	Library functions, covering in particular the C standard library
4.	Special files (usually devices, those found in /dev) and drivers
5.	File formats and conventions
6.	Games and screensavers
7.	Miscellanea
8.	System administration commands and daemons

layout:

NAME        The name of the command or function, followed by a one-line description of what it does.
SYNOPSIS    In the case of a command, a formal description of how to run it and what command line options it takes. For program functions, a list of the parameters the function takes and which header file contains its definition.
DESCRIPTION A textual description of the functioning of the command or function.
EXAMPLES    Some examples of common usage.
SEE ALSO    A list of related commands or functions.
```

1.5 Input and Output
---------------------

File descriptors are normally small non-negative integers that the kernel uses to identify the files accessed by a process. Whenever it opens an existing file or creates a new file, the kernel returns a file descriptor that we use when we want to read or write the file.

By convention, all shells open three descriptors whenever a new program is run: standard input, standard output, and standard error. If nothing special is done, as in the simple command ls then all three are connected to the terminal.

Unbuffered I/O is provided by the functions open, read, write, lseek, and close. These functions all work with file descriptors.

```c
int n;
char    buf[BUFFSIZE];
n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0
write(STDOUT_FILENO, buf, n) != n
```

The <unistd.h> header, included by apue.h, and the two constants STDIN_FILENO and STDOUT_FILENO are part of the POSIX standard

####Standard I/O

The standard I/O functions provide a buffered interface to the unbuffered I/O functions. Using standard I/O relieves us from having to choose optimal buffer sizes, such as the BUFFSIZE constant in Figure 1.4. The standard I/O functions also simplify dealing with lines of input (a common occurrence in UNIX applications).

The most common standard I/O function is printf. In programs that call printf, we’ll always include <stdio.h>

```c
int c;
while ((c = getc(stdin)) != EOF)
   if (putc(c, stdout) == EOF){
       printf("output error");
       exit(1);
}
```

1.6 Programs and Processes
--------------------------

####Program
A program is an executable file residing on disk in a directory. A program is read into memory and is executed by the kernel as a result of one of the seven exec functions.

An executing instance of a program is called a process,
Some operating systems use the term task to refer to a program that is being executed









