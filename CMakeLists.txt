cmake_minimum_required(VERSION 3.14)
project(latinka_transliteracija)

set (CMAKE_AUTORCC)
find_package(Qt5Core)
find_package(Qt5Widgets)

set (lt_src
    main.cpp
    mainWindow.h
    mainWindow.cpp
    latinkaConverter.h
    latinkaConverter.cpp
    latinkaConverterStd.h
    latinkaConverterStd.cpp
    )

add_executable(latinka_transliteracija ${lt_src})
target_link_libraries(latinka_transliteracija Qt5::Core Qt5::Widgets)
