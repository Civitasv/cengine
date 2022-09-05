# It's dynamic lib
add_library(Cazel SHARED Application.cpp Log.cpp "../../include/Cazel/Events/ApplicationEvent.h")

target_compile_definitions(Cazel PRIVATE 
	CZ_PLATFORM_WINDOWS CZ_BUILD_DLL)

target_include_directories(Cazel PUBLIC 
	${PROJECT_SOURCE_DIR}/include
	${PROJECT_SOURCE_DIR}/vendor/spdlog/include)

set_target_properties(Cazel
	PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}-${CMAKE_HOST_SYSTEM_PROCESSOR}/${PROJECT_NAME}/lib"
	LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}-${CMAKE_HOST_SYSTEM_PROCESSOR}/${PROJECT_NAME}/lib"
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}-${CMAKE_HOST_SYSTEM_PROCESSOR}/${PROJECT_NAME}/lib")

# After chaning Cazel, copy its dll to Sandbox
add_custom_command(TARGET Cazel POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different
	${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}-${CMAKE_HOST_SYSTEM_PROCESSOR}/Cazel/lib/Cazel.dll
	${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}-${CMAKE_HOST_SYSTEM_PROCESSOR}/Sandbox/lib/)