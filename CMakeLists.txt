cmake_minimum_required(VERSION 3.20)

project(MinecraftGL)

# Will save all files corresponding to the "src/*.cpp" 
# regex in the SRC_FILES variable
file(GLOB_RECURSE SRC_FILES 
src/*.cpp 
src/graphics/*.cpp 
src/models/*.cpp 
src/utils/*.cpp)
add_executable(${PROJECT_NAME} ${SRC_FILES})

# Modern OpenGL subdirectory ("add_subdirectory" needs a CMakeLists.txt
# in the directory)
add_subdirectory(lib/glad)
# OpenGL Context (Cross-platform windowing)
add_subdirectory(lib/glfw)
# OpenGL Mathematics Library for matrix and vector operations
add_subdirectory(lib/glm)

set(PROJECT_SRC_DIR ${CMAKE_SOURCE_DIR}/src)

# Directories where the "include" macro can look for
target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SRC_DIR}/graphics      # Self-made h/hpp files
    PUBLIC ${PROJECT_SRC_DIR}/models
    PUBLIC ${PROJECT_SRC_DIR}/utils
    PUBLIC lib/glad/include                 # Modern OpenGL
    PUBLIC lib/glfw/include                 # Windowing lib
    PUBLIC lib/glm                          # OpenGL Mathematics
)

# Directories for the linking process
target_link_directories(${PROJECT_NAME}
    PRIVATE lib/glad/src
    PRIVATE lib/glfw/src
)

# Variable LIBS with all used libraries
set(LIBS glad glfw glm)

target_link_libraries(${PROJECT_NAME} ${LIBS})