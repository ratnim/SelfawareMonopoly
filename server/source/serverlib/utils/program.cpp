#include "program.h"

#include <actions/lobbywatcher.h>
#include <models/accountmodel.h>
#include <models/gamemodel.h>
#include <utils/database.h>

Program::Program(const QString& databaseName)
{
    Database::reset(databaseName);
    AccountModel::reset();
    GameModel::reset();
    LobbyWatcher::reset();
}
