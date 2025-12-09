# Qt Creator Project Setup

This project is optimized for Qt Creator. Follow these steps to open and build the project:

## Opening the Project in Qt Creator

1. Launch Qt Creator
2. Select **File** → **Open File or Project** 
3. Navigate to the project directory and select either:
   - `CMakeLists.txt` for CMake build system, or
   - `SoftwarePackageDatabase.pro` for qmake build system
4. Qt Creator will automatically detect the build system and configure the project

## Build Configuration

### Using CMake (Recommended):
- The project includes a `CMakeLists.txt` file that is configured for Qt 5
- Qt Creator will automatically detect CMake and create appropriate build directories
- Make sure you have CMake support enabled in Qt Creator

### Using qmake:
- The project includes a `SoftwarePackageDatabase.pro` file
- This is the traditional Qt build system

## Required Qt Components

This project requires the following Qt 5 modules:
- Qt5::Core
- Qt5::Widgets 
- Qt5::Gui
- Qt5::Sql

Make sure your Qt installation includes these modules.

## Project Structure

```
SoftwarePackageDatabase/
├── CMakeLists.txt          # CMake build configuration
├── SoftwarePackageDatabase.pro  # qmake project file
├── include/                # Header files
│   ├── MainWindow.h
│   ├── Database.h
│   ├── SoftwarePackage.h
│   └── CustomContainer.h
├── src/                    # Source files
│   ├── main.cpp
│   ├── MainWindow.cpp
│   ├── Database.cpp
│   └── SoftwarePackage.cpp
└── ...
```

## Building the Project

1. After opening the project, select a kit from the status bar at the bottom
2. Choose **Debug** or **Release** build configuration
3. Press **Ctrl+B** or select **Build** → **Build All**
4. The executable will be created in the build directory

## Troubleshooting

If you encounter issues:

1. **Missing Qt modules**: Ensure your Qt installation includes Core, Widgets, Gui, and Sql modules
2. **CMake errors**: Make sure CMake is installed and in your PATH
3. **Compiler issues**: Verify that your selected kit has a valid compiler

## Qt-Specific Features Used

- QMainWindow with custom UI implementation
- QTableWidget for displaying data
- QAction and QMenuBar for menus
- QToolBar for toolbar functionality
- QMessageBox for dialogs
- QFileDialog for file operations
- QSettings for persistent settings (if implemented)
- Custom widgets and layouts
- Qt's signal/slot mechanism
- Qt's MOC (Meta-Object Compiler) for QObject support

## MOC-Enabled Classes

The following classes use Q_OBJECT macro and will be processed by MOC:
- MainWindow class in MainWindow.h

The project is now optimized for Qt Creator development environment.