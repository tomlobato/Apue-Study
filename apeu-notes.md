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

The UNIX System guarantees that every process has a unique numeric identifier called the process ID. The process ID is always a non-negative integer.

####Process Control
There are three primary functions for process control: fork, exec, and waitpid. (The exec function has seven variants, but we often refer to them collectively as simply the exec function.)

####shell1.c
```c
#include "apue.h"
#include <sys/wait.h>

int
main(void)
{
	char	buf[MAXLINE];	/* from apue.h */
	pid_t	pid;
	int		status;

	printf("%% ");	/* print prompt (printf requires %% to print %) */
	while (fgets(buf, MAXLINE, stdin) != NULL) {
		if (buf[strlen(buf) - 1] == '\n')
			buf[strlen(buf) - 1] = 0; /* replace newline with null */

		if ((pid = fork()) < 0) {
			err_sys("fork error");
		} else if (pid == 0) {		/* child */
			execlp(buf, buf, (char *)0);
			err_ret("couldn't execute: %s", buf);
			exit(127);
		}

		/* parent */
		if ((pid = waitpid(pid, &status, 0)) < 0)
			err_sys("waitpid error");
		printf("%% ");
	}
	exit(0);
}
```

```c
	pid_t fork(void):
		0: child.
		>0: parent, with pid_t being the child pid

	int execlp(const char *path, const char *arg0, ..., NULL);
	/* http://support.sas.com/documentation/onlinedoc/sasc/doc/lr2/execlp.htm :
	Like all of the exec functions, execlp replaces the calling process image with a new process image. This has the effect of running a new program with the process ID of the calling process. Note that a new process is not started; the new process image simply overlays the original process image. The execlp function is most commonly used to overlay a process image that has been created by a call to the fork function.*/

	pid_t waitpid(pid_t pid, int *stat_loc, int options);
```

We use the standard I/O function fgets to read one line at a time from the standard input. When we type the end-of-file character (which is often Control-D) as the first character of a line, fgets returns a null pointer, the loop stops, and the process terminates.

We call fork to create a new process, which is a copy of the caller. 

Then fork returns the non-negative process ID of the new child process to the parent, and returns 0 to the child.

Because fork creates a new process, we say that it is called once by the parent but returns twice, in the parent and in the child.

In the child, we call execlp to execute the command that was read from the standard input. This replaces the child process with the new program file. 

The combination of fork followed by exec is called spawning a new process on some operating systems.

Because the child calls execlp to execute the new program file, the parent wants to wait for the child to terminate. This is done by calling waitpid, specifying which process to wait for: the pid argument, which is the process ID of the child.

####Threads and Thread IDs

Usually, a process has only one thread of control, one set of machine instructions executing at a time. 

Some problems are easier to solve when more than one thread of control can operate on different parts of the problem. 

Additionally, multiple threads of control can exploit the parallelism possible on multiprocessor systems.

All threads within a process share the same address space, file descriptors, stacks, and process-related attributes. Each thread executes on its own stack, although any thread can access the stacks of other threads in the same process. 

Because they can access the same memory, the threads need to synchronize access to shared data among themselves to avoid inconsistencies.

Like processes, threads are identified by IDs. Thread IDs, however, are local to a process. A thread ID from one process has no meaning in another process. We use thread IDs to refer to specific threads as we manipulate the threads within a process.

Functions to control threads parallel those used to control processes


1.7 Error Handling
------------------

When an error occurs in one of the UNIX System functions, a negative value is often returned, and the integer errno is usually set to a value that tells why.

in an environment that supports threads, the process address space is shared among multiple threads, and each thread needs its own local copy of errno to prevent one thread from interfering with another. Linux, for example, supports multithreaded access to errno by defining it as
	extern int *__errno_location(void); #define errno (*__errno_location())

errno. First, its value is never cleared by a routine if an error does not occur.
the value of errno is never set to 0 by any of the functions, and none of the constants defined in <errno.h> has a value of 0.

```c
char *strerror(int errnum); // maps errnum into an error message string and returns a pointer to the string.
void perror(const char *msg); // produces an error message on the standard error, based on the current value of errno, and returns.
```

1.8 User Identification
-----------------------

With every file on disk, the file system stores both the user ID and the group ID of a file’s owner.

Storing both of these values requires only four bytes, assuming that each is stored as a two-byte integer. 

