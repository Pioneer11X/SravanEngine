#Build Instructions. Add the Libraries..
#Add the Source Directory in VC++ Directories to the Source Directory.

cmake_minimum_required (VERSION 3.1)
set(CMAKE_CXX_STANDARD 11)

project(SravanEngine)

file(GLOB PC_SRC "${CMAKE_CURRENT_SOURCE_DIR}/Source/*")

add_executable(SravanEngine ${PC_SRC})

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/Deps/includes/")

find_package(OpenGL)

IF (OPENGL_FOUND)

    include_directories(${OPENGL_INCLUDE_DIR})
    target_link_libraries(SravanEngine ${OPENGL_LIBRARIES})

ENDIF (OPENGL_FOUND)

target_link_libraries(SravanEngine "${CMAKE_CURRENT_SOURCE_DIR}/Deps/libs/glfw3.lib")
