add_executable(huffman-cli
    main.c
    cli_options.c
)

target_include_directories(huffman-cli PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(huffman-cli
    PRIVATE
        huffman-core
)

set_target_properties(huffman-cli PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)

install(TARGETS huffman-cli
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
