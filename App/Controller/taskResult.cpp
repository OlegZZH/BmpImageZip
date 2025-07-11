#include "taskResult.h"

TaskResult::TaskResult(QObject *parent)
    : QObject{ parent }, result(QVariant(0)), status(false)
{
    connect(this,&TaskResult::statusChanged,this,&TaskResult::deleteLater);
}

PROPERTY_IMPLEMENTATION(TaskResult, status, bool)

PROPERTY_IMPLEMENTATION(TaskResult, result, QVariant)
