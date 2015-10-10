# Binary Reduction

## Problem
Implement a parallel, binary reduction. Given a list of N numbers, the program will use N/2 threads to cooperatively determine the maximum number in the list.

## Solution
The solution uses a multi-threaded approach to construct the solution. Barriers, implemented using binary semaphores allow the execution of the program cooperatively and remove race conditions. 


