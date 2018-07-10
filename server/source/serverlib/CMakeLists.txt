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
    actions/gamewatcher.cpp
    actions/gamewatcher.h
    actions/watcher.cpp
    actions/watcher.h
    actions/lobbywatcher.cpp
    actions/lobbywatcher.h
	game/dices.cpp
	game/dices.h
    game/game.cpp
    game/game.h
    game/player.cpp
    game/player.h
    game/jail.cpp
    game/jail.h
    game/state/state.h
    game/state/active.cpp
    game/state/active.h
    game/state/passive.cpp
    game/state/passive.h
    game/state/dead.cpp
    game/state/dead.h
    game/state/enter.cpp
    game/state/enter.h
    actions/gamewatcher.cpp
    actions/gamewatcher.h
    models/accountmodel.cpp
    models/accountmodel.h
    models/gamemodel.cpp
    models/gamemodel.h
    rest_apis/coinhive.cpp
    rest_apis/coinhive.h
    rest_apis/restAPIsBase.cpp
    rest_apis/restAPIsBase.h
    routes/route.cpp
    routes/route.h
    routes/routefactory.cpp
    routes/routefactory.h
    routes/gameroute.cpp
    routes/gameroute.h
    routes/lobbyroute.cpp
    routes/lobbyroute.h
    routes/overviewroute.cpp
    routes/overviewroute.h
    network/request.cpp
    network/request.h
    network/websocketserver.cpp
    network/websocketserver.h
    utils/configuration.cpp
    utils/configuration.h
    utils/database.cpp
    utils/database.h
    utils/exception.cpp
    utils/exception.h
    utils/program.cpp
    utils/program.h
    utils/staticstorage.h
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
