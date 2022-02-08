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
                            gui
                            gui/window
                            gui/optionwindow
                            gui/tablemodel
                            storage
                            manager
                            dataprocessor
                            dataprocessor/tbl
                            dataprocessor/ini
                            dataprocessor/cfg
                            dataprocessor/batch
                            dataprocessor/batchini
                            system)

add_executable(generator    main.cpp
                            cfggenerator/cfggenerator.cpp
                            cfggenerator/cfggenerator.h
                            sregenerator/sregenerator.cpp
                            sregenerator/sregenerator.h
                            table/table.cpp
                            table/table.h
                            gui/window/mainwindow.cpp
                            gui/tablemodel/tableview.cpp
                            gui/tablemodel/dialogitemdelegate.cpp
                            gui/tablemodel/calendaritemdelegate.cpp
                            gui/window/mainwindow.h
                            gui/tablemodel/tableview.h
                            tablerowprop.h
                            gui/tablemodel/dialogitemdelegate.h
                            gui/tablemodel/calendaritemdelegate.h
                            gui/window/mainwindow.ui
                            storage/datastorage.h
                            storage/datastorage.cpp
                            gui/tablemodel/itempathwidget.h
                            gui/tablemodel/itempathwidget.cpp
                            gui/tablemodel/itempathwidget.ui
                            generator.cpp
                            generator.h
                            manager/manager.h
                            manager/filemanager.h
                            manager/filemanager.cpp
                            manager/batchmanager.h
                            manager/batchmanager.cpp
                            dataprocessor/dataprocessor.h
                            dataprocessor/tbl/tblprocessor.cpp
                            dataprocessor/tbl/tblprocessor.h
                            dataprocessor/ini/iniprocessor.cpp
                            dataprocessor/ini/iniprocessor.h
                            dataprocessor/batch/batchprocessor.cpp
                            dataprocessor/batch/batchprocessor.h
                            dataprocessor/batchini/batchiniprocessor.cpp
                            dataprocessor/batchini/batchiniprocessor.h
                            dataprocessor/cfg/cfgprocessor.cpp
                            dataprocessor/cfg/cfgprocessor.h
                            dataprocessor/cfg/blockcfg.h
                            dataprocessor/cfg/blockcfg.cpp
                            gui/optionwindow/optionwindow.h
                            gui/optionwindow/optionwindow.cpp
                            gui/optionwindow/optionwindow.ui
                            options.h
                            )


target_link_libraries(generator  Qt5::Widgets
                                 Qt5::Gui
                                 Qt5::Core )

target_include_directories(generator PRIVATE ${SEARCH_DIRS})
