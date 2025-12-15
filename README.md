# Concurrent Random Number Lists

A multithreaded C program that generates random integers and stores them in separate positive and negative linked lists.

## Description

This program creates multiple threads that concurrently generate random integers in the range INT_MIN to INT_MAX. The numbers are stored in two separate linked lists based on their sign. After all threads complete, both lists are sorted in ascending order and printed to stdout.

## Building

Compile the project using the provided Makefile:

```bash
make
```

This will create the executable at `bin/c_test`.

To clean object files:

```bash
make clean
```

To remove all build artifacts:

```bash
make fclean
```

To rebuild from scratch:

```bash
make re
```

## Usage

```bash
./bin/c_test <number_of_threads> <numbers_per_thread>
```

### Parameters

- `number_of_threads`: Number of threads to create (1-999)
- `numbers_per_thread`: How many random numbers each thread will generate (1-99999)

### Example

```bash
./bin/c_test 4 100
```

This creates 4 threads, each generating 100 random numbers, for a total of 400 numbers.

## Testing

The project includes three test suites in the `testing/` directory:

### Run All Tests

To compile the program and run all tests at once:

```bash
make test
```

This will automatically:
- Compile the program if needed
- Run invalid input tests
- Run memory leak tests
- Run sorting order tests

### Individual Test Suites

#### Invalid Input Tests

Tests that the program correctly rejects invalid inputs:

```bash
cd testing
./invalid_input.sh
```

#### Memory Leak Tests

Verifies no memory leaks using Valgrind:

```bash
cd testing
./leaks.sh
```

Note: Requires Valgrind to be installed.

#### Sorting Order Tests

Validates that output is correctly sorted:

```bash
cd testing
./order.sh
```
