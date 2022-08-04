cmake_minimum_required(VERSION 3.20)
project(Algorithm CXX)
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
set(CMAKE_CXX_STANDARD 17)

include_directories(
        ${PROJECT_SOURCE_DIR}/include/
)
aux_source_directory(
      ./src SRC_FILES
)

#find_package(gflags CONFIG REQUIRED)
#find_package(Boost REQUIRED COMPONENTS context filesystem program_options regex system thread)
find_package(folly CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)
find_path(DBG_MACRO_INCLUDE_DIRS "dbg.h")
add_executable(Algorithm src/main.cpp src/ListAglo.cpp include/ListAglo.h
        src/StringAglo.cpp include/StringAglo.h src/ArrayAlgo.cpp include/ArrayAlgo.h src/UnionFindSet.cpp include/UnionFindSet.h src/GreedyAlgo.cpp include/GreedyAlgo.h include/Dynamic.h src/Dynamic.cpp src/SkipList.cpp include/SkipList.h src/TreeAlgo.cpp include/LeetCode.h src/LeetCode.cpp "include/LeetCode200.h" "src/LeetCode200.cpp" src/Offer.cpp include/Offer.h)
target_link_libraries(Algorithm PRIVATE GTest::gmock GTest::gtest GTest::gmock_main GTest::gtest_main)
target_link_libraries(Algorithm PRIVATE Folly::folly Folly::folly_deps Folly::follybenchmark Folly::folly_test_util)
target_include_directories(Algorithm PRIVATE ${DBG_MACRO_INCLUDE_DIRS})
target_link_libraries(Algorithm PRIVATE gflags::gflags)