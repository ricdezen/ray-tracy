# Arguments:
# - MY_DIR: output directory containing all build files.
# - MY_SHR: suffix of shared libraries in the current system.
# - MY_OUT: output dir of shared libraries.
cmake_minimum_required(VERSION 3.10)

# Find shared library files.
file(
    GLOB_RECURSE
    SDL_SHARED
    "${MY_DIR}/dep/SDL/*${MY_SHR}"
)

# Copy them to output dir.
file(
    COPY
    ${SDL_SHARED}
    DESTINATION
    ${MY_OUT}
)