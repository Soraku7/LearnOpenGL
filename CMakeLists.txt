cmake_minimum_required(VERSION 3.26)
project(LearnOpenGL)

set(CMAKE_CXX_STANDARD 23)

add_executable(LearnOpenGL src/glad.c src/Triangle/Triangle.cpp)

add_executable(CreateWindow src/glad.c src/CreateWindow/CreateWindow.cpp)

add_executable(Rectangle src/glad.c src/Triangle/Rectangle.cpp)
#file (GLOB_RECURSE files *.cpp)
#foreach (file ${files})
#    string(REGEX REPLACE ".+/(.+)\\..*" "\\1" exe ${file})
#    add_executable (${exe} ${file})
#    message (\ \ \ \ --\ src/${exe}.cpp\ will\ be\ compiled\ to\ bin/${exe})
#endforeach ()


INCLUDE_DIRECTORIES(include)
link_directories(lib)
target_link_libraries(LearnOpenGL ${PROJECT_SOURCE_DIR}/lib/glfw3.dll)
target_link_libraries(CreateWindow ${PROJECT_SOURCE_DIR}/lib/glfw3.dll)
target_link_libraries(Rectangle ${PROJECT_SOURCE_DIR}/lib/glfw3.dll)