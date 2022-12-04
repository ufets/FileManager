cmake_minimum_required(VERSION 3.21)
project(lab4)

set(CMAKE_CXX_STANDARD 20)
set(SRC main.cpp
        Dialog/DActions.cpp
        Launcher/launch.cpp
        Dialog/Dialog.cpp
        SystemSource/SystemDescriptor.cpp
        SystemSource/User.cpp
        Descriptors/AccessTable.cpp
        Descriptors/Descriptor.cpp
        Descriptors/FileDescriptor.cpp
        #MyMap/mymap.cpp MyMap/mymap.h
        )
add_executable(lab4 ${SRC})

include_directories(c:/SFML/include)

set(SFML_ROOT c:/SFML)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake-modules")
find_package(SFML REQUIRED network audio graphics window system)

include_directories(${SFML_INCLUDE_DIR})
target_link_libraries(lab4 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})


#file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

# Copy dlls to build

add_subdirectory(_GTEST)
