cmake_minimum_required(VERSION 3.10)
project(inverse_kinematics_project C)

# Source files
add_executable(ik
    ik.c
    glad/src/glad.c
)

# Include directories (GLAD + GLFW headers)
target_include_directories(ik PRIVATE
    ${CMAKE_SOURCE_DIR}/glad/include
    /Users/adityasaini/Downloads/glfw-3.4/include
)


set(GLFW_LIB /Users/adityasaini/Downloads/glfw-3.4/build/src/libglfw3.a)

# Link GLFW + macOS frameworks
target_link_libraries(ik PRIVATE ${GLFW_LIB}
    "-framework Cocoa"
    "-framework OpenGL"
    "-framework IOKit"
    "-framework CoreVideo"
)