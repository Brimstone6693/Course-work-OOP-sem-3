cmake_minimum_required(VERSION 3.16)

project(SoftwarePackageDatabase VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Enable automatic MOC, UIC, and RCC processing
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Find Qt components - try Qt6 first, then Qt5 as fallback
if(NOT DEFINED QT_DEFAULT_MAJOR_VERSION)
    find_package(Qt6 COMPONENTS Core Widgets Gui Sql QUIET)
    if(Qt6_FOUND)
        message(STATUS "Found Qt6 - using Qt6")
        set(QT_DEFAULT_MAJOR_VERSION 6)
    else()
        message(STATUS "Qt6 not found, trying Qt5...")
        
        # On Windows, we might need to help CMake find Qt5
        if(WIN32)
            # Common Qt5 installation paths on Windows
            list(APPEND CMAKE_PREFIX_PATH
                $ENV{QTDIR}
                $ENV{QT_DIR}
                "C:/Qt/5.15.2/msvc2019_64"
                "C:/Qt/5.15.2/gcc_64"
                "C:/Qt/6.5.0/msvc2019_64"
                "C:/Qt/6.5.0/gcc_64"
                "C:/Qt/5.14.2/msvc2019_64"
                "C:/Qt/5.14.2/gcc_64"
                "C:/Qt/5.13.2/msvc2019_64"
                "C:/Qt/5.13.2/gcc_64"
                ${CMAKE_PREFIX_PATH}
            )
        endif()
        
        find_package(Qt5 REQUIRED COMPONENTS Core Widgets Gui Sql)
        set(QT_DEFAULT_MAJOR_VERSION 5)
    endif()
endif()

# Set Qt libraries based on version found
if(QT_DEFAULT_MAJOR_VERSION EQUAL 6)
    set(QT_LIBRARIES Qt6::Core Qt6::Widgets Qt6::Gui Qt6::Sql)
else()
    set(QT_LIBRARIES Qt5::Core Qt5::Widgets Qt5::Gui Qt5::Sql)
endif()

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

# Link Qt libraries (either Qt5 or Qt6 based on what was found)
target_link_libraries(${PROJECT_NAME} ${QT_LIBRARIES})

# Set installation rules (optional)
install(TARGETS ${PROJECT_NAME} DESTINATION bin)