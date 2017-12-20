cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
project(HonoursProject)
SET(OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")


SET (EXE_LOCATION "${CMAKE_BINARY_DIR}/bin/")
SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${EXE_LOCATION})


file(GLOB_RECURSE SOURCE_FILES src/*.cpp src/*.h)

include_directories("${CMAKE_SOURCE_DIR}/SFML/include")
link_directories("${CMAKE_SOURCE_DIR}/SFML/lib")
link_directories("${CMAKE_SOURCE_DIR}/SFML/lib")

add_executable(HonoursProject ${SOURCE_FILES})

add_custom_target(copy_resources ALL
		COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/SFML/bin" "${EXE_LOCATION}/Debug"
		COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/SFML/bin" "${EXE_LOCATION}/Release"
)


target_link_libraries(HonoursProject
"sfml-graphics" 
"sfml-audio"
"openal32"
"sfml-main"
"sfml-system"
"sfml-window"
)


#target_link_libraries(HonoursProject 
#  optimized sfml-graphics debug sfml-graphics-d 
#  optimized sfml-audio debug sfml-audio-d 
#  optimized sfml-window debug sfml-window-d 
#  optimized sfml-system debug sfml-system-d 
#  optimized sfml-graphics debug sfml-graphics-d
# )

#add_dependencies(HonoursProject sfml-graphics)
add_dependencies(HonoursProject copy_resources)