cmake_minimum_required(VERSION 2.8)

project( ArucoDetection_2 )

find_package( OpenCV REQUIRED )

include_directories( OpenCV REQUIRED )

set(HEADER_FILES src/aruco_dictionary_strings.h)

add_executable(single_image_detect src/single_image_detect.cpp ${HEADER_FILES})
add_executable(calibrate src/calibrate.cpp ${HEADER_FILES})
add_executable(single_image_estimate_pose src/single_image_estimate_pose.cpp ${HEADER_FILES})
add_executable(video_estimate_pose src/video_estimate_pose.cpp ${HEADER_FILES})

target_link_libraries(single_image_detect ${OpenCV_LIBS})
target_link_libraries(calibrate ${OpenCV_LIBS})
target_link_libraries(single_image_estimate_pose ${OpenCV_LIBS})
target_link_libraries(video_estimate_pose ${OpenCV_LIBS})
