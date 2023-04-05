if (CMAKE_SYSTEM_NAME MATCHES "Linux")
    # Linux specific configuration
    add_subdirectory(Linux)
elseif (CMAKE_SYSTEM_NAME MATCHES "Windows")
    # Windows specific configuration
    add_subdirectory(Windows)
elseif (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    # macOS specific configuration
else()
    message(FATAL_ERROR "Unsupported operating system")
endif()

add_subdirectory(OpenGL)