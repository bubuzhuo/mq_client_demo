set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

add_definitions(-DFUXI)

# set the toolchain path
set(TOOL_CHAIN_DIR /home/lanceli/csky-linux-gnuabiv2-tools-x86_64-glibc-linux)


# set the toolchain lib & include files
set(TOOL_CHAIN_INCLUDE ${TOOL_CHAIN_DIR}/include)
set(TOOL_CHAIN_LIB ${TOOL_CHAIN_DIR}/lib)


# set the compiler
set(CMAKE_C_COMPILER "${TOOL_CHAIN_DIR}/bin/csky-abiv2-linux-gcc")

# set the cmake find root path
set(CMAKE_FIND_ROOT_PATH ${TOOL_CHAIN_DIR})

# search for programs in the build host directories (not necessary)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

# 只在指定目录下查找库文件,只在指定目录下查找头文件,只在指定目录下查找依赖包
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

set(CMAKE_INCLUDE_PATH ${TOOL_CHAIN_INCLUDE})
set(CMAKE_LIBRARY_PATH ${TOOL_CHAIN_LIB})