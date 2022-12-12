# 'Google_test' is the subproject name
project(Google_tests)

# 'lib' is the folder with Google Test sources
add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(SOURCE
        ../Dialog/DActions.cpp
        ../Launcher/launch.cpp
        ../Dialog/Dialog.cpp
        ../SystemSource/SystemDescriptor.cpp
        ../SystemSource/User.cpp
        ../Descriptors/AccessTable.cpp
        ../Descriptors/Descriptor.cpp
        ../Descriptors/FileDescriptor.cpp
        ../Descriptors/DirDescriptor.cpp
        ../MyMap/mymap.cpp

        )

set( TESTS
        #test_system_descriptor.cpp
        #test_access_table.cpp
        test_descriptor.cpp
        #FileDesctiptor_test.cpp
        test_dirdescriptor.cpp
        test_map.cpp)
# 'Google_Tests_run' is the target name
# 'test1.cpp tests2.cpp' are source files with tests
add_executable(Google_Tests_run ${SOURCE} ${TESTS} )
target_link_libraries(Google_Tests_run gtest gtest_main)