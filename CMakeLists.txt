cmake_minimum_required(VERSION 3.16)

project(ArduiPi VERSION 0.0.1)

add_library(${PROJECT_NAME}_lib STATIC
    Adafruit_GFX.cpp
    ArduiPi_OLED.cpp
    bcm2835.c
)

target_include_directories(${PROJECT_NAME}_lib INTERFACE ./)
target_link_libraries(${PROJECT_NAME}_lib i2c)

add_executable(oled_demo examples/oled_demo.cpp)

target_link_libraries(oled_demo PUBLIC ${PROJECT_NAME}_lib)
