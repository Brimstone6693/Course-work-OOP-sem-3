cmake_minimum_required(VERSION 3.16)

project(SoftwarePackageDatabase VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Find Qt5 components
find_package(Qt5 REQUIRED COMPONENTS Core Widgets Gui Sql)

# Enable automatic MOC, UIC, and RCC processing
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Define source files
set(SOURCES
    src/main.cpp
    src/MainWindow.cpp
    src/Database.cpp
    src/SoftwarePackage.cpp
)

# Define header files
set(HEADERS
    include/MainWindow.h
    include/Database.h
    include/SoftwarePackage.h
    include/CustomContainer.h
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Link Qt5 libraries
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets Qt5::Gui Qt5::Sql)

# Set installation rules (optional)
install(TARGETS ${PROJECT_NAME} DESTINATION bin)