cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
project(HonoursProject)
SET(OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")


#SET (EXE_LOCATION "${CMAKE_BINARY_DIR}/bin/")
SET (EXE_LOCATION "${CMAKE_BINARY_DIR}/")
SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${EXE_LOCATION})


file(GLOB_RECURSE SOURCE_FILES src/*.cpp src/*.h)

include_directories("${CMAKE_SOURCE_DIR}/SFML/include")
link_directories("${CMAKE_SOURCE_DIR}/SFML/lib")
link_directories("${CMAKE_SOURCE_DIR}/SFML/lib")

add_executable(HonoursProject ${SOURCE_FILES})





#attempting to get textures to work//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#copy General resources to build post build script
add_custom_command(TARGET HonoursProject POST_BUILD  
  COMMAND ${CMAKE_COMMAND} -E copy_directory  "${PROJECT_SOURCE_DIR}/res" $<TARGET_FILE_DIR:HonoursProject>>/res)

if(${MSVC})
  #set outDir as debugging directory
  #This doesn't work yet?
  #set_target_properties(Astral_Insanity_main PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "$(TargetDir)")
  
  file( WRITE "${CMAKE_CURRENT_BINARY_DIR}/HonoursProject.vcxproj.user" 
    "<?xml version=\"1.0\" encoding=\"utf-8\"?>
    <Project ToolsVersion=\"4.0\" xmlns=\"http://schemas.microsoft.com/developer/msbuild/2003\">
    <PropertyGroup Condition=\"'$(Configuration)|$(Platform)'=='Debug|x64'\">
      <LocalDebuggerWorkingDirectory>$(TargetDir)</LocalDebuggerWorkingDirectory>
      <DebuggerFlavor>WindowsLocalDebugger</DebuggerFlavor>
    </PropertyGroup>
    <PropertyGroup Condition=\"'$(Configuration)|$(Platform)'=='Release|x64'\">
      <LocalDebuggerWorkingDirectory>$(TargetDir)</LocalDebuggerWorkingDirectory>
      <DebuggerFlavor>WindowsLocalDebugger</DebuggerFlavor>
    </PropertyGroup>
  </Project>")
		
  target_compile_options(HonoursProject PUBLIC /MP)

else()

endif()

#/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




add_custom_target(copy_resources ALL
		COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/SFML/bin" "${EXE_LOCATION}/Debug"
		COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/SFML/bin" "${EXE_LOCATION}/Release"

		COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/res/PNG/Cards" "${EXE_LOCATION}/Debug/Cards"
		COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/res/PNG/Cards" "${EXE_LOCATION}/Release/Cards"

		
		COMMAND ${CMAKE_COMMAND} -E copy_directory  
		"${EXE_LOCATION}/GameRecords" "${CMAKE_SOURCE_DIR}/GameRecords"

		COMMAND ${CMAKE_COMMAND} -E copy_directory  
		"${CMAKE_SOURCE_DIR}/GameRecords" "${EXE_LOCATION}/GameRecords"

		#COMMAND ${CMAKE_COMMAND} -E copy_directory
        #"${CMAKE_SOURCE_DIR}/res/PNG/Cards" "${CMAKE_BINARY_DIR}"
)


#target_link_libraries(HonoursProject
#"sfml-graphics" 
#"sfml-audio"
#"openal32"
#"sfml-main"
#"sfml-system"
#"sfml-window"
#)


target_link_libraries(HonoursProject 
  optimized sfml-graphics debug sfml-graphics-d 
  optimized sfml-audio debug sfml-audio-d 
  optimized sfml-window debug sfml-window-d 
  optimized sfml-system debug sfml-system-d 
  optimized sfml-graphics debug sfml-graphics-d
 )

#add_dependencies(HonoursProject sfml-graphics)
add_dependencies(HonoursProject copy_resources)