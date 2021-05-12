set(NIM_FLAGS -d:release --passL=$<TARGET_FILE:p0f-static>)
list(APPEND NIM_FLAGS --passL=${PCAP_LIBRARY})

add_custom_target(p0f-nim-client ALL
    DEPENDS p0f-static
    COMMAND nim c ${NIM_FLAGS} -o:p0f-nim-client ${CMAKE_CURRENT_SOURCE_DIR}/main.nim
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Generating nim binaries")
