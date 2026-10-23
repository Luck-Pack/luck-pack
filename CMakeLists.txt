cmake_minimum_required(VERSION 3.26)

project(LuckPack VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Quick REQUIRED)

add_subdirectory(src)

qt_add_executable(appLuckPack
  MANUAL_FINALIZATION
  src/main.cpp
)

qt_add_qml_module(appLuckPack
  URI LuckPack
  VERSION 1.0
  QML_FILES
    ${QML_SOURCES}
  SOURCES
    ${UI_SOURCES}
    ${MANAGER_SOURCES}
)

target_include_directories(appLuckPack PUBLIC
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${INCLUDE_DIRS}
)

target_link_libraries(appLuckPack PRIVATE
  Qt6::Quick
)

qt_finalize_executable(appLuckPack)