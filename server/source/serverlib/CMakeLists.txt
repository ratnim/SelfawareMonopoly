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
    watchers/gamewatcher.cpp
    watchers/gamewatcher.h
    watchers/watcher.cpp
    watchers/watcher.h
    watchers/lobbywatcher.cpp
    watchers/lobbywatcher.h
    game/dices.cpp
    game/dices.h
    game/game.cpp
    game/game.h
    game/gameinfo.cpp
    game/gameinfo.h
    game/player.cpp
    game/player.h   
    game/watson.cpp
    game/watson.h
    game/bank/bank.cpp
    game/bank/bank.h
    game/board/board.cpp
    game/board/board.h
    game/board/field.cpp
    game/board/field.h
    game/board/ownablefield.cpp
    game/board/ownablefield.h
    game/board/fieldfactory.cpp
    game/board/fieldfactory.h
    game/board/start.cpp
    game/board/start.h
    game/board/street.cpp
    game/board/street.h
    game/board/station.cpp
    game/board/station.h
    game/board/utility.cpp
    game/board/utility.h
    game/board/gotojail.cpp
    game/board/gotojail.h
    game/board/taxfield.cpp
    game/board/taxfield.h
    game/turn/endstate.cpp
    game/turn/endstate.h
    game/turn/buystate.cpp
    game/turn/buystate.h
    game/turn/initstate.cpp
    game/turn/initstate.h
    game/turn/idlestate.cpp
    game/turn/idlestate.h
    game/turn/jailstate.cpp
    game/turn/jailstate.h
    game/turn/jailbuyoutstate.cpp
    game/turn/jailbuyoutstate.h
    game/turn/paystate.cpp
    game/turn/paystate.h
    game/turn/turnstate.cpp
    game/turn/turnstate.h
    game/turn/movestate.cpp
    game/turn/movestate.h
    game/turn/possiblerequest.cpp
    game/turn/possiblerequest.h
    models/accountmodel.cpp
    models/accountmodel.h
    models/boardmodel.cpp
    models/boardmodel.h
    models/gamemodel.cpp
    models/gamemodel.h
    connections/connection.cpp
    connections/connection.h
    connections/connectionfactory.cpp
    connections/connectionfactory.h
    connections/gameconnection.cpp
    connections/gameconnection.h
    connections/lobbyconnection.cpp
    connections/lobbyconnection.h
    connections/overviewconnection.cpp
    connections/overviewconnection.h
    network/connectionrequest.cpp
    network/connectionrequest.h
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
