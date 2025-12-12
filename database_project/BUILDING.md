# Software Package Database

This is a Qt5-based application for managing a database of software packages using a custom container implementation.

## Features

- Custom container with iterator support based on QVector
- Database operations for software packages (add, edit, delete, search)
- GUI interface with menus, toolbars, and status bar
- Data persistence (save/load to/from disk)
- Database merging capability

## Build Instructions

### Linux Build

To build the project on Linux, you need Qt5 development libraries installed:

```bash
# Install dependencies
sudo apt-get install qtbase5-dev pkg-config build-essential

# Build the project
make

# Run the application
./SoftwarePackageDatabase
```

### Windows Build

To build the project on Windows 11 with Qt and MinGW:

1. Install Qt5 with MinGW from the official Qt website
2. Open Qt Command Prompt or MinGW shell
3. Navigate to the project directory
4. Run these commands:

```cmd
qmake SoftwarePackageDatabase.pro
mingw32-make
```

This will generate `SoftwarePackageDatabase.exe` which can be run on Windows.

Alternatively, you can open the `.pro` file directly in Qt Creator and build using the IDE.

## Requirements

### Linux
- Qt5 development libraries
- g++ compiler
- pkg-config
- C++17 compatible compiler

### Windows
- Qt5 with MinGW
- qmake
- mingw32-make
- C++17 compatible compiler

## Clean Build

To clean and rebuild:

```bash
make clean
make
```

## Build Status

The application has been successfully built and tested. All Qt5 dependencies are properly linked.