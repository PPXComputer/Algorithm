cmake_minimum_required(VERSION 3.20)
project(Algorithm CXX)

set(CMAKE_CXX_STANDARD 17)
set(Boost_NO_WARN_NEW_VERSIONS 1)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/Debug/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/Release/bin)

# 使用多线程编译
if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  add_compile_options(/MP)

# 禁用 RTTI 

  add_compile_options(/GR)

# 根据目标平台进行优化

  if("${CMAKE_SIZEOF_VOID_P}" STREQUAL "8")
    add_compile_options("/favor:INTEL64")
  else()
    add_compile_options("/favor:INTEL32")
  endif()
endif ()
# 判断是否为msvc编译器添加以下编译选项

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/source-charset:utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/source-charset:utf-8>")
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/execution-charset:utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/execution-charset:utf-8>")


find_package(folly CONFIG REQUIRED)
#find_package(GTest CONFIG REQUIRED)
find_path(DBG_MACRO_INCLUDE_DIRS "dbg.h")
find_package(GTest CONFIG REQUIRED)
# 判断是为windows 系统然后判断这个东西是否存在 并且设置 CMake_VS_GLOBALS
if (WIN32)
    if (EXISTS "C:\\Tools\\ccache-4.7.4-windows-x86_64\\ccache.exe")
        set(CMAKE_VS_GLOBALS
                "CLToolExe=cl.exe"
                "CLToolPath=${CMAKE_BINARY_DIR}"
                "TrackFileAccess=false"
                "UseMultiToolTask=true"
                "DebugInformationFormat=OldStyle"
        )
    endif ()
endif ()
# 添加头文件搜索路径
include_directories(${PROJECT_SOURCE_DIR}/include)
# 获取该目录下所有源文件
aux_source_directory(src SRC_FILES)

add_executable(Algorithm ${SRC_FILES} ${HEAD_FILES})
#target_link_libraries(Algorithm PRIVATE  GTest::gtest  GTest::gtest_main)
target_link_libraries(Algorithm PRIVATE Folly::folly)
target_include_directories(Algorithm PRIVATE ${DBG_MACRO_INCLUDE_DIRS})
target_link_libraries(Algorithm PRIVATE GTest::gtest GTest::gtest_main)

# target_link_libraries(Algorithm PRIVATE gflags::gflags)
add_subdirectory(test)
