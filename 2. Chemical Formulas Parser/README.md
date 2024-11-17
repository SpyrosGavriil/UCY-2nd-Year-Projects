@mainpage

# Assignment 2 | Handling Chemical Formulas

## Project Description

This project is a C implementation for parsing and processing chemical formulas. 
It includes functionality for handling chemical elements, processing nested parentheses, 
and working with chemical formula structures like `Co₃(Fe(CN)₆)₂`. The project also includes 
a custom stack implementation and periodic table data handling.

The main file, **parseFormula.c**, is responsible for reading chemical formulas from an input file, parsing the formulas, and expanding them into their full form. The program handles complex nested parentheses and groups, using a stack data structure to manage these nested expressions. The processed formulas are then output to a specified output file.

## Command Line Options

The program offers three modes of operation, which can be specified via command-line options:

1. **`-v`**: Verifies that the parentheses in the chemical formula are balanced.
2. **`-ext`**: Expands the chemical formulas into their full representation.
3. **`-pn`**: Calculates the total number of protons in each chemical formula based on the periodic table.

### Verify Balanced Parentheses

This mode checks whether the parentheses in the chemical formulas are balanced.

Example usage:

```bash
./parseFormula periodicTable.txt -v testFile.txt
```

- **periodicTable.txt**: The periodic table data file.
- **testFile.txt**: The input file containing chemical formulas.

**Output:**

Verifies that the parentheses in the formulas are balanced, and displays a message such as:

```
Parentheses are balanced for all chemical formulas
```

### Expand Formulas

This mode expands the chemical formulas to show each element in its full form.

Example usage:

```bash
./parseFormula periodicTable.txt -ext testFile.txt extFile.txt
```

- **periodicTable.txt**: The periodic table data file.
- **testFile.txt**: The input file containing chemical formulas.
- **extFile.txt**: The output file where the expanded formulas will be written.

**Output:**

Expands formulas from the input file and writes the full representation to the output file:

```
Writing formulas to extFile.txt
```

### Compute Proton Numbers

This mode calculates the total proton number for each chemical formula.

Example usage:

```bash
./parseFormula periodicTable.txt -pn testFile.txt pnFile.txt
```

- **periodicTable.txt**: The periodic table data file.
- **testFile.txt**: The input file containing chemical formulas.
- **pnFile.txt**: The output file where the total proton numbers will be written.

**Output:**

Computes the total number of protons for each formula and writes the results to the output file:

```
Writing formulas to pnFile.txt
```

## Files and Structure

- **parseFormula.c**: Main file responsible for reading chemical formulas, handling parsing logic, and managing input/output operations.
- **formula_parser.c**: Contains core functions for formula parsing, handling nested structures, and expanding formulas into their full representations.
- **formula_parser.h**: Header file for `formula_parser.c`, providing declarations of functions and data structures used in parsing.
- **periodic_table.c**: Handles operations related to the periodic table, including loading element data and finding elements by atomic number.
- **periodic_table.h**: Header file for `periodic_table.c`, defining structures and function prototypes for periodic table operations.
- **stack.c**: Implements a stack data structure used in the formula parser to handle nested parentheses and chemical groups.
- **stack.h**: Header file for `stack.c`, defining stack-related functions and structures.

## Features

- **Chemical Formula Parsing**: Supports formulas with nested parentheses, ensuring proper handling of chemical elements and their counts.
- **Stack Data Structure**: A custom stack implementation is used for managing nested groups in chemical formulas.
- **Periodic Table Integration**: The program uses a periodic table to find atomic numbers and other data related to chemical elements.

## How to Build

To build the project, run the following command:

```bash
gcc -o formula_parser parseFormula.c formula_parser.c periodic_table.c stack.c
```

## Usage

The program supports three modes of operation: verifying balanced parentheses, expanding formulas, and computing proton numbers.

## Dependencies

No external dependencies are required for this project. It relies solely on standard C libraries.

## Future Improvements

- Add support for more complex chemical formulas.
- Optimize the parsing algorithm for better performance.
- Improve error handling for invalid or malformed formulas.

## Author

- **Spyros Gavriil**: Developer and maintainer of the project.
