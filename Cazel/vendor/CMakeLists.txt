set(GLFW_BUILD_DOCS
    OFF
    CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS
    OFF
    CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES
    OFF
    CACHE BOOL "" FORCE)

add_subdirectory(GLFW)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
add_subdirectory(spdlog)

add_subdirectory(GLAD)
add_subdirectory(imgui)
add_subdirectory(glm)