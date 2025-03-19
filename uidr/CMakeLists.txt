cmake_minimum_required(VERSION 3.10)
project(udir C)

# 设置 C 标准
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# 添加可执行文件
add_library(uidr SHARED
    uidr.c
)

target_include_directories(uidr PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(uidr PUBLIC
    pthread
)
