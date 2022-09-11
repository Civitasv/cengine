file(GLOB_RECURSE _headers CONFIGURE_DEPENDS ${CMAKE_CURRENT_LIST_DIR}/Cazel/*.h)
target_sources(Cazel PRIVATE Cazel.h ${_headers})
unset(_headers)

target_precompile_headers(Cazel PRIVATE czpch.h)