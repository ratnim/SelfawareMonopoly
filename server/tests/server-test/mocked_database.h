#pragma once

#include <accountmodel.h>

struct ResetDatabase : Database
{
    ResetDatabase();
};

struct MockedDatabase : ResetDatabase
{
    MockedDatabase();

    AccountModel accounts;
};
