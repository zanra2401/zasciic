cmake_minimum_required(VERSION 4.3)
project(zasciic CXX)

find_package(stb REQUIRED)


add_executable(
  ${PROJECT_NAME}
  src/main.cpp
  src/stb.cpp
  src/ascii.cpp
  src/commandCenter.cpp
  src/image.cpp
)

target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE
    stb::stb
)
