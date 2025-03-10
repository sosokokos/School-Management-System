# School Management System

## Overview
The School Management System is a C++ based application designed to manage basic administrative tasks for an educational institution. It follows object-oriented programming principles and incorporates relational database concepts for optimized memory management such as custom dynamic array implementation.

## Project Structure
- **Course Management**: Add new courses, Remove courses, Search for specific courses
- **Student Management**: Register new students, Search for specific students, Remove students from the system
- **Enrollment System**: Enroll students in courses, Withdraw students from courses, Assign letter grades, Compute student GPA, Identify the top-performing student
- **Memory-Efficient Data Handling**: Uses custom-built dynamic data structures for optimal performance, Inspired by relational database design for efficient lookups

## SmarterArray Implementation
This project includes a SmarterArray class that enhances functionality beyond standard C++ arrays. 
- **Deep Copy of Data**: Implements a copy constructor and assignment operator to ensure independent instances
- **Memory Management**: Destructor prevents memory leaks by handling dynamic allocation cleanup
- **Dynamic Resizing**: The array expands dynamically to accommodate additional elements
- **Indexing Operator Overload**: (operator[]) Provides array-like access with built-in validation
- **Search Function**: (find()) Allows quick retrieval of stored elements
- **Element Removal**: (remove()) Supports safe and efficient deletion of elements.

## Setup
### Dependencies
- **Libraries**:
  - `iostream` for I/O
  - `string` for handling strings
  - `cassert` for assertions and debugging
  - `cstdlib` for random number generation
  - `ctime` for seeding random values
- **C++ Compiler**
  - I used g++ but you are welcome to use any alternative

### Compiling the Code
Ensure you have g++ (or complier of your choice) installed along with the required libraries. Compile the source code (using g++ as an example):
```r
g++ SchoolSystem.cpp -o SchoolSystem
```
### Running the Executable
Run the executable using:
```r
./SchoolSystem
```