####Supplementary Group IDs

These supplementary group IDs are obtained at login time by reading the file /etc/group and finding the first 16 entries that list the user as a member.

POSIX requires that a system support at least 8 supplementary groups per process, but most systems support at least 16.

1.9 Signals
-----------

Signals are a technique used to notify a process that some condition has occurred.

#####man signal
#####man kill

####shell2.c

```c
#include "apue.h"
#include <sys/wait.h>

static void	sig_int(int);		/* our signal-catching function */

void
sig_x(int x)
{
	printf("received signal %d\n", x);
}

int
main(void)
{
	char	buf[MAXLINE];	/* from apue.h */
	pid_t	pid;
	int		status;

	if (signal(SIGINT, sig_int) == SIG_ERR)
		err_sys("signal error");

	for(int x = 1; x<32; x++){
		printf("%d\n", x);
		if (x != 9 && x != 17){
			if (signal(x, sig_x) == SIG_ERR)
				err_sys("signal error");		
		}
	}

	printf("pid %d\n", getpid());

	printf("%% ");	/* print prompt (printf requires %% to print %) */
	
	while (fgets(buf, MAXLINE, stdin) != NULL) {
		if (buf[strlen(buf) - 1] == '\n')
			buf[strlen(buf) - 1] = 0; /* replace newline with null */

		if ((pid = fork()) < 0) {
			err_sys("fork error");
		} else if (pid == 0) {		/* child */
			execlp(buf, buf, (char *)0);
			err_ret("couldn't execute: %s", buf);
			exit(127);
		}

		/* parent */
		if ((pid = waitpid(pid, &status, 0)) < 0)
			err_sys("waitpid error");
		printf("%% ");
	}
	exit(0);
}

void
sig_int(int signo)
{
	printf("interrupt\n%% ");
}
```

####testing signals
```c
#include "stdio.h"
#include "stdlib.h"
#include <unistd.h>
#include <signal.h>
#include "sys/wait.h"

int main() 
{
	int pid;
	int status;
	int tf = 10000;

	for(int sig = 1; sig < 32; sig++) 
	{
		// printf("--- sig %d\n", sig);

		if ((pid = fork()) < 0) 
		{
			printf("fork error.\n");
			exit(1);

		} else if (pid == 0) /* child */
		{ 
			// printf("mypid %d\n", getpid());
			// usleep(2*tf);
			printf("sig %d didnt killed me\n", sig);
			exit(0);
		}
		
		// parent
		// usleep(1*tf);
		if ((kill(pid, sig) == -1)){
			perror("kill error");
			exit(1);
		}

		// usleep(3*tf);
	}
}
```

1.10 Time Values
----------------

Historically, UNIX systems have maintained two different time values:

1. Calendar time. This value counts the number of seconds since the Epoch: 00:00:00 January 1, 1970, Coordinated Universal Time (UTC).

2. Process time. This is also called CPU time and measures the central processor resources used by a process. Process time is measured in clock ticks, which have historically been 50, 60, or 100 ticks per second.

UNIX System maintains three values for a process:
* Clock time: The clock time, sometimes called wall clock time, is the amount of time the process takes to run
* User CPU time: CPU time attributed to user instructions.
* System CPU time: CPU time attributed to the kernel when it executes on behalf of the process.

The sum of user CPU time and system CPU time is often called the CPU time.

from http://en.wikipedia.org/wiki/CPU_time:

CPU time or CPU usage can be reported either for each thread, for each process or for the entire system. Moreover, depending on what exactly the CPU was doing, the reported values can be subdivided in:

* User time is the amount of time the CPU was busy executing code in user space.
* System time is the amount of time the CPU was busy executing code in kernel space. If this value is reported for a thread or process, then it represents the amount of time the kernel was doing work on behalf of the executing context, for example, after a thread issued a system call.
* Idle time (for the whole system only) is the amount of time the CPU was not busy, or, otherwise, the amount of time it executed the system idle process. Idle time actually measures unused CPU capacity.
* Steal time (for the whole system only), on virtualized hardware, is the amount of time the operating system wanted to execute, but was not allowed to by the hypervisor.[1] This can happen if the physical hardware runs multiple guest operating system and the hypervisor chose to allocate a CPU time slot to another one.


