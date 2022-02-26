These are changes made in the repository to the official version 3.09b.

- 2021-04-11: Fixed ASan error in lookup_hdr function by increasing the malloc
  by `ALLOC_OFF` in `alloc-inl.h` file. 
- 2021-04-11: Removed deprecated `pcap_lookupdev` by `pcap_findalldevs`. Added
  a new function `find_interface_unix` to search of device that can be opened.
- 2021-04-11: Reorganized the source tree.
- 2021-04-11: Added cmake build system.
