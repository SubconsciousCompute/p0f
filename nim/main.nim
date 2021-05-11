{.passC: "-I../src".}

import json
import parseopt
import logging

var logger = newConsoleLogger()
addHandler(logger)

type
  p0f_api_query {.header : "api.h", packed, importc: "struct p0f_api_query".} = object
    magic: uint32
    addr_type: uint8
    `addr`: array[16, uint8]

  p0f_api_response {.header : "api.h", packed, importc: "struct p0f_api_response".} = object
    magic, status, first_seen, last_seen, total_conn, uptime_min, up_mod_days, last_nat, last_chg : uint32
    distance: int16
    bad_sw, os_match_q: uint8
    os_name, os_flavor, http_name, http_flavor, link_type, language : string # array[32, uint8]


proc handle_query(q: ptr p0f_api_query, r: ptr p0f_api_response) {.header: "api.h", importc: "handle_query".}


#
# Main section.
#
var
  a : p0f_api_query
  b : p0f_api_response

var p = initOptParser("--socket")
while true:
  p.next()
  case p.kind
  of cmdEnd:
    break
  of cmdShortOption, cmdLongOption:
    if p.key == "":
      echo "Option: ", p.key
    else:
      echo "Option and value: ", p.key, ", ", p.val
  of cmdArgument:
    echo "Argument: ", p.key

info("Starting client")

a.magic = 0x50304601
a.addr_type = 4'u8

# Command line arguments.
a.addr = cast[array[16, uint8]]("192.168.1.5")

# linking error here.
handle_query(addr a, addr b)
echo(%* b)
# echo(b.magic, b.status, b.os_name, b.os_flavor, b.language)
