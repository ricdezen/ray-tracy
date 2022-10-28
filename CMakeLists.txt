cmake_minimum_required(VERSION 3.10)
set(CXX_STANDARD 17)

project(ray-tracy)

## --- Compile SDL ---
add_subdirectory(dep/SDL)
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

if (MSVC)
    set_target_properties(main PROPERTIES LINK_FLAGS "/PROFILE")
endif()

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