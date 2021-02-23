cmake_minimum_required(VERSION 3.19)
project(latinka_transliteracija)

set (CMAKE_AUTORCC ON)
find_package(Qt6 COMPONENTS Core Gui Widgets)

set (lt_src
    main.cpp
    mainWindow.h
    mainWindow.cpp
    darkTheme.h
    )

add_executable(latinka_transliteracija ${lt_src} rc.qrc)
target_link_libraries(latinka_transliteracija lib_latinka_tl Qt6::Core Qt6::Gui Qt6::Widgets)
target_include_directories(latinka_transliteracija
    PUBLIC $<TARGET_PROPERTY:lib_latinka_tl,INTERFACE_INCLUDE_DIRECTORIES>
    )
