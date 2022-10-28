# ray-tracy

## Installation

The project just needs CMake and a few dependencies.

Most of the dependencies are included:
- [SDL](https://github.com/libsdl-org/SDL) and [glm](https://github.com/g-truc/glm)
    are git submodules inside `dep`. They do not need any extra configuration.
- [GLFW](https://github.com/glfw/glfw) is a submodule as well, but on Unix-like
    systems you need some extra dependencies, as explained
    [here](https://www.glfw.org/docs/latest/compile.html). Windows should be ok.
- [Vulkan](https://vulkan.lunarg.com/sdk/home) must be installed via the SDK.
    The `VULKAN_SDK` environment variable must be set to the root of the Vulkan
    installation for CMake to find it.