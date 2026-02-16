cmake_minimum_required(VERSION 3.10)
project(Vault)
set(CMAKE_PREFIX_PATH "C:/Qt/6.10.1/msvc2022_64")
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
find_package(Qt6 REQUIRED COMPONENTS Charts)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON) # Handles Qt's Meta-Object Compiler automatically
set(CMAKE_AUTOUIC ON) # Handles .ui files automatically
set(CMAKE_AUTORCC ON) # Handles .qrc resource files automatically

find_package(Qt6 REQUIRED COMPONENTS Widgets)

include_directories(public)

file(GLOB_RECURSE SOURCES "private/*.cpp")
file(GLOB_RECURSE HEADERS "public/*.h")

add_executable(Vault ${SOURCES} ${HEADERS})
target_link_libraries(Vault Qt6::Widgets
							Qt6::Charts)