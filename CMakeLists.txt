cmake_minimum_required(VERSION 3.26)
project(LearnOpenGL)

set(CMAKE_CXX_STANDARD 23)

add_executable(LearnOpenGL src/glad.c src/Chap1_2Triangle/Triangle.cpp)

add_executable(CreateWindow src/glad.c src/Chap1_1CreateWindow/CreateWindow.cpp)

add_executable(Rectangle src/glad.c src/Chap1_2Triangle/Rectangle.cpp)

add_executable(TwoTriangle src/glad.c src/Chap1_2Triangle/TwoTriangle.cpp)

add_executable(GLSL src/glad.c src/Chap1_3Shader/GLSL.cpp)

add_executable(Uniform src/glad.c src/Chap1_3Shader/Uniform.cpp)

add_executable(ColorfulTriangle src/glad.c src/Chap1_3Shader/ColorfulTriangle.cpp)

add_executable(useGLSL src/glad.c src/Chap1_3Shader/useGLSL.cpp
         src/glad.c src/Chap1_3Shader/Shader.cpp
         src/glad.c include/Tool/Shader.h)

add_executable(Texture src/glad.c src/Chap1_4Texture/Texture.cpp
        include/Tool/stb_image.h
        include/Tool/Shader.h
        src/Chap1_3Shader/Shader.cpp)

add_executable(TransformTest src/glad.c src/Chap1_5Transform/TransformTest.cpp
        include/Tool/stb_image.h
        include/Tool/Shader.h
        src/Chap1_3Shader/Shader.cpp
)

add_executable(Coordinate src/glad.c src/Chap1_6Coordinate/Coordinate.cpp
        include/Tool/stb_image.h
        include/Tool/Shader.h
        src/Chap1_3Shader/Shader.cpp
)
add_executable(Cube src/glad.c src/Chap1_6Coordinate/CUbe.cpp
        include/Tool/stb_image.h
        include/Tool/Shader.h
        src/Chap1_3Shader/Shader.cpp
)
add_executable(LookAt src/glad.c src/Chap1_7Camera/LookAt.cpp
        include/Tool/stb_image.h
        include/Tool/Shader.h
        src/Chap1_3Shader/Shader.cpp
)
add_executable(FreeCamera src/glad.c src/Chap1_7Camera/FreeCamera.cpp
        include/Tool/stb_image.h
        include/Tool/Shader.h
        src/Chap1_3Shader/Shader.cpp
)
add_executable(Color src/glad.c src/Chap2_1Light/Color.cpp
        include/Tool/stb_image.h
        include/Tool/Shader.h
        include/Tool/Camera.h
        src/Chap1_3Shader/Shader.cpp
        src/Chap2_1Light/Lighting.frag
        src/Chap2_1Light/Lighting.vert
        src/Chap2_1Light/LightingSource.vert
        src/Chap2_1Light/LightingSource.frag
)
add_executable(AmbientLight src/glad.c src/Chap2_2BasicLight/AmbientLight.cpp
        include/Tool/stb_image.h
        include/Tool/Shader.h
        include/Tool/Camera.h
        src/Chap1_3Shader/Shader.cpp
        src/Chap2_2BasicLight/Lighting.frag
        src/Chap2_2BasicLight/Lighting.vert
        src/Chap2_1Light/LightingSource.vert
        src/Chap2_1Light/LightingSource.frag
)
add_executable(MaterialCube src/glad.c src/Chap2_3Material/Material.cpp
        include/Tool/stb_image.h
        include/Tool/Shader.h
        include/Tool/Camera.h
        src/Chap1_3Shader/Shader.cpp
        src/Chap2_4LightingMap/F_MaterialCube.frag
        src/Chap2_4LightingMap/V_MaterialCube.vert
        src/Chap2_1Light/LightingSource.vert
        src/Chap2_1Light/LightingSource.frag
)
add_executable(DiffuseMap src/glad.c src/Chap2_4LightingMap/DiffuseMap.cpp
        include/Tool/stb_image.h
        include/Tool/Shader.h
        include/Tool/Camera.h
        src/Chap1_3Shader/Shader.cpp
        src/Chap2_3Material/F_MaterialCube.frag
        src/Chap2_3Material/V_MaterialCube.vert
        src/Chap2_1Light/LightingSource.vert
        src/Chap2_1Light/LightingSource.frag
)
add_executable(ParallelLight src/glad.c src/Chap2_5LightCaster/ParallelLight.cpp
        include/Tool/stb_image.h
        include/Tool/Shader.h
        include/Tool/Camera.h
        src/Chap1_3Shader/Shader.cpp
        src/Chap2_3Material/F_MaterialCube.frag
        src/Chap2_3Material/V_MaterialCube.vert
        src/Chap2_1Light/LightingSource.vert
        src/Chap2_1Light/LightingSource.frag
)
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
target_link_libraries(useGLSL ${PROJECT_SOURCE_DIR}/lib/glfw3.dll)
target_link_libraries(Texture ${PROJECT_SOURCE_DIR}/lib/glfw3.dll)
target_link_libraries(TransformTest ${PROJECT_SOURCE_DIR}/lib/glfw3.dll)
target_link_libraries(Coordinate ${PROJECT_SOURCE_DIR}/lib/glfw3.dll)
target_link_libraries(Cube ${PROJECT_SOURCE_DIR}/lib/glfw3.dll)
target_link_libraries(LookAt ${PROJECT_SOURCE_DIR}/lib/glfw3.dll)
target_link_libraries(FreeCamera ${PROJECT_SOURCE_DIR}/lib/glfw3.dll)
target_link_libraries(Color ${PROJECT_SOURCE_DIR}/lib/glfw3.dll)
target_link_libraries(AmbientLight ${PROJECT_SOURCE_DIR}/lib/glfw3.dll)
target_link_libraries(MaterialCube ${PROJECT_SOURCE_DIR}/lib/glfw3.dll)
target_link_libraries(DiffuseMap ${PROJECT_SOURCE_DIR}/lib/glfw3.dll)
target_link_libraries(ParallelLight ${PROJECT_SOURCE_DIR}/lib/glfw3.dll)