####nextPrimeNumber.c
```c
#include <stdio.h>
#include <stdlib.h>
 
int isPrimeNumber(unsigned long int n){
  int i;
  for(i=2; i<=(n>>1); i++)
    if(n%i==0) return 0;
  return 1;
}
 
int main(int argc, char *argv[]){
  unsigned long int argument = strtoul(argv[1], NULL, 10), n = argument;
  while(!isPrimeNumber(++n));
 
  printf("Prime number greater than %d is %d\n", argument, n);
  return 0;
}
```

```bash
gcc nextPrimeNumber.c -o nextPrimeNumber

tom@mobile:~/prog/books/apue/apue-estudy$ time ./nextPrimeNumber 1000000000
Prime number greater than 1000000000 is 1000000007

real	0m4.963s
user	0m4.960s
sys	0m0.003s
```

1.11 System Calls and Library Functions
---------------------------------------

service points through which programs request services from the kernel

The system call interface has always been documented in Section 2 of the UNIX Programmer’s Manual.

Its definition is in the C language

older operating systems, which traditionally defined the kernel entry points in the assembly language of the machine.

```
The technique used on UNIX systems is for each system call to have a function of the same name in the standard C library. The user process calls this function, using the standard C calling sequence. This function then invokes the appropriate kernel service, using whatever technique is required on the system. For example, the function may put one or more of the C arguments into general registers and then execute some machine instruction that generates a software interrupt in the kernel. For our purposes, we can consider the system calls to be C functions.
```

Section 3 of the UNIX Programmer’s Manual defines the general-purpose library functions available to programmers. These functions aren’t entry points into the kernel, although they may invoke one or more of the kernel’s system calls.


2 UNIX Standardization and Implementations
==========================================

2.2 UNIX Standardization
------------------------

####2.2.1 ISO C

In late 1989, ANSI Standard X3.159-1989 for the C programming language was approved. This standard was also adopted as International Standard ISO/IEC 9899:1990.

ANSI: American National Standards Institute (the U.S. member in the ISO)
ISO: International Organization for Standardization.
IEC: International Electrotechnical Commission.

The C standard is now maintained and developed by the ISO/IEC international standardization working group for the C programming language, known as ISO/IEC JTC1/SC22/WG14, or WG14 for short.

The intent of the ISO C standard is to provide portability of conforming C programs to a wide variety of operating systems, not only the UNIX System.

This standard defines not only the syntax and semantics of the programming language but also a standard library

This library is important because all contemporary UNIX systems, such as the ones described in this book, provide the library routines that are specified in the C standard.

In 1999, the ISO C standard was updated and approved as ISO/IEC 9899:1999

Since 1999, three technical corrigenda have been published to correct errors in the ISO C standard—one in 2001, one in 2004, and one in 2007.

####2.2.2 IEEE POSIX

POSIX is a family of standards initially developed by the IEEE

IEEE: Institute of Electrical and Electronics Engineers
POSIX: Portable Operating System Interface

It originally referred only to the IEEE Standard 1003.1-1988 — the operating system interface—but was later extended to include many of the standards and draft standards with the 1003 designation, including the shell and utilities (1003.2).

It originally referred only to the IEEE Standard 1003.1-1988 — the operating system interface—but was later extended to include many of the standards and draft standards with the 1003 designation, including the shell and utilities (1003.2).

In this text we describe the 2008 edition of POSIX.1.

