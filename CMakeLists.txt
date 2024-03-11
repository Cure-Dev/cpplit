cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(lit VERSION 0.0.0)

file(GLOB_RECURSE SOURCES "src/*.cpp")

include_directories("include")

add_executable(${PROJECT_NAME} ${SOURCES})

set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
add_custom_target(uninstall
  COMMAND xargs rm < install_manifest.txt
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMENT "Uninstalling...")