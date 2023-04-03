# It's dynamic lib
add_library(Cazel SHARED Application.cpp Log.cpp Layer.cpp LayerStack.cpp)

target_include_directories(Cazel PUBLIC ${PROJECT_SOURCE_DIR}/include)

find_package(OpenGL REQUIRED)
target_link_libraries(Cazel spdlog glfw OpenGL::GL)

set_target_properties(
  Cazel
  PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY
    "${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}-${CMAKE_HOST_SYSTEM_PROCESSOR}/${PROJECT_NAME}/lib"
    LIBRARY_OUTPUT_DIRECTORY
    "${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}-${CMAKE_HOST_SYSTEM_PROCESSOR}/${PROJECT_NAME}/lib"
    RUNTIME_OUTPUT_DIRECTORY
    "${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}-${CMAKE_HOST_SYSTEM_PROCESSOR}/${PROJECT_NAME}/lib"
)
