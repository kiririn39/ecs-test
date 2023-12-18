cmake_minimum_required(VERSION 3.27)
project(untitled1)

set(CMAKE_CXX_STANDARD 23)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS Game/*.cpp Game/*.h Engine/*.cpp Engine/*.h)
add_executable(untitled1 main.cpp ${SOURCES})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)
set(FETCHCONTENT_TRY_FIND_PACKAGE_MODE ALWAYS)


# raylib
find_package(raylib QUIET)
if (NOT raylib_FOUND)
    include(FetchContent)
    FetchContent_Declare(
            raylib
            GIT_REPOSITORY https://github.com/raysan5/raylib.git
    )
    FetchContent_MakeAvailable(raylib)
endif ()

# raylib-cpp
find_package(raylib_cpp QUIET)
if (NOT raylib_cpp_FOUND)
    include(FetchContent)
    FetchContent_Declare(
            raylib_cpp
            GIT_REPOSITORY https://github.com/RobLoach/raylib-cpp.git
    )
    FetchContent_MakeAvailable(raylib_cpp)
endif ()

FetchContent_Declare(fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git)
FetchContent_MakeAvailable(fmt)

#set(BOX2D_BUILD_TESTBED OFF CACHE BOOL "" FORCE)
#FetchContent_Declare(box2d
#        GIT_REPOSITORY https://github.com/erincatto/box2d.git
#        GIT_TAG main)
#FetchContent_MakeAvailable(box2d)

FetchContent_Declare(flecs
        GIT_REPOSITORY https://github.com/SanderMertens/flecs.git)
FetchContent_MakeAvailable(flecs)

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    message(STATUS "Building in Release mode")
    add_definitions(-DFLECS_NDEBUG=1 -DFLECS_NO_APP=1 -DFLECS_NO_PLECS=1)

    if (MSVC)
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2 /GL")
        set(CMAKE_C_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2 /GL")
        set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /LTCG")
    else ()
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -flto")
        set(CMAKE_C_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -flto")
        set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -flto")
    endif ()

elseif (CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Building in a Debug configuration")

    add_definitions(-DFLECS_DEBUG=1)
endif ()

FetchContent_Declare(mathfu
        GIT_REPOSITORY https://github.com/google/mathfu.git)
FetchContent_MakeAvailable(mathfu)

set(mathfu_build_benchmarks OFF CACHE BOOL "")
set(mathfu_build_tests OFF CACHE BOOL "")
mathfu_configure_flags(${PROJECT_NAME})

install(TARGETS untitled1)

target_link_libraries(${PROJECT_NAME} PUBLIC raylib raylib_cpp fmt flecs)

add_custom_command(
        TARGET untitled1 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Game/Resources
        $<TARGET_FILE_DIR:untitled1>/Resources
)

target_include_directories(untitled1 PUBLIC ${CMAKE_SOURCE_DIR})
