cmake_minimum_required(VERSION 2.8)

project( ArucoDetection_2 )

find_package( OpenCV REQUIRED )

include_directories( OpenCV REQUIRED )

add_executable(single_image_detect single_image_detect.cpp)
add_executable(calibrate calibrate.cpp)

target_link_libraries(single_image_detect ${OpenCV_LIBS})
target_link_libraries(calibrate ${OpenCV_LIBS})
