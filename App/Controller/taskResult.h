#ifndef TASKRESULT_H
#define TASKRESULT_H

#include <QObject>
#include <QVariant>
#include "macros.h"


class TaskResult : public QObject {
    Q_OBJECT

public:
    explicit TaskResult(QObject *parent = nullptr);

    PROPERTY_DEFINITION(status, bool)

    PROPERTY_DEFINITION(result, QVariant)

};

#endif // TASKRESULT_H
