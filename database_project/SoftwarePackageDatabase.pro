TEMPLATE = app
TARGET = SoftwarePackageDatabase
CONFIG += qt console c++17
QT += core widgets gui

# Define source files
SOURCES += \
    src/main.cpp \
    src/MainWindow.cpp \
    src/Database.cpp \
    src/SoftwarePackage.cpp

# Define header files
HEADERS += \
    include/MainWindow.h \
    include/Database.h \
    include/SoftwarePackage.h \
    include/CustomContainer.h

# Include path
INCLUDEPATH += $$PWD/include

# Output directories
MOC_DIR = .moc
OBJECTS_DIR = .obj