After more than twenty years of work, the standards are mature and stable. The POSIX.1 standard is maintained by an open working group known as the Austin Group (http://www.opengroup.org/austin). To ensure that they are still relevant, the standards need to be either updated or reaffirmed every so often.

2.5 Limits
----------

The implementations define many magic numbers and constants. Many of these have been hard coded into programs or were determined using ad hoc techniques. With the various standardization efforts that we’ve described, more portable methods are now provided to determine these magic numbers and implementation-defined limits, greatly improving the portability of software written for the UNIX environment.
Two types of limits are needed:
1. Compile-time limits (e.g., what’s the largest value of a short integer?)
2. Runtime limits (e.g., how many bytes in a filename?)



3 - File I/O
============


3.2 File descriptors
--------------------

File descriptor range from 0 to OPEN_MAX - 1

The term unbuffered means that each read or write invokes a system call in the kernel. These unbuffered I/O functions are not part of ISO C, but are part of POSIX.1 and the Single UNIX Specification.

3.3 open and openat Functions
-----------------------------

```c
#include <fcntl.h>
int open(const char *path, int oflag, ... /* mode_t mode */ );
int openat(int fd, const char *path, int oflag, ... /* mode_t mode */ );
```

One and only one of these five constants must be specified:
O_RDONLY
O_WRONLY
O_RDWR
O_EXEC
O_SEARCH (not suported by main unixes)

- O_CREAT Create the file if it doesn’t exist. This option requires a third argument to the open function (a fourth argument to the openat function) — the mode
- O_EXCL Generate an error if O_CREAT is also specified and the file already exists.
- O_NOFOLLOW Generate an error if path refers to a symbolic link
- O_SYNC Have each write wait for physical I/O to complete, including I/O necessary to update file attributes modified as a result of the write

not fully portable:

- O_DSYNC Have each write wait for physical I/O to complete, but don’t wait for file attributes to be updated if they don’t affect the ability to read the data just written.
- O_RSYNC Have each read operation on the file descriptor wait until any pending writes for the same portion of the file are complete.

The file descriptor returned by open and openat is guaranteed to be the lowest- numbered unused descriptor.
This fact is used by some applications to open a new file on standard input, standard output, or standard error. For example, an application might close standard output—normally, file descriptor 1—and then open another file, knowing that it will be opened on file descriptor 1.

openat (not fully portable)
------

1. The path parameter specifies an absolute pathname. In this case, the fd parameter is ignored and the openat function behaves like the open function.
2. The path parameter specifies a relative pathname and the fd parameter is a file descriptor that specifies the starting location in the file system where the relative pathname is to be evaluated. The fd parameter is obtained by opening the directory where the relative pathname is to be evaluated.
3. The path parameter specifies a relative pathname and the fd parameter has the special value AT_FDCWD. In this case, the pathname is evaluated starting in the current working directory and the openat function behaves like the open function.

The openat function is one of a class of functions added to the latest version of POSIX.1 to address two problems. First, it gives threads a way to use relative pathnames to open files in directories other than the current working directory. As we’ll see in Chapter 11, all threads in the same process share the same current working directory, so this makes it difficult for multiple threads in the same process to work in different directories at the same time. Second, it provides a way to avoid time-of-check- to-time-of-use (TOCTTOU) errors.

time-of-check- to-time-of-use (TOCTTOU) errors.
The basic idea behind TOCTTOU errors is that a program is vulnerable if it makes two file-based function calls where the second call depends on the results of the first call. Because the two calls are not atomic, the file can change between the two calls, thereby invalidating the results of the first call, leading to a program error. TOCTTOU errors in the file system namespace generally deal with attempts to subvert file system permissions by tricking a privileged program into either reducing permissions on a privileged file or modifying a privileged file to open up a security hole. Wei and Pu [2005] discuss TOCTTOU weaknesses in the UNIX file system interface.

3.4 creat

```c
#include <fcntl.h>
int creat(const char *path, mode_t mode);
```

same as:

open(path, O_WRONLY | O_CREAT | O_TRUNC, mode);

Historically, in early versions of the UNIX System, the second argument to open could be only 0, 1, or 2. There was no way to open a file that didn’t already exist. Therefore, a separate system call, creat, was needed to create new files. With the O_CREAT and O_TRUNC options now provided by open, a separate creat function is no longer needed.

3.6 lseek Function
------------------

Every open file has an associated "current file offset", normally a non-negative integer that measures the number of bytes from the beginning of the file.

#include <unistd.h>
off_t lseek(int fd, off_t offset, int whence);

- If whence is SEEK_SET, the file’s offset is set to offset bytes from the beginning of
the file.
- If whence is SEEK_CUR, the file’s offset is set to its current value plus the offset.
The offset can be positive or negative.
- If whence is SEEK_END, the file’s offset is set to the size of the file plus the offset.
The offset can be positive or negative.

Because a successful call to lseek returns the new file offset, we can seek zero bytes
from the current position to determine the current offset:

```c
   off_t    currpos;
   currpos = lseek(fd, 0, SEEK_CUR);
```

This technique can also be used to determine if a file is capable of seeking. If the file descriptor refers to a pipe, FIFO, or socket, lseek sets errno to ESPIPE and returns −1.


3.10 File Sharing
=================

