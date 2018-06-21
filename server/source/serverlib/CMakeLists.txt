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
    game/gameinfo.cpp
    game/gameinfo.h
    game/player.cpp
    game/player.h
    game/state/gamestate.cpp
    game/state/gamestate.h
    game/state/endstate.cpp
    game/state/endstate.h
    game/state/initstate.cpp
    game/state/initstate.h
    game/state/runstate.cpp
    game/state/runstate.h
    game/state/active/freestate.cpp
    game/state/active/freestate.h
    game/state/active/jailstate.cpp
    game/state/active/jailstate.h
    game/state/active/movestate.cpp
    game/state/active/movestate.h
    game/state/active/playerstate.cpp
    game/state/active/playerstate.h
    game/state/active/rollstate.cpp
    game/state/active/rollstate.h
    actions/gamewatcher.cpp
    actions/gamewatcher.h
    models/accountmodel.cpp
    models/accountmodel.h
    models/gamemodel.cpp
    models/gamemodel.h
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
    utils/budhist.h
    utils/configuration.cpp
    utils/configuration.h
    utils/database.cpp
    utils/database.h
    utils/exception.cpp
    utils/exception.h
    utils/program.cpp
    utils/program.h
    utils/ringbuffer.h
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
