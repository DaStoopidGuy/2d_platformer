cmake_minimum_required(VERSION 3.22.1)

project(2d_platformer)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")

add_executable(${PROJECT_NAME} "${SOURCE_FILES}")

target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/") # for development only
# target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="./resources/") #Uncomment this line to ship to client

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_PROJECT_DIR}/include/" )
target_link_libraries(${PROJECT_NAME} raylib m)
