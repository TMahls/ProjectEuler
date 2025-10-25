# Project Euler Problem Repository


## What's in here? 

### Scripts for executing problems

'./runProblem.sh', which I just have aliased to 'runProblem' in my .bashrc file

Usage: "runProblem 3" will run problem 3 and output the answer, and amount of time it took. 

You can add a '-n' flag to prevent compilation of the utils library.

The '-v' flag will compare your answer to the decoded answer key.

'/.runAllProblems.sh' generally is for testing to see if library changes broke any previous solutions. Will
run any problem that exists (assuming the xxxx.cpp naming scheme) with the '-n' flag for speed.

'answerData.txt' - No spoilers! This text file has all the answers, but it's been mildly obfuscated to prevent peeking.
Don't ruin the fun for yourself and others by publishing answers online.


### Problem Source 

This folder, as one might expect, contains all the problemX.cpp files as well as any required data files. 


### libEulerUtils

A library for common Project Euler utilities! Pretty handy. Includes a home-grown BigInt class.

Original source on that: https://www.geeksforgeeks.org/cpp/bigint-big-integers-in-c-with-example/

I re-implemented this in my style, added a header file, etc. 


### Old Work

My old high school (2016) era solutions and notes. When I first started project euler, I was hoping to get
into MIT because the MIT website said doing these problems would help. I didn't get in, but it did sharpen 
my programming and math skills which is the important thing! 


## Guidelines

**Time for solution** -- While the website uses the 'minute or less' guideline, we are running in C++ on a much
faster, modern machine. To account for older computers and slow languages, really each of these should take _under
0.5 seconds_. Any slower than that and your algorithm needs improvement. Additionally, that speed will help when running
'runAllProblems'. 

**Solution Memory Usage** -- No array should take up more than a couple megabytes of memory, and a program
shouldn't use much more total memory than that either. 

**General optimization tip** -- if a function returns a bool and is checking for something in a loop,
put a return condition in the loop. In simpler terms, the moment we find out if a number is or isn't something,
don't wait for the loop to finish. Return right then and there!


