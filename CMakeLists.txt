cmake_minimum_required(VERSION 4.2)
project(DataStructures)


set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# message(STATUS Hello World)

# add subdirs here
add_subdirectory(vector)
add_subdirectory(ring-buffer)
# add_subdirectory(red-black-bst)
# add_subdirectory(stack)

add_executable(main_app main.cpp)

# add libraries here
target_link_libraries(main_app PRIVATE bd_vector_lib)
target_link_libraries(main_app PRIVATE bd_ringbuffer_lib)
# target_link_libraries(main_app PRIVATE my_red-black-bst_lib)
