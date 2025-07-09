cmake_minimum_required(VERSION 3.10.0)

project(
  gix-dllist
  VERSION 0.1.0
  LANGUAGES C)

set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 17)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

option(GIX_DLL_BUILD_STATIC "Build static library" ON)
option(GIX_DLL_BUILD_SHARED "Build shared library" ON)

message(STATUS "BUILD TYPE " ${CMAKE_BUILD_TYPE})
message(STATUS "BUILD SHARED LIBRARY " ${GIX_DLL_BUILD_SHARED})
message(STATUS "BUILD STATIC LIBRARY " ${GIX_DLL_BUILD_STATIC})

if(NOT GIX_DLL_BUILD_STATIC AND NOT GIX_DLL_BUILD_SHARED)
  message(
    FATAL_ERROR
      "Library build type not defined. Set GIX_DLL_BUILD_SHARED or GIX_DLL_BUILD_STATIC to ON"
  )
endif()

# versioning
add_compile_definitions(GIX_DLL_MAJOR_VERSION=${PROJECT_VERSION_MAJOR})
add_compile_definitions(GIX_DLL_MINOR_VERSION=${PROJECT_VERSION_MINOR})
add_compile_definitions(GIX_DLL_PATCH_VERSION=${PROJECT_VERSION_PATCH})
add_compile_definitions(GIX_DLL_VERSION="${PROJECT_VERSION}")

# compiler flag
if(CMAKE_C_COMPILER_ID STREQUAL "MSVC")
  add_compile_options(/Wall)
  add_compile_options(/Wextra)
  # add_compile_options(/Werror)
else()
  add_compile_options(-Wall)
  add_compile_options(-Wextra)
  # add_compile_options(-Werror)
endif()

add_subdirectory(src)

if(GIX_DLL_BUILD_STATIC)
  target_include_directories(${PROJECT_NAME}-static
                             PUBLIC ${PROJECT_SOURCE_DIR}/src/include)
endif()

if(GIX_DLL_BUILD_SHARED)
  target_include_directories(${PROJECT_NAME}
                             PUBLIC ${PROJECT_SOURCE_DIR}/src/include)
endif()

# add test only on debug build
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  include(CTest)
  enable_testing()
  add_subdirectory(tests)
endif()
