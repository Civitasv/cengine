add_executable(Sandbox SandboxApp.cpp Sandbox2D.cpp ExampleLayer.cpp)

target_include_directories(Sandbox PUBLIC 
	${CMAKE_SOURCE_DIR}/Cazel/include)

target_link_libraries(Sandbox PUBLIC Cazel)

set_target_properties(Sandbox
	PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}/${CMAKE_HOST_SYSTEM_PROCESSOR}/${PROJECT_NAME}/lib"
	LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}/${CMAKE_HOST_SYSTEM_PROCESSOR}/${PROJECT_NAME}/lib"
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}/${CMAKE_HOST_SYSTEM_PROCESSOR}/${PROJECT_NAME}/lib")
