cmake_minimum_required(VERSION 3.10)
set(CXX_STANDARD 17)

project(ray-tracy)

## --- Compile SDL ---
# SDL is built in Release mode and then we revert to desired mode.
set(CMAKE_BUILD_TYPE_OLD "${CMAKE_BUILD_TYPE}")
set(CMAKE_CONFIGURATION_TYPES_OLD "${CMAKE_CONFIGURATION_TYPES}")
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CONFIGURATION_TYPES Release)
add_subdirectory(dep/SDL)
set(CMAKE_BUILD_TYPE "${CMAKE_BUILD_TYPE_OLD}")
set(CMAKE_CONFIGURATION_TYPES "${CMAKE_CONFIGURATION_TYPES_OLD}")

include_directories(dep/SDL/include)
set(SDL_LIBS SDL2 SDL2main)

## --- GLM ---
include_directories(dep/glm)

## --- GLFW ---
add_subdirectory(dep/GLFW)
include_directories(dep/glfw/include)
set(GLFW_LIBS glfw)

## --- Vulkan ---
find_package(Vulkan REQUIRED)
include_directories(${Vulkan_INCLUDE_DIRS})

## --- Compile actual project ---
set(
    SRC_COMMON src/display.cpp src/geom.cpp src/hittable.cpp src/camera.cpp
    src/light.cpp src/utils.cpp src/threading.cpp
)
include_directories(include)

add_executable(main src/main.cpp ${SRC_COMMON})
target_link_libraries(main ${SDL_LIBS} ${GLFW_LIBS})

add_executable(vk_test src/vulkan_test.cpp)
target_link_libraries(vk_test ${GLFW_LIBS} ${Vulkan_LIBRARIES})

## --- Copy DLL after build ---
file(
    COPY
    copyshared.cmake
    DESTINATION
    ${CMAKE_CURRENT_BINARY_DIR}
)
add_custom_command(
    TARGET main POST_BUILD                              # Adds a post-build event to main
    COMMAND ${CMAKE_COMMAND}                            # Run the cmake executable
    -DMY_DIR:STRING="${CMAKE_CURRENT_BINARY_DIR}"       # Pass the binary dir
    -DMY_SHR:STRING="${CMAKE_SHARED_LIBRARY_SUFFIX}"    # Pass the .dll or .so suffix
    -DMY_OUT:STRING="$<TARGET_FILE_DIR:main>"           # Pass the dir with main.exe
    -P copyshared.cmake                                 # Run copyshared script.
)                 