# SPDX-License-Identifier: MIT
# Copyright (c) 2024 Pedro López-Cabanillas <plcl@users.sf.net>

cmake_minimum_required(VERSION 3.19)

project(PipeListener LANGUAGES CXX)

find_package(QT NAMES Qt6 REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

qt6_standard_project_setup()

qt_add_executable(${PROJECT_NAME}
  main.cpp
  pipelistener.cpp
  pipelistener.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
)

install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
