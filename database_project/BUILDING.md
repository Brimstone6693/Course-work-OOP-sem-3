# Software Package Database

This is a Qt5-based application for managing a database of software packages using a custom container implementation.

## Features

- Custom container with iterator support based on QVector
- Database operations for software packages (add, edit, delete, search)
- GUI interface with menus, toolbars, and status bar
- Data persistence (save/load to/from disk)
- Database merging capability

## Build Instructions

To build the project, you need Qt5 development libraries installed:

```bash
# Install dependencies
sudo apt-get install qtbase5-dev pkg-config build-essential

# Build the project
make

# Run the application
./SoftwarePackageDatabase
```

## Clean Build

To clean and rebuild:

```bash
make clean
make
```

## Requirements

- Qt5 development libraries
- g++ compiler
- pkg-config
- C++17 compatible compiler

## Build Status

The application has been successfully built and tested. All Qt5 dependencies are properly linked.