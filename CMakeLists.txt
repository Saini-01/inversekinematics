cmake_minimum_required(VERSION 3.10)
project(inverse_kinematics_project C)

# Add source files, including GLAD
add_executable(ik
    ik.c
    glad/src/glad.c
)

# Add include directories
target_include_directories(ik PRIVATE
    ${CMAKE_SOURCE_DIR}/glad/include
    ${CMAKE_SOURCE_DIR}/glfw-3.4/include
)

# Link GLFW
target_link_directories(ik PRIVATE
    ${CMAKE_SOURCE_DIR}/glfw-3.4/build/src
)
target_link_libraries(ik PRIVATE glfw)

# macOS frameworks required by GLFW
target_link_libraries(ik PRIVATE
    "-framework Cocoa"
    "-framework OpenGL"
    "-framework IOKit"
    "-framework CoreVideo"
)