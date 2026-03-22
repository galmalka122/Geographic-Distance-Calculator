# Geographic Distance Calculator

A C++ project designed to manage a database of cities and calculate geographic distances between them using various mathematical metrics. The application allows users to search for cities within a specific radius of a given origin and provides details on their spatial relationship.

## Project Structure
The project is organized into three main directories:
* **`include/`**: Header files defining the core classes and interfaces.
* **`src/`**: Implementation of the logic for coordinate handling, city management, and distance calculations.
* **`resources/`**: Data files, including `data.txt` which contains the city names and their geographic coordinates.

## Features

### 1. Distance Metrics
The application supports multiple ways to calculate the distance between two geographic points:
* **Euclidean Distance**: Standard straight-line distance calculated as $\sqrt{\Delta lat^2 + \Delta lon^2}$.
* **Chebyshev Distance**: The maximum absolute difference between coordinates, calculated as $\max(|\Delta lat|, |\Delta lon|)$.
* **Manhattan Distance**: The sum of the absolute differences of their coordinates, calculated as $|\Delta lat| + |\Delta lon|$.

### 2. Specialized Coordinate Validation
* **Latitude**: Validates that values are within the range of [-90, 90] degrees.
* **Longitude**: Validates that values are within the range of [-180, 180] degrees.
* **City Names**: Ensures city names follow specific formatting (e.g., "NAME REGION") and do not contain digits.

### 3. Efficient Searching
The system utilizes custom comparators to keep cities sorted by both Latitude and Longitude. This allows for optimized range-based queries when searching for nearby cities.

## Usage

### Data Format
The application reads from a `data.txt` file located in the `resources` folder. The file should follow this structure:
```text
City Name, ST
Latitude - Longitude
```
*Example:* `Abbeville, AL` followed by `31.566367 - 85.251300`.

### Running the Application
Upon execution, the program:
1. Loads all cities from the input file.
2. Prompts the user for an origin city name, a search radius, and a choice of distance function.
3. Displays the number of cities found within that radius, the number of cities located to the north of the origin, and a list of the matching city names.

## Building the Project
The project uses **CMake** for its build system. Each directory contains a `CMakeLists.txt` file to manage dependencies and compilation.
1.  Navigate to the root directory.
2.  Run `cmake .` to generate build files.
3.  Run `make` (or your platform's build command) to compile the executable.
