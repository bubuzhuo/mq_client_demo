cmake_minimum_required (VERSION 3.1)

project(mq_linux_target C)

# macro define...

# version setting
set(SOFTWAREVERSION_H 01)
set(SOFTWAREVERSION_L 000)


# json buffer size
set(JSON_BUFFER_LEN 4096)


#############################################################
###                     debug message
#############################################################
# log timestamp
set(DEBUG_TIME 1)



option(RSYSLOG "RSYSLOG..." OFF)
if(RSYSLOG)
add_definitions(-DRSYSLOG)
endif(RSYSLOG)

option(DEBUG_PRINTF "DEBUG..." OFF)
if(DEBUG_PRINTF)
add_definitions(-DDEBUG -DDEBUG_TIME)
endif(DEBUG_PRINTF)


############################################################## 
###                 Platform definition
##############################################################
option(DOCKER "Docker image..." OFF)
if(DOCKER)

else(DOCKER)
link_libraries("${PROJECT_SOURCE_DIR}/lib/_aarch64_MTK/librabbitmq.so")
endif(DOCKER)




SET(CMAKE_SYSTEM_NAME Linux)
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/target)
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -Wall")


configure_file(
    "${PROJECT_SOURCE_DIR}/mq_config_demo.h.in"
    "${PROJECT_BINARY_DIR}/mq_config_demo.h")


file(GLOB SOURCES
    "${PROJECT_SOURCE_DIR}/src/common/*.c"
	"${PROJECT_SOURCE_DIR}/src/log/*.c"
	"${PROJECT_SOURCE_DIR}/src/main/*.c"
	"${PROJECT_SOURCE_DIR}/src/cjson/*.c")

include_directories(
	"${PROJECT_BINARY_DIR}"
	"${PROJECT_SOURCE_DIR}/include"
    "${PROJECT_SOURCE_DIR}/src/common"
	"${PROJECT_SOURCE_DIR}/src/log"
	"${PROJECT_SOURCE_DIR}/src/main"
	"${PROJECT_SOURCE_DIR}/src/cjson"
)


link_libraries(pthread)
link_libraries(m)


add_executable(${PROJECT_NAME} ${SOURCES})

