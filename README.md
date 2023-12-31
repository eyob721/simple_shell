# 0x16. C - Simple shell

## Description

This project is about implementing a simple shell, similar to the original shell program **sh**. This is our second group project in Alx.

## General

A shell is a program that allows users to interact with the operating system. It can be a command line interface, such as the one in this project, or it can be a graphical user interface, such as Windows Office or Adobe suite for example.

In UNIX the most popular shell programs are:

| Shell Program | Description |
| --- | --- |
| sh  | Shell program. The original shell program, with small features. |
| csh | C Shell. Syntax resembles the c programming language. Is an improved version of sh. |
| tcsh | TENEX C Shell. Also called the Turbos C Shell. Is an improved version of the C shell with lots of features added to it. |
| ksh | Korn Shell. A very advanced and improved version of the original shell program, sh. |
| bash | Bourne Again Shell. This is the GNU shell that is most commonly used. It has the best features of all the other shells and is also beginner friendly. |

This project focuses on implementing the original shell program sh (/bin/sh).

## Features

The shell handles builtin commands and system commands. The following builtin commands are implemented.

| Commands | Description |
| --- | --- |
| exit | Exits from the shell. It can take an exit code to exit with as argument. |
| env | Prints all of the environment variables. |
| setenv | Adds or overwrites an environment variable. Just like the set command in sh. |
| unsetenv | Removes an environment variable. Just like unset command in sh. |
| cd | Changes directory. |
| alias | Defines an alias for a command. |

The shell can also take a file as an argument and run the commands in the file line
by line. It also implements the following features.

- Command separator (;)
- Logical operators (&& and ||)
- Comments (#)
- Variable expansions


## Restrictions

There are restrictions on the functions and system calls we can use on this project. The only allowed functions and system calls are listed below.

- `access` (man 2 access)
- `chdir` (man 2 chdir)
- `close` (man 2 close)
- `closedir` (man 3 closedir)
- `execve` (man 2 execve)
- `exit` (man 3 exit)
- `_exit` (man 2 _exit)
- `fflush` (man 3 fflush)
- `fork` (man 2 fork)
- `free` (man 3 free)
- `getcwd` (man 3 getcwd)
- `getline` (man 3 getline)
- `getpid` (man 2 getpid)
- `isatty` (man 3 isatty)
- `kill` (man 2 kill)
- `malloc` (man 3 malloc)
- `open` (man 2 open)
- `opendir` (man 3 opendir)
- `perror` (man 3 perror)
- `read` (man 2 read)
- `readdir` (man 3 readdir)
- `signal` (man 2 signal)
- `stat` (__xstat) (man 2 stat)
- `lstat` (__lxstat) (man 2 lstat)
- `fstat` (__fxstat) (man 2 fstat)
- `strtok` (man 3 strtok)
- `wait` (man 2 wait)
- `waitpid` (man 2 waitpid)
- `wait3` (man 2 wait3)
- `wait4` (man 2 wait4)
- `write` (man 2 write)

From this list, there are two functions we have implemented our selves and used for this project. These are the getline and strtok function.

## Usage

To use the shell you can clone the repo to your machine and compile all the source files. You can use the following command to compile the codes

`gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh`

After compilation just run the executable `./hsh`, and it shall work.

## Contributors

Eyob Melkamu ([eyob721](https://github.com/eyob721 "eyob721"))

Ezra Teshome ([Ezralx](https://github.com/Ezralx "Ezralx"))
