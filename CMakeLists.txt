cmake_minimum_required(VERSION 3.12)

project(p0f LANGUAGES C)
set(VERSION 3.09b)

#
# Search dependencies
#
find_file(pcap.h PCAP_HEADER)

set(SRCS fp_http.c fp_mtu.c fp_tcp.c p0f.c process.c readfp.c)

add_executable(p0f ${SRCS})
