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
                            src
                            src/gui
                            src/gui/window
                            src/gui/optionwindow
                            src/gui/tablemodel
                            src/storage
                            src/manager
                            src/dataprocessor
                            src/dataprocessor/tbl
                            src/dataprocessor/ini
                            src/dataprocessor/cfg
                            src/dataprocessor/txt
                            src/dataprocessor/batch
                            src/dataprocessor/batchini
                            src/dataprocessor/batchcfg
                            )

add_executable(generator    src/main.cpp
                            src/gui/window/mainwindow.cpp
                            src/gui/tablemodel/tableview.cpp
                            src/gui/tablemodel/dialogitemdelegate.cpp
                            src/gui/tablemodel/calendaritemdelegate.cpp
                            src/gui/window/mainwindow.h
                            src/gui/tablemodel/tableview.h
                            src/tablerowprop.h
                            src/gui/tablemodel/dialogitemdelegate.h
                            src/gui/tablemodel/calendaritemdelegate.h
                            src/gui/tablemodel/checkdelegate.h
                            src/gui/tablemodel/checkdelegate.cpp
                            src/gui/window/mainwindow.ui
                            src/storage/datastorage.h
                            src/storage/datastorage.cpp
                            src/gui/tablemodel/itempathwidget.h
                            src/gui/tablemodel/itempathwidget.cpp
                            src/gui/tablemodel/itempathwidget.ui
                            src/generator.cpp
                            src/generator.h
                            src/manager/manager.h
                            src/manager/filemanager.h
                            src/manager/filemanager.cpp
                            src/manager/batchmanager.h
                            src/manager/batchmanager.cpp
                            src/dataprocessor/dataprocessor.h
                            src/dataprocessor/tbl/tblprocessor.cpp
                            src/dataprocessor/tbl/tblprocessor.h
                            src/dataprocessor/ini/iniprocessor.cpp
                            src/dataprocessor/ini/iniprocessor.h
                            src/dataprocessor/batch/batchprocessor.cpp
                            src/dataprocessor/batch/batchprocessor.h
                            src/dataprocessor/batchini/batchiniprocessor.cpp
                            src/dataprocessor/batchini/batchiniprocessor.h
                            src/dataprocessor/cfg/cfgprocessor.cpp
                            src/dataprocessor/cfg/cfgprocessor.h
                            src/dataprocessor/cfg/blockcfg.h
                            src/dataprocessor/cfg/blockcfg.cpp
                            src/dataprocessor/batchcfg/batchcfgprocessor.cpp
                            src/dataprocessor/batchcfg/batchcfgprocessor.h
                            src/gui/optionwindow/optionwindow.h
                            src/gui/optionwindow/optionwindow.cpp
                            src/gui/optionwindow/optionwindow.ui
                            src/options.h
                            src/dataprocessor/txt/txtdataprocessor.h
                            src/dataprocessor/txt/swtxtdataprocessor.cpp
                            src/dataprocessor/txt/rstxtdataprocessor.cpp
                            )


target_link_libraries(generator  Qt5::Widgets
                                 Qt5::Gui
                                 Qt5::Core )

target_include_directories(generator PRIVATE ${SEARCH_DIRS})
