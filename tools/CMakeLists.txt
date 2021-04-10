add_executable(p0f-client p0f-client.c)
add_executable(p0f-sendsyn6 p0f-sendsyn6.c)
add_executable(p0f-sensyn p0f-sendsyn.c)

#
# install
#
install(TARGETS p0f-client p0f-sendsyn6 p0f-sensyn RUNTIME DESTINATION bin)
