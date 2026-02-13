cmake_minimum_required(VERSION 3.16)

project(Notepad VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
    main.cpp
    notepad.cpp
    notepad.h
    notepad.ui
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_add_executable(Notepad
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        res.qrc
    )
else()
    add_executable(Notepad
        ${PROJECT_SOURCES}
        res.qrc
    )
endif()

target_link_libraries(Notepad PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(Notepad PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER com.github.yourname.notepad
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Notepad
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Notepad)
endif()
