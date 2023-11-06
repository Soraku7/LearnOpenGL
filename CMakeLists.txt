cmake_minimum_required(VERSION 3.26)
project(LearnOpenGL)

set(CMAKE_CXX_STANDARD 23)

add_executable(LearnOpenGL src/glad.c src/Triangle/Triangle.cpp)

add_executable(CreateWindow src/glad.c src/CreateWindow/CreateWindow.cpp)

add_executable(Rectangle src/glad.c src/Triangle/Rectangle.cpp)

add_executable(TwoTriangle src/glad.c src/Triangle/TwoTriangle.cpp)

add_executable(GLSL src/glad.c src/Shader/GLSL.cpp)

add_executable(Uniform src/glad.c src/Shader/Uniform.cpp)

add_executable(ColorfulTriangle src/glad.c src/Shader/ColorfulTriangle.cpp)

add_executable(Shader src/glad.c src/Shader/Shader.cpp)

add_executable(useGLSL src/glad.c src/Shader/useGLSL.cpp
         src/glad.c src/Shader/Shader.cpp
         src/glad.c include/Tool/Shader.h)

add_executable(Texture src/glad.c src/Texture/Texture.cpp
        include/Tool/stb_image.h
        include/Tool/Shader.h
        src/Shader/Shader.cpp)

add_executable(TransformTest src/glad.c src/Transform/TransformTest.cpp)
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
target_link_libraries(TwoTriangle ${PROJECT_SOURCE_DIR}/lib/glfw3.dll)
target_link_libraries(GLSL ${PROJECT_SOURCE_DIR}/lib/glfw3.dll)
target_link_libraries(Uniform ${PROJECT_SOURCE_DIR}/lib/glfw3.dll)
target_link_libraries(ColorfulTriangle ${PROJECT_SOURCE_DIR}/lib/glfw3.dll)
target_link_libraries(Shader ${PROJECT_SOURCE_DIR}/lib/glfw3.dll)
target_link_libraries(useGLSL ${PROJECT_SOURCE_DIR}/lib/glfw3.dll)
target_link_libraries(Texture ${PROJECT_SOURCE_DIR}/lib/glfw3.dll)