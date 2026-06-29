cmake_minimum_required(VERSION 3.19)
project(huffman-archiver VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

add_subdirectory(app/core)
add_subdirectory(app/cli)

qt_add_executable(huffman-archiver
    main.cpp
)

target_link_libraries(huffman-archiver
    PRIVATE
        Qt::Core
        Qt6::Widgets
        huffman-core
)

set_target_properties(huffman-archiver PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)

install(TARGETS huffman-archiver
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
