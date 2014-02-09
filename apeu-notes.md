1.2 UNIX Architecture
=====================

In a strict sense, an operating system can be defined as the software that controls the hardware resources of the computer and provides an environment under which programs can run.

The interface to the kernel is a layer of software called the system calls


1.3 Logging in
==============

The shell is a special application that provides an interface for running other applications.
A shell is a command-line interpreter that reads user input and executes commands
The user input to a shell is normally from the terminal (an interactive shell) or sometimes from a file (called a shell script)


1.4 Files and Directories
=========================

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

--- MAN ---
man on Research Unix, BSD, OS X and Linux:

Section	Description
*1	General commands
*2	System calls
*3	Library functions, covering in particular the C standard library
*4	Special files (usually devices, those found in /dev) and drivers
*5	File formats and conventions
*6	Games and screensavers
*7	Miscellanea
*8	System administration commands and daemons

layout:
NAME 		The name of the command or function, followed by a one-line description of what it does.
SYNOPSIS	In the case of a command, a formal description of how to run it and what command line options it takes. For program functions, a list of the parameters the function takes and which header file contains its definition.
DESCRIPTION A textual description of the functioning of the command or function.
EXAMPLES 	Some examples of common usage.
SEE ALSO
---

1.5 Input and Output
====================



