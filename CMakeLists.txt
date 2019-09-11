cmake_minimum_required(VERSION 3.14)
project(shared-editor)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# In CLion->Settings->Build, Execution, Deployment->CMake->CMake options aggiungere
# il path delle librerie. Supponendo che la directory di installazione di Qt sia /opt/Qt:
# Linux:
# -DCMAKE_PREFIX_PATH=/opt/Qt/5.12.4/gcc_64/lib/cmake
# Windows:
# -DCMAKE_PREFIX_PATH=C:\\Qt\5.12.4\mingw73_64\lib\cmake

find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Charts REQUIRED)
find_package(Qt5PrintSupport REQUIRED)

list(APPEND LIBRARIES
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Charts
        Qt5::PrintSupport)
list(REMOVE_DUPLICATES LIBRARIES)

add_executable(shared-editor main.cpp textedit.cpp textedit.h textedit.qrc)
target_link_libraries(shared-editor ${LIBRARIES})