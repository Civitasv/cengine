# It's dynamic lib
add_library(Cazel SHARED Application.cpp Log.cpp Layer.cpp LayerStack.cpp)

target_include_directories(Cazel PUBLIC ${PROJECT_SOURCE_DIR}/include)

find_package(OpenGL REQUIRED)
target_link_libraries(Cazel PUBLIC spdlog glfw glad imgui OpenGL::GL)

set_target_properties(
  Cazel
  PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY
    "${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}/${CMAKE_HOST_SYSTEM_PROCESSOR}/${PROJECT_NAME}/lib"
    LIBRARY_OUTPUT_DIRECTORY
    "${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}/${CMAKE_HOST_SYSTEM_PROCESSOR}/${PROJECT_NAME}/lib"
    RUNTIME_OUTPUT_DIRECTORY
    "${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}/${CMAKE_HOST_SYSTEM_PROCESSOR}/${PROJECT_NAME}/lib"
)

add_custom_command(TARGET Cazel POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different
	${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}/${CMAKE_HOST_SYSTEM_PROCESSOR}/${PROJECT_NAME}/lib/${PROJECT_NAME}.dll
	${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}/${CMAKE_HOST_SYSTEM_PROCESSOR}/Sandbox/lib/)

add_subdirectory(imgui)