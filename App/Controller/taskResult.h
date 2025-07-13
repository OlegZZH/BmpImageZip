#ifndef TASKRESULT_H
#define TASKRESULT_H

#include <QObject>
#include <QVariant>
#include "App/macros.h"


class TaskResult : public QObject {
    Q_OBJECT

public:
    explicit TaskResult(QObject *parent = nullptr);

    PROPERTY_DEFINITION(status, bool)

    PROPERTY_DEFINITION(result, QVariant)

};

#endif // TASKRESULT_H
