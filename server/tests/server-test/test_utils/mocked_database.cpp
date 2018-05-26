#include "mocked_database.h"

ResetDatabase::ResetDatabase()
{
    database() = createDatabase();
}

MockedDatabase::MockedDatabase()
{
    accounts.createUser("registered_player");
}
