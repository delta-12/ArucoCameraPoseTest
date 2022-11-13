cmake_minimum_required(VERSION 2.8)

project( ArucoDetection_2 )

find_package( OpenCV REQUIRED )

include_directories( OpenCV REQUIRED )

add_executable(single_image_detect src/single_image_detect.cpp)
add_executable(calibrate src/calibrate.cpp)
add_executable(single_image_estimate_pose src/single_image_estimate_pose.cpp)

target_link_libraries(single_image_detect ${OpenCV_LIBS})
target_link_libraries(calibrate ${OpenCV_LIBS})
target_link_libraries(single_image_estimate_pose ${OpenCV_LIBS})
