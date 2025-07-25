cmake_minimum_required(VERSION 3.14)

project(SpaceInvaders)

find_package(raylib 5.5 QUIET)

# This code downloads raylib into a directory called _deps and adds it as a subdirectory, compiling it with the program when running the build command
include(FetchContent)
if (NOT raylib_FOUND)
    FetchContent_Declare(
        raylib
        URL https://github.com/raysan5/raylib/archive/refs/tags/5.5.tar.gz
        DOWNLOAD_EXTRACT_TIMESTAMP True #This option is not required but suppresses a warning
    )
    FetchContent_MakeAvailable(raylib)
endif()

# We don't want raylib's examples built. This option is picked up by raylib's CMakeLists.txt
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_executable(SpaceInvaders)
target_sources(SpaceInvaders
    PRIVATE
        "src/main.cpp"
        "src/SpaceInvaders.cpp"
        "src/SpaceShip.cpp"
        "src/Laser.cpp"
        "src/Obstacle.cpp"
        "src/Block.cpp"
        "src/Alien.cpp"
        )

# Link raylib to SpaceInvaders
target_link_libraries(SpaceInvaders 
    raylib
)
# Make SpaceInvaders find the <raylib.h> header (and others)
target_include_directories(SpaceInvaders PUBLIC "${raylib_SOURCE_DIR}/src")

# Copy resources to build directory so the executable can find them locally
add_custom_command(TARGET SpaceInvaders POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources
        $<TARGET_FILE_DIR:SpaceInvaders>/resources
    COMMENT "Copying resources to build directory"
)

if (EMSCRIPTEN)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lidbfs.js -s USE_GLFW=3 --shell-file ${CMAKE_CURRENT_LIST_DIR}/web/minshell.html --preload-file ${CMAKE_CURRENT_LIST_DIR}/resources/@resources/ -s GL_ENABLE_GET_PROC_ADDRESS=1")
    set(CMAKE_EXECUTABLE_SUFFIX ".html") # This line is used to set your executable to build with the emscripten html template so that you can directly open it.
endif ()
