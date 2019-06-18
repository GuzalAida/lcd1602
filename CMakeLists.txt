cmake_minimum_required(VERSION 3.1)
project(displayLcdInfo)


set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

add_definitions("-Wl,-rpath,/opt/GuzalAida/lib")
link_directories("/opt/GuzalAida/lib")

include_directories("./displayinfo" "/opt/GuzalAida/include/wiringPi")

add_executable(${PROJECT_NAME} "displayinfo/displayinfo.c" "/opt/GuzalAida/include/wiringPi/wiringPi.h")
target_link_libraries(${PROJECT_NAME} PRIVATE wiringPi)
