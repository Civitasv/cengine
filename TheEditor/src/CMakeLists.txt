add_executable(TheEditor TheEditor.cpp EditorLayer.cpp "../../Sandbox/src/Sandbox2D.cpp")

target_include_directories(TheEditor PUBLIC 
	${CMAKE_SOURCE_DIR}/Cazel/include)

target_link_libraries(TheEditor PUBLIC Cazel)

set_target_properties(TheEditor
	PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}/${CMAKE_HOST_SYSTEM_PROCESSOR}/${PROJECT_NAME}/lib"
	LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}/${CMAKE_HOST_SYSTEM_PROCESSOR}/${PROJECT_NAME}/lib"
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}/${CMAKE_HOST_SYSTEM_PROCESSOR}/${PROJECT_NAME}/lib")
