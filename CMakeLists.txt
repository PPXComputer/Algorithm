cmake_minimum_required(VERSION 3.20)
project(Algorithm CXX)


SET(CMAKE_CXX_STANDARD 17)
# SET(CMAKE_CXX_FLAGS "-fsanitize=address")

#SET(DBG_MACRO_INCLUDE_DIRS "DEBUG")
SET(folly_DIR "D:\\Code\\tools\\vcpkg\\installed\\x64-windows\\share\\folly")
include_directories("D:/Code/tools/vcpkg/installed/x64-windows/include")
find_package(folly CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)
find_path(DBG_MACRO_INCLUDE_DIRS "dbg.h")
   
#find_package(libbsoncxx CONFIG REQUIRED)
#find_package(libmongocxx CONFIG REQUIRED)
 

  add_executable(Algorithm src/main.cpp src/ListAglo.cpp include/ListAglo.h src/StringAglo.cpp include/StringAglo.h src/ArrayAlgo.cpp include/ArrayAlgo.h src/UnionFindSet.cpp include/UnionFindSet.h src/GreedyAlgo.cpp include/GreedyAlgo.h include/Dynamic.h src/Dynamic.cpp src/SkipList.cpp include/SkipList.h  "include/pch.h" src/TreeAlgo.cpp include/TreeAlgo.h)
target_link_libraries(Algorithm PRIVATE GTest::gmock GTest::gtest GTest::gmock_main GTest::gtest_main)
target_link_libraries(Algorithm PRIVATE Folly::folly Folly::folly_deps Folly::follybenchmark Folly::folly_test_util)
target_include_directories(Algorithm PRIVATE ${DBG_MACRO_INCLUDE_DIRS})
 