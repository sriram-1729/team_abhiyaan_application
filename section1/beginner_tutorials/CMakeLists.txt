cmake_minimum_required(VERSION 2.8.3)
project(beginner_tutorials)

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS roscpp rospy std_msgs genmsg geometry_msgs turtlesim)

## Declare ROS messages and services
add_message_files(FILES Phrase.msg AbhiyaanPose.msg Turtle1Velocity.msg)
add_service_files(FILES AddTwoInts.srv Turtle1.srv)

## Generate added messages and services
generate_messages(DEPENDENCIES std_msgs geometry_msgs turtlesim)

## Declare a catkin package
catkin_package()

## Build talker and listener
include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(talker src/talker.cpp)
target_link_libraries(talker ${catkin_LIBRARIES})
add_dependencies(talker beginner_tutorials_generate_messages_cpp)

add_executable(listener src/listener.cpp)
target_link_libraries(listener ${catkin_LIBRARIES})
add_dependencies(listener beginner_tutorials_generate_messages_cpp)

add_executable(publishernode src/publishernode.cpp)
target_link_libraries(publishernode ${catkin_LIBRARIES})
add_dependencies(publishernode beginner_tutorials_generate_messages_cpp)

add_executable(subscribernode src/subscribernode.cpp)
target_link_libraries(subscribernode ${catkin_LIBRARIES})
add_dependencies(subscribernode beginner_tutorials_generate_messages_cpp)

add_executable(add_two_ints_server src/add_two_ints_server.cpp)
target_link_libraries(add_two_ints_server ${catkin_LIBRARIES})
add_dependencies(add_two_ints_server beginner_tutorials_gencpp)

add_executable(add_two_ints_client src/add_two_ints_client.cpp)
target_link_libraries(add_two_ints_client ${catkin_LIBRARIES})
add_dependencies(add_two_ints_client beginner_tutorials_gencpp)

add_executable(turtle1_server src/turtle1_server.cpp)
target_link_libraries(turtle1_server ${catkin_LIBRARIES})
add_dependencies(turtle1_server beginner_tutorials_gencpp)

add_executable(turtle1_client src/turtle1_client.cpp)
target_link_libraries(turtle1_client ${catkin_LIBRARIES})
add_dependencies(turtle1_client beginner_tutorials_generate_messages_cpp beginner_tutorials_gencpp)

add_executable(turtle_exercise src/turtle_exercise.cpp)
target_link_libraries(turtle_exercise ${catkin_LIBRARIES})
add_dependencies(turtle_exercise beginner_tutorials_generate_messages_cpp)
