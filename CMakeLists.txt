cmake_minimum_required(VERSION 3.5)

project(generator LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(Qt5 REQUIRED Widgets Gui Core)


set                        (SEARCH_DIRS
                            cfggenerator
                            sregenerator
                            table
                            mainwindow
                            storage)

add_executable(generator    main.cpp
                            cfggenerator/cfggenerator.cpp
                            cfggenerator/cfggenerator.h
                            sregenerator/sregenerator.cpp
                            sregenerator/sregenerator.h
                            table/table.cpp
                            table/table.h
                            mainwindow/mainwindow.cpp
                            mainwindow/tableview.cpp
                            mainwindow/tableitemdelegate.cpp
                            mainwindow/mainwindow.h
                            mainwindow/tableview.h
                            tablerowprop.h
                            mainwindow/tableitemdelegate.h
                            mainwindow/mainwindow.ui
                            storage/datastorage.h
                            storage/datastorage.cpp
                            )


target_link_libraries(generator  Qt5::Widgets
                                 Qt5::Gui
                                 Qt5::Core )

target_include_directories(generator PRIVATE ${SEARCH_DIRS})
