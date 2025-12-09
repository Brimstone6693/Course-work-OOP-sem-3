# Makefile for Software Package Database
# Clean makefile without CMake

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -fPIC
QTDIR = /usr/lib/x86_64-linux-gnu/qt5
MOC = $(QTDIR)/bin/moc
UIC = $(QTDIR)/bin/uic
RCC = $(QTDIR)/bin/rcc

# Find Qt5 include paths
QT_INCLUDES = $(shell pkg-config --cflags Qt5Core Qt5Gui Qt5Widgets)
QT_LIBS = $(shell pkg-config --libs Qt5Core Qt5Gui Qt5Widgets)

# If pkg-config doesn't work, fallback to common paths
ifeq ($(QT_INCLUDES),)
    QT_INCLUDES = -I/usr/include/x86_64-linux-gnu/qt5 -I/usr/include/x86_64-linux-gnu/qt5/QtWidgets -I/usr/include/x86_64-linux-gnu/qt5/QtGui -I/usr/include/x86_64-linux-gnu/qt5/QtCore
endif

ifeq ($(QT_LIBS),)
    QT_LIBS = -lQt5Core -lQt5Gui -lQt5Widgets
endif

INCLUDES = -I./include $(QT_INCLUDES)
LIBS = $(QT_LIBS)

SRCDIR = src
INCDIR = include
BUILDDIR = build
TARGET = SoftwarePackageDatabase

SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(BUILDDIR)/%.o)

# Generate MOC file for MainWindow
MOC_FILE = $(BUILDDIR)/moc_MainWindow.cpp
MOC_OBJECT = $(BUILDDIR)/moc_MainWindow.o

.PHONY: all clean run

all: $(BUILDDIR) $(TARGET)

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

# Rule to generate MOC file
$(MOC_FILE): $(INCDIR)/MainWindow.h | $(BUILDDIR)
	$(MOC) $(INCLUDES) $(INCDIR)/MainWindow.h -o $(MOC_FILE)

# Rule to compile MOC file
$(MOC_OBJECT): $(MOC_FILE) | $(BUILDDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Rule to compile source files to objects
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp | $(BUILDDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Rule to build the target executable
$(TARGET): $(OBJECTS) $(MOC_OBJECT)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ $(LIBS) -o $@

clean:
	rm -rf $(BUILDDIR)
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

install-qt-dev:
	apt-get update && apt-get install -y qtbase5-dev qtchooser qt5-qmake qtbase5-dev-tools

check-qt:
	@echo "Qt includes: $(QT_INCLUDES)"
	@echo "Qt libs: $(QT_LIBS)"