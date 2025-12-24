# Build Instructions

## Prerequisites

- GCC compiler (MinGW on Windows, GCC on Linux/Mac)
- Make utility (GNU Make)

## Project Structure

```
student-grade-tracker/
├── bin/                  # Compiled executables
├── build/                # Object files (.o)
├── data/                 # Student data (CSV files)
├── docs/                 # Documentation
├── include/              # Header files (.h)
│   ├── student.h
│   ├── grading.h
│   ├── fileio.h
│   ├── display.h
│   ├── operations.h
│   └── statistics.h
├── src/                  # Source files (.c)
│   ├── main.c
│   ├── grading.c
│   ├── fileio.c
│   ├── display.c
│   ├── operations.c
│   └── statistics.c
├── tests/                # Test files (future)
├── Makefile              # Build automation
├── .gitignore            # Git ignore rules
└── README.md             # Project documentation
```

## Building the Project

### Using Makefile (Recommended)

1. **Build the project:**

   ```bash
   make
   ```

   or

   ```bash
   make all
   ```

2. **Build and run:**

   ```bash
   make run
   ```

3. **Clean build artifacts:**

   ```bash
   make clean
   ```

4. **Rebuild from scratch:**

   ```bash
   make rebuild
   ```

5. **Show help:**
   ```bash
   make help
   ```

### Manual Compilation

If you prefer to compile manually without Make:

```bash
# Create directories
mkdir bin build data

# Compile all source files
gcc -Wall -Wextra -Iinclude -c src/main.c -o build/main.o
gcc -Wall -Wextra -Iinclude -c src/grading.c -o build/grading.o
gcc -Wall -Wextra -Iinclude -c src/fileio.c -o build/fileio.o
gcc -Wall -Wextra -Iinclude -c src/display.c -o build/display.o
gcc -Wall -Wextra -Iinclude -c src/operations.c -o build/operations.o
gcc -Wall -Wextra -Iinclude -c src/statistics.c -o build/statistics.o

# Link all object files
gcc build/main.o build/grading.o build/fileio.o build/display.o build/operations.o build/statistics.o -o bin/studentSystem
```

### Running the Program

After building:

```bash
./bin/studentSystem
```

On Windows:

```bash
.\bin\studentSystem.exe
```

## Compiler Flags Explained

- `-Wall`: Enable all common warnings
- `-Wextra`: Enable extra warnings
- `-Iinclude`: Add include directory to header search path
- `-c`: Compile without linking (create object files)
- `-o`: Specify output file name

## Troubleshooting

### Make command not found

- **Windows**: Install MinGW-w64 or use WSL
- **Linux**: `sudo apt install build-essential`
- **Mac**: `xcode-select --install`

### GCC not found

Install a C compiler:

- **Windows**: MinGW-w64, TDM-GCC, or MSYS2
- **Linux**: `sudo apt install gcc`
- **Mac**: Included with Xcode Command Line Tools

### Permission denied (Linux/Mac)

```bash
chmod +x bin/studentSystem
```

## Module Descriptions

- **main.c**: Entry point, menu system
- **grading.c**: Grade point calculations (SGPA, CGPA)
- **fileio.c**: CSV file operations (save/load)
- **display.c**: Display functions (tables, graphs, rank list)
- **operations.c**: CRUD operations (add, update, delete)
- **statistics.c**: Statistical analysis (average, topper, etc.)

## Grading System

The system implements the **Mar Athanasius College of Engineering** grading scale:

| Grade | Grade Point | Percentage Range |
| ----- | ----------- | ---------------- |
| S     | 10.0        | ≥ 90%            |
| A+    | 9.0         | 85% – < 90%      |
| A     | 8.5         | 80% – < 85%      |
| B+    | 8.0         | 75% – < 80%      |
| B     | 7.5         | 70% – < 75%      |
| C+    | 7.0         | 65% – < 70%      |
| C     | 6.5         | 60% – < 65%      |
| D     | 6.0         | 55% – < 60%      |
| P     | 5.5         | 50% – < 55%      |
| F     | 0.0         | < 50%            |

## Data Storage

Student data is stored in `data/students.csv` in the following format:

```
roll_no,name,subjectCount,subject1,marks1,credits1,...,sgpa
```
