#ifndef ASYNCDECORATOR_H
#define ASYNCDECORATOR_H

#include "taskResult.h"
#include <QtConcurrent/QtConcurrentRun>

#include "controller.h"
#include "App/Model/model.h"


class AsyncDecorator : public Controller {
    Q_OBJECT

public:
    explicit AsyncDecorator(Model *model) : Controller(model) {
    };

public slots:
    TaskResult *convert() {
        auto result = new TaskResult();
        auto future = QtConcurrent::run([this, result]() {
            try {
                Controller::convert();
                result->set_status(true);
            } catch (const std::exception &ex) {
                qWarning() << "Error: " << ex.what() ;
                result->set_status(false);
                emit notifyUserSignal(ex.what());
            }
        });
        return result;
    }

    TaskResult *saveFile(const QString &name) {
        auto result = new TaskResult();
        auto future = QtConcurrent::run([this, result, name]() {
            Controller::saveFile(name);
            result->set_status(true);
        });
        return result;
    }
};


#endif //ASYNCDECORATOR_H
