# Student Management System

A comprehensive C-based student management system for tracking academic performance, calculating GPAs, and generating reports. Implements the Mar Athanasius College of Engineering grading system.

## 🎯 Features

- **Student Management**: Add, update, delete, and display student records
- **Grade Calculation**: Automatic SGPA and CGPA calculation based on credits and marks
- **Performance Analytics**: Class statistics, topper identification, and average calculations
- **Visual Reports**: Bar graph visualization of student performance
- **Rank System**: SGPA-based leaderboard with visual representation
- **Data Persistence**: CSV file storage for student records
- **Modular Architecture**: Clean separation of concerns with multiple modules

## 📁 Project Structure

```
Student Management System/
├── bin/                  # Compiled executables
├── build/                # Object files
├── data/                 # Student data (CSV)
├── docs/                 # Documentation
│   └── BUILD.md         # Build instructions
├── include/              # Header files
│   ├── student.h        # Student structure and constants
│   ├── grading.h        # Grading calculations
│   ├── fileio.h         # File I/O operations
│   ├── display.h        # Display functions
│   ├── operations.h     # CRUD operations
│   └── statistics.h     # Statistical analysis
├── src/                  # Source files
│   ├── main.c           # Entry point
│   ├── grading.c        # Grade point calculations
│   ├── fileio.c         # CSV operations
│   ├── display.c        # Display functions
│   ├── operations.c     # Student operations
│   └── statistics.c     # Statistics functions
├── tests/                # Test files (future)
├── Makefile              # Build automation
├── .gitignore            # Git ignore rules
└── README.md             # This file
```

## 🚀 Quick Start

### Prerequisites

- GCC compiler
- Make utility

### Build and Run

```bash
# Build the project
make

# Build and run
make run

# Clean build artifacts
make clean

# Rebuild from scratch
make rebuild
```

For detailed build instructions, see [docs/BUILD.md](docs/BUILD.md).

## 📊 Grading System

Implements the **Mar Athanasius College of Engineering** grading scale:

| Grade | Points | Range  | Grade | Points | Range  |
| ----- | ------ | ------ | ----- | ------ | ------ |
| S     | 10.0   | ≥ 90%  | C+    | 7.0    | 65-69% |
| A+    | 9.0    | 85-89% | C     | 6.5    | 60-64% |
| A     | 8.5    | 80-84% | D     | 6.0    | 55-59% |
| B+    | 8.0    | 75-79% | P     | 5.5    | 50-54% |
| B     | 7.5    | 70-74% | F     | 0.0    | < 50%  |

### GPA Calculation

**SGPA (Semester Grade Point Average):**

```
SGPA = Σ(Credits × Grade Points) / Σ(Credits)
```

**CGPA (Cumulative Grade Point Average):**

```
CGPA = Σ(Credits × Grade Points) / Σ(Credits) [across all semesters]
```

**Percentage Equivalent:**

```
Percentage = 10 × CGPA
```

## 💻 Usage

### Menu Options

1. **Add Student**: Register a new student with subjects, marks, and credits
2. **Display Students**: View all students in tabular format
3. **Update Student**: Modify marks for an existing student
4. **Delete Student**: Remove a student by roll number
5. **Show Statistics**: View class average, topper, and performance graphs
6. **Show Leaderboard**: Display students ranked by SGPA
7. **Exit**: Save and quit the application

### Example Workflow

```
1. Add Student
   - Enter roll number, name
   - Enter number of subjects
   - For each subject: name, marks (0-100), credits

2. Display Students
   - View all student records in a table

3. Show Statistics
   - See class average SGPA
   - Identify topper
   - View performance bar graph

4. Show Leaderboard
   - See students ranked by SGPA with visual bars
```

## 📦 Modules

### Core Modules

- **student.h**: Student structure, constants, and global declarations
- **grading.c/h**: Grade point and GPA calculations
- **fileio.c/h**: CSV file read/write operations
- **display.c/h**: Terminal-based display and visualization
- **operations.c/h**: CRUD operations for student records
- **statistics.c/h**: Statistical analysis and reporting
- **main.c**: Program entry point and menu system

## 🗄️ Data Storage

Student data is stored in `data/students.csv` with the format:

```csv
roll_no,name,subjectCount,subject1,marks1,credits1,subject2,marks2,credits2,...,sgpa
```

## 🔧 Development

### Compilation Flags

- `-Wall -Wextra`: Enable comprehensive warnings
- `-Iinclude`: Include header directory

### Adding New Features

1. Define function prototypes in appropriate header file (`include/`)
2. Implement functions in corresponding source file (`src/`)
3. Update Makefile dependencies if needed
4. Rebuild with `make rebuild`

## 📝 License

This project was created for educational purposes.

## 👨‍💻 Author

Created as a semester 1 project, now modularized and improved.

## 🙏 Acknowledgments

- Grading system based on **Mar Athanasius College of Engineering** regulations
- Built with C for performance and simplicity

---

**Note**: This is a CLI-based application. For best experience, use a terminal with at least 80 character width.
