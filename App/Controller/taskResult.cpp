#include "taskResult.h"

TaskResult::TaskResult(QObject *parent)
    : QObject{parent}, result(QVariant(0)), status(false) {
    connect(this, &TaskResult::statusChanged, this, &TaskResult::deleteLater);
}

void TaskResult::set_status(bool newStatus) {
    status = newStatus;
    emit statusChanged(newStatus);
}

PROPERTY_IMPLEMENTATION(TaskResult, result, QVariant)
