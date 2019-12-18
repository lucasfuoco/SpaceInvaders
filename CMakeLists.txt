# Specify the minimum version for CMake
cmake_minimum_required (VERSION 3.8)

if(${CMAKE_VERSION} VERSION_LESS 3.14)
	cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
	cmake_policy(VERSION 3.14)
endif()

# Project name
set(SPACE_INVADERS "SpaceInvaders")
set(SPACE_INVADERS_LIBRARIES "spaceinvaders-1.0")

project (
	${SPACE_INVADERS}
	VERSION 0.1
	LANGUAGES CXX C
)

# Build directories
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(PROJECT_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(SPACE_INVADERS_GAME_FOLDER ${CMAKE_SOURCE_DIR}/game)

# The following folder will be included
include_directories(${PROJECT_SOURCE_DIR} ${EXECUTABLE_OUTPUT_PATH})

#qt
find_package(Qt5 COMPONENTS Core Widgets Svg OpenGl REQUIRED)

#boost
find_package(Boost REQUIRED COMPONENTS date_time filesystem system)

file(GLOB SOURCES
	${PROJECT_SOURCE_DIR}/*.cpp
	${PROJECT_SOURCE_DIR}/**/*.cpp
	${PROJECT_SOURCE_DIR}/**/**/*.cpp
)

QT5_ADD_RESOURCES(RESOURCES ${CMAKE_SOURCE_DIR}/resources.qrc)

add_library(${SPACE_INVADERS_LIBRARIES} STATIC
	${SOURCES}
	${RESOURCES}
)
target_include_directories(${SPACE_INVADERS_LIBRARIES} PRIVATE
	${Qt5Widgets_INCLUDE_DIRS}
	${Qt5Svg_INCLUDE_DIRS}
	${Qt5OpenGl_INCLUDE_DIRS}
	${Boost_INCLUDE_DIR}
)

add_executable(${SPACE_INVADERS} ${PROJECT_SOURCE_DIR}/main.cpp ${CMAKE_SOURCE_DIR}/resources.qrc)
target_include_directories(${SPACE_INVADERS} PRIVATE
	${Qt5Widgets_INCLUDE_DIRS}
	${Qt5Svg_INCLUDE_DIRS}
	${Qt5OpenGl_INCLUDE_DIRS}
	${Boost_INCLUDE_DIR}
)

target_link_libraries(${SPACE_INVADERS} PRIVATE
	${SPACE_INVADERS_LIBRARIES}
	${Qt5Widgets_LIBRARIES}
	${Qt5Svg_LIBRARIES}
	${Qt5OpenGl_LIBRARIES}
	${Boost_LIBRARIES}
)