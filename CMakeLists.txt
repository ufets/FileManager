cmake_minimum_required(VERSION 3.17)
project(lab4)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab4 main.cpp )
        #launch.cpp Dialog.cpp SystemDescriptor.cpp User.cpp DirDescriptor.cpp)

include_directories(c:/SFML/include)

set(SFML_ROOT c:/SFML)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake-modules")
find_package(SFML REQUIRED network audio graphics window system)

include_directories(${SFML_INCLUDE_DIR})
target_link_libraries(lab4 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})


#file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

# Copy dlls to build

