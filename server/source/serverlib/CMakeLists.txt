# 
# Library name and options
# 

# Target name
set(target serverlib)
message(STATUS "Lib ${target}")


# 
# Sources
# 

set(sources
    models/accountmodel.cpp
    models/accountmodel.h
    models/gamestate.cpp
    models/gamestate.h
    routes/route.cpp
    routes/route.h
    routes/routefactory.cpp
    routes/routefactory.h
    routes/game.cpp
    routes/game.h
    routes/lobby.cpp
    routes/lobby.h
    routes/overview.cpp
    routes/overview.h
    network/request.cpp
    network/request.h
    network/websocketserver.cpp
    network/websocketserver.h
    utils/configuration.cpp
    utils/configuration.h
    utils/database.cpp
    utils/database.h
)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${sources})

# 
# Create library
# 

add_library(${target} ${sources})


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

    PUBLIC
    ${DEFAULT_INCLUDE_DIRECTORIES}

    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)


# 
# Libraries
# 

target_link_libraries(${target}
    PRIVATE

    PUBLIC
    ${DEFAULT_LIBRARIES}
    Qt5::Core
    Qt5::Gui
    Qt5::Network
    Qt5::Sql
    Qt5::Widgets
    Qt5::WebSockets

    INTERFACE
)


# 
# Compile definitions
# 

target_compile_definitions(${target}
    PRIVATE

    PUBLIC
    $<$<NOT:$<BOOL:${BUILD_SHARED_LIBS}>>:${target_id}_STATIC_DEFINE>
    ${DEFAULT_COMPILE_DEFINITIONS}

    INTERFACE
)


# 
# Compile options
# 

target_compile_options(${target}
    PRIVATE

    PUBLIC
    ${DEFAULT_COMPILE_OPTIONS}

    INTERFACE
)


# 
# Linker options
# 

target_link_libraries(${target}
    PRIVATE

    PUBLIC
    ${DEFAULT_LINKER_OPTIONS}

    INTERFACE
)


#
# Target Health
#

perform_health_checks(
    ${target}
    ${sources}
    ${headers}
)
