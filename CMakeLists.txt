cmake_minimum_required(VERSION 3.20)
project(Algorithm CXX)

set(CMAKE_CXX_STANDARD 17)

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

include_directories(SYSTEM ./include)
include_directories(SYSTEM ./src)

find_package(folly CONFIG REQUIRED)
#find_package(GTest CONFIG REQUIRED)
find_path(DBG_MACRO_INCLUDE_DIRS "dbg.h")
find_program(ccache_exe "C:\\Tools\\ccache-4.7.4-windows-x86_64\\ccache.exe")
if (ccache_exe)

    set(CMAKE_VS_GLOBALS
            "CLToolExe=cl.exe"
            "CLToolPath=${CMAKE_BINARY_DIR}"
            "TrackFileAccess=false"
            "UseMultiToolTask=true"
            "DebugInformationFormat=OldStyle"
            )
endif ()

file(GLOB SRC_FILES src/*.cpp)
file(GLOB HEAD_FILES include/*.h)

add_executable(Algorithm ${SRC_FILES} ${HEAD_FILES})
#target_link_libraries(Algorithm PRIVATE  GTest::gtest  GTest::gtest_main)
target_link_libraries(Algorithm PRIVATE Folly::folly)
target_include_directories(Algorithm PRIVATE ${DBG_MACRO_INCLUDE_DIRS})
# target_link_libraries(Algorithm PRIVATE gflags::gflags)
