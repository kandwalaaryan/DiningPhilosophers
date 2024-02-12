# Dining Philosophers Problem Solution

This repository contains my implementation of the Dining Philosophers Problem, a classic synchronization exercise. The solution is implemented in C using POSIX threads (pthreads) and synchronization primitives such as mutexes and condition variables.

## Problem Statement

The Dining Philosophers Problem illustrates the challenges of allocating limited resources among processes in a deadlock-free and starvation-free manner. Five philosophers sit at a table with five forks and must alternately think and eat. Importantly, each philosopher needs two forks to eat, and must pick up the left fork before the right one.

## Implementation Details

This solution to the Dining Philosophers Problem ensures that deadlock does not occur and that all philosophers can eat and think without starving. The implementation uses mutex locks to protect shared resources (the forks) and condition variables to manage philosopher states.

## Files in Repository

- `dining_philosophers.c`: The main C source file containing the algorithm and thread logic.
- `dining_philosophers`: The compiled executable file from the C source, which can be run to simulate the philosophers' actions.

## How to Compile and Run

You need a Linux environment with GCC and make installed to compile and run this project. Use the following commands:

To compile the source code:

```sh
gcc -o dining_philosophers dining_philosophers.c -lpthread
