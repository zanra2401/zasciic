cmake_minimum_required(VERSION 4.3)
project(zasciic CXX)

find_package(stb REQUIRED)


add_executable(
  ${PROJECT_NAME}
  src/main.cpp
  src/stb.cpp
)

target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE
    stb::stb
)
