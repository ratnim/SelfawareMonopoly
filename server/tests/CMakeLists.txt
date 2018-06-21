#
# Configure test project and environment
#

# Function: Build test and add command to execute it via target 'run-tests'
function(add_test_without_ctest target)
    add_subdirectory(${target})
    
    if(NOT TARGET ${target})
        return()
    endif()
    
    add_dependencies(run-tests ${target})
    add_custom_command(TARGET run-tests POST_BUILD 
        COMMAND $<TARGET_FILE:${target}> --gtest_output=xml:gtests-${target}.xml)
endfunction()

# Build gmock
set(gmock_build_tests           OFF CACHE BOOL "")
set(gtest_build_samples         OFF CACHE BOOL "")
set(gtest_build_tests           OFF CACHE BOOL "")
set(gtest_disable_pthreads      OFF CACHE BOOL "")
set(gtest_force_shared_crt      ON  CACHE BOOL "")
set(gtest_hide_internal_symbols OFF CACHE BOOL "")

set(IDE_FOLDER "Tests")
add_subdirectory(googletest/googlemock)

# Create interface library to link against gmock
add_library(gmock-dev INTERFACE)
set_target_properties(gtest gtest_main gmock gmock_main PROPERTIES FOLDER "${IDE_FOLDER}")

target_include_directories(gmock-dev
    SYSTEM INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/include
    ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googlemock/include
)

target_link_libraries(gmock-dev
    INTERFACE
    gmock
)


# 
# Tests
# 

add_custom_target(run-tests)
set_target_properties(run-tests PROPERTIES EXCLUDE_FROM_DEFAULT_BUILD 1)

add_test_without_ctest(server-test)
