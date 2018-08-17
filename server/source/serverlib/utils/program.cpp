#include "program.h"

#include <watchers/lobbywatcher.h>
#include <models/accountmodel.h>
#include <models/gamemodel.h>
#include <models/boardmodel.h>
#include <utils/database.h>

Program::Program(const QString& databaseName)
{
    Database::reset(databaseName);
    AccountModel::reset();
    GameModel::reset();
    BoardModel::setBoardDir("./assets/boards");
    LobbyWatcher::reset();
}
