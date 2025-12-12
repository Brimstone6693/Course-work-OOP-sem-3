# Software Package Database

## Project Description
This is a database application developed in C++ using Qt5 for managing software packages. The application features a custom container implementation that works similarly to STL containers, with full iterator support.

## Features
- **Custom Container**: A vector-like container with custom iterator implementation
- **Database Operations**:
  - Add, edit, and delete software packages
  - Search functionality with custom predicates
  - Load and save databases to disk
  - Merge multiple databases
- **GUI Interface**:
  - Main menu with File, Edit, View, and Help options
  - Toolbar with quick access to common functions
  - Status bar showing package count
  - Context menu for table operations
  - Search functionality
  - About dialog

## Classes

### SoftwarePackage
Represents a software package with the following attributes:
- Name
- Manufacturer
- Size (in MB)
- Version
- Release year

### CustomContainer<T>
A custom container implementation similar to std::vector with:
- Iterator support (CustomIterator)
- Template-based design
- Standard container operations (push_back, erase, etc.)
- Find and remove_if methods with predicate support

### Database
Manages the collection of SoftwarePackage objects with:
- Add, edit, delete operations
- Search functionality
- Serialization to/from files
- Database merging capability

### MainWindow
The main GUI interface with:
- Table view of packages
- Menu system
- Toolbar
- Status bar
- Context menu support

## Build Instructions

### Prerequisites
- CMake 3.16 or higher
- Qt5 development libraries
- C++17 compatible compiler

### Building
```bash
mkdir build
cd build
cmake ..
make
```

### Running
```bash
./SoftwarePackageDatabase
```

## Usage
1. Launch the application
2. Use "Add Package" to add new software packages
3. Use "Edit Package" or "Delete Package" to modify existing entries
4. Use the search bar to filter packages
5. Save your database using "Save Database"
6. Load previously saved databases using "Load Database"
7. Merge with other databases using "Merge Databases"

## Design Decisions
- **Custom Container**: Implemented to meet the requirement of creating a custom container similar to STL containers
- **Template Design**: Allows the container to work with different types, though specialized for SoftwarePackage
- **Iterator Pattern**: Custom iterator implementation to provide STL-like interface
- **Separation of Concerns**: GUI logic separated from data management
- **Serialization**: Binary format for efficient storage and retrieval
- **Predicate-based Search**: Flexible search functionality using function objects

## File Structure
```
├── include/                 # Header files
│   ├── SoftwarePackage.h    # Software package class
│   ├── CustomContainer.h    # Custom container and iterator
│   ├── Database.h           # Database management class
│   └── MainWindow.h         # GUI main window class
├── src/                     # Source files
│   ├── main.cpp             # Application entry point
│   ├── SoftwarePackage.cpp  # Software package implementation
│   ├── Database.cpp         # Database implementation
│   └── MainWindow.cpp       # GUI implementation
├── CMakeLists.txt           # Build configuration
└── README.md               # This file
```

## Building on Windows 11

### With Qt Creator and MinGW

To build on Windows 11:

1. Ensure Qt5 with MinGW is properly installed
2. Open the `SoftwarePackageDatabase.pro` file in Qt Creator
3. Select the appropriate MinGW kit (e.g., Desktop Qt 5.x.x MinGW 64-bit)
4. Configure and build the project using Qt Creator

### With Command Line Tools

Alternatively, you can build from command line using qmake:

1. Open Qt Command Prompt or MinGW shell
2. Navigate to the project directory
3. Run these commands:

```cmd
qmake SoftwarePackageDatabase.pro
mingw32-make
```

This will generate `SoftwarePackageDatabase.exe` which can be run on Windows.

### Prerequisites for Windows

Make sure you have:
- Qt5 installed with MinGW compiler
- The PATH environment variable includes Qt and MinGW directories
- All required Qt libraries (Qt Core, Gui, Widgets)