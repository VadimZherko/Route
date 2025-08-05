#ifndef ACTION_H
#define ACTION_H

#include <QString>
#include "mark.h"

struct Action
{
public:
    Action(QString, Mark&);
    friend class MainWindow;

private:
    QString actionType;
    Mark& mark;
};

#endif // ACTION_H
