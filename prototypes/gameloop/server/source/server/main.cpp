#include <iostream>

#include <QApplication>
#include <QDebug>

#include <database.h>
#include <symbol.h>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    Database db;
    db.send("I'm alive with value: ");

	qDebug() << db.receive() << value;
}
