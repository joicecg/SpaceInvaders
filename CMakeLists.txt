cmake_minimum_required(VERSION 3.12)
project(SpaceInvaders)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#--- Find GLUT
find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIRS})
link_directories(${GLUT_LIBRARY_DIRS})
add_definitions(${GLUT_DEFINITIONS})
if(NOT GLUT_FOUND)
    message(ERROR " GLUT not found!")
endif(NOT GLUT_FOUND)


#--- Find OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)

find_package(GLEW REQUIRED)
if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})
    link_libraries(${GLEW_LIBRARIES})
endif()

include_directories(utils common/include)
link_directories(utils common/include)

file(GLOB_RECURSE SOURCES RELATIVE ${PROJECT_SOURCE_DIR} "envaders/*.cpp")
file(GLOB_RECURSE HEADERS RELATIVE ${PROJECT_SOURCE_DIR} "envaders/*.hpp")

add_executable(SpaceInvaders envaders/main.cpp common/include envaders utils ${HEADERS} ${SOURCES})
target_link_libraries(SpaceInvaders glfw ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${GLEW_LIBRARY})