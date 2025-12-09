#!/bin/bash

echo "Software Package Database - Demo Script"
echo "======================================="

echo
echo "1. Building the application..."
cd /workspace/database_project
mkdir -p build
cd build
cmake .. && make

echo
echo "2. Running the test program to verify functionality..."
cd /workspace/database_project
./test_program

echo
echo "3. The application executable is located at:"
echo "   /workspace/database_project/build/SoftwarePackageDatabase"
echo
echo "4. To run the GUI application, execute:"
echo "   cd /workspace/database_project/build && ./SoftwarePackageDatabase"
echo
echo "5. Features implemented:"
echo "   - Custom container with iterator support"
echo "   - Software package management"
echo "   - Add, edit, delete operations"
echo "   - Search functionality"
echo "   - Save/load databases"
echo "   - Merge databases"
echo "   - Complete Qt5 GUI with menu, toolbar, status bar, context menu"
echo "   - About dialog"

echo
echo "Demo completed successfully!"