qt_add_executable(huffman-cli
    main.c
)

target_link_libraries(huffman-cli
    PRIVATE
        huffman-core
        Qt::Core
)

install(TARGETS huffman-cli
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
