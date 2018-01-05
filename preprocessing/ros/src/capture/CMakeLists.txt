cmake_minimum_required(VERSION 2.8.3)
project(capture)

set(OpenCV_INCLUDE_DIRS /usr/local)

set(OpenCV_LIBS /usr/local/lib/libopencv_core.so)

find_package(OpenCV REQUIRED)

find_package(catkin REQUIRED COMPONENTS
  cv_bridge
  image_transport
  message_filters
  roscpp
  rospy
  sensor_msgs
  std_msgs
  pcl_conversions
  pcl_ros roscpp
  sensor_msgs
  visualization_msgs
)


catkin_package(
)



###########
## Build ##
###########

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(
  ${catkin_INCLUDE_DIRS}
)



## Declare a C++ executable
add_executable(image_read src/rosbag_capture.cpp)

## Specify libraries to link a library or executable target against
target_link_libraries(image_read ${OpenCV_LIBS} ${catkin_LIBRARIES} )