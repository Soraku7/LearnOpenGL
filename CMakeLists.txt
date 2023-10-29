cmake_minimum_required(VERSION 3.26)
project(LearnOpenGL)

set(CMAKE_CXX_STANDARD 23)

add_executable(Trigger src/glad.c src/Trigger/Trigger.cpp)

add_executable(LearnOpenGL src/glad.c src/CreateWindow/CreateWindow.cpp)

#file (GLOB_RECURSE files *.cpp)
#foreach (file ${files})
#    string(REGEX REPLACE ".+/(.+)\\..*" "\\1" exe ${file})
#    add_executable (${exe} ${file})
#    message (\ \ \ \ --\ src/${exe}.cpp\ will\ be\ compiled\ to\ bin/${exe})
#endforeach ()


INCLUDE_DIRECTORIES(include)
link_directories(lib)
target_link_libraries(LearnOpenGL ${PROJECT_SOURCE_DIR}/lib/glfw3.dll)