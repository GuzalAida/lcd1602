cmake_minimum_required(VERSION 3.1)
project(displayinfo4lcd)


set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

add_definitions("-Wl,-rpath,/opt/wiringPi/lib")
link_directories("/opt/wiringPi/lib")

include_directories("./displayinfo" "/opt/wiringPi/include/wiringPi" "/opt/wiringPi/include/wiringDev")

add_executable(${PROJECT_NAME} "displayinfo/displayinfo4lcd.c" "/opt/wiringPi/include/wiringPi/wiringPi.h" "/opt/wiringPi/include/wiringPi/wiringPiI2C.h" "/opt/wiringPi/include/wiringDev/lcd.h")
target_link_libraries(${PROJECT_NAME} PRIVATE wiringPi wiringPiDev)
