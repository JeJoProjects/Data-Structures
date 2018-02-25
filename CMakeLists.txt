cmake_minimum_required(VERSION 3.1)

project("Project_Data_Structures")

file(GLOB SOURCES
   *.h   
   *.hpp   
   *.cc
   *.cpp
 )
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
#target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
#install(TARGETS ${PROJECT_NAME}  RUNTIME DESTINATION bin)

add_executable(${PROJECT_NAME} ${SOURCES})
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
