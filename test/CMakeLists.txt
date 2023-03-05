# 载入 GTest 命令
find_package(GTest REQUIRED)

#add_executable(main "")
#target_sources(main PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}//src/main.cpp")

# 为该目录中所有源码添加一个可执行文件 testRunner
add_executable(testRunner "")
find_package(folly CONFIG REQUIRED)
#find_package(GTest CONFIG REQUIRED)
find_path(DBG_MACRO_INCLUDE_DIRS "dbg.h")
find_package(GTest CONFIG REQUIRED)

# 将所有 .cpp 文件添加到编译 src 目录下的源码及头文件一起运行测试
file(GLOB_RECURSE SRC_FILES ../src/*.cpp ../include/*.h *.cpp)
foreach (SOURCE_FILE IN LISTS SRC_FILES)
    if (NOT SOURCE_FILE MATCHES "../src/main.cpp")
        target_sources(testRunner PRIVATE ${SOURCE_FILE})
    endif ()
endforeach ()

# 添加依赖项
target_link_libraries(testRunner PRIVATE GTest::GTest GTest::Main)

# 设置一些参数
set_target_properties(testRunner PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/test")

# 下面的命令将在构建时自动发现并运行测试
enable_testing()
add_test(NAME UnitTest COMMAND testRunner)

# 添加依赖项
target_link_libraries(testRunner PRIVATE GTest::GTest GTest::Main)
target_link_libraries(testRunner PRIVATE Folly::folly)
target_include_directories(testRunner PRIVATE ${DBG_MACRO_INCLUDE_DIRS})
target_link_libraries(testRunner PRIVATE GTest::gtest GTest::gtest_main)

# 设置一些参数
set_target_properties(testRunner PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/test")

# 下面的命令将在构建时自动发现并运行测试
