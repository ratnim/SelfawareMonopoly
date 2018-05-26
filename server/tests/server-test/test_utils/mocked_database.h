#pragma once

#include <models/accountmodel.h>
#include <utils/database.h>

struct ResetDatabase : Database
{
    ResetDatabase();
};

struct MockedDatabase : ResetDatabase
{
    MockedDatabase();

    AccountModel accounts;
};
