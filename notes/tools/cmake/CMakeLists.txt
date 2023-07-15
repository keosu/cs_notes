cmake_minimum_required(VERSION 3.8)
project(Tutorial)

set(Tutorial_VERSION_MAJOR 1)
set(Tutorial_VERSION_MINOR 0)

# 配置一个头文件，通过它向源代码中传递一些CMake的设置。
configure_file(
    "${PROJECT_SOURCE_DIR}/mymathConfig.h.in"
    "${PROJECT_BINARY_DIR}/mymathConfig.h"
)

# 将二进制文件树添加到包含文件的搜索路径中，这样我们可以找到TutorialConfig.h
include_directories("${PROJECT_BINARY_DIR}")

# 是否使用自定义的math库作为库函数
option(USE_MYMATH "Use tutorial provided math implementation" On)
if(USE_MYMATH)
    include_directories("${PROJECT_SOURCE_DIR}/math")
    add_subdirectory(math)
    set(EXTERNAL_LIBS ${EXTERNAL_LIBS} sqrt)
endif(USE_MYMATH)

add_executable(sample src/main.cpp)
target_link_libraries(sample ${EXTERNAL_LIBS})