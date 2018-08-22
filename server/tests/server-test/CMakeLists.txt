# 
# Executable name and options
# 

set(target server-test)
message(STATUS "Test ${target}")


# 
# Sources
# 

set(sources
    main.cpp
	tests/board_test.cpp
    tests/boardmodel_test.cpp
    tests/configuration_test.cpp
    tests/exception_test.cpp
    tests/fieldfactory_test.cpp
	tests/field_test.cpp
    tests/game_test.cpp
    tests/gameinfo_test.cpp
    tests/gamemodel_test.cpp
	tests/gameconnection_test.cpp
    tests/request_test.cpp
    tests/connection_test.cpp
    tests/runstate_test.cpp
    tests/websocketserver_test.cpp
    test_utils/mocked_database.cpp
    test_utils/mocked_database.h
    test_utils/mocked_server.cpp
    test_utils/mocked_server.h
)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${sources})

# 
# Create executable
# 

add_executable(${target} ${sources})

# 
# Project options
# 

set_target_properties(${target}
    PROPERTIES
    ${DEFAULT_PROJECT_OPTIONS}
    FOLDER "${IDE_FOLDER}"
)


# 
# Include directories
# 

target_include_directories(${target}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE
    ${DEFAULT_INCLUDE_DIRECTORIES}
)


# 
# Libraries
# 

target_link_libraries(${target}
    PRIVATE
    ${DEFAULT_LIBRARIES}
    serverlib
    gmock-dev
    Qt5::Test
)

# 
# Compile definitions
# 

target_compile_definitions(${target}
    PRIVATE
    ${DEFAULT_COMPILE_DEFINITIONS}
)


# 
# Compile options
# 

target_compile_options(${target}
    PRIVATE
    ${DEFAULT_COMPILE_OPTIONS}
)


# 
# Linker options
# 

target_link_libraries(${target}
    PRIVATE
    ${DEFAULT_LINKER_OPTIONS}
)
