# 
# Executable name and options
# 

# Target name
set(target server)


# 
# Sources
# 

set(sources
    main.cpp
)


# 
# Create executable
# 

add_executable(${target}
    MACOSX_BUNDLE
    ${sources}
)

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


#
# Target Health
#

perform_health_checks(
    ${target}
    ${sources}
)
