set(NIM_FLAGS -d:release --passL="-L$<TARGET_FILE_DIR:p0f-static> -lp0f-static")

add_custom_target(p0fa ALL
    DEPENDS p0f-static
    COMMAND nim c ${NIM_FLAGS} -o:p0fa ${CMAKE_CURRENT_SOURCE_DIR}/main.nim
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Generating nim binaries"
    VERBATIM)
