cmake_minimum_required(VERSION 3.8)
project(chat_interface)

# Find required dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Create executable for chat_publisher
add_executable(chat_publisher src/chat_publisher.cpp)
ament_target_dependencies(chat_publisher rclcpp std_msgs)

# Create executable for chat_subscriber
add_executable(chat_subscriber src/chat_subscriber.cpp)
ament_target_dependencies(chat_subscriber rclcpp std_msgs)

# Install executables
install(TARGETS chat_publisher chat_subscriber
  DESTINATION lib/${PROJECT_NAME}
)

# Enable testing if required
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
