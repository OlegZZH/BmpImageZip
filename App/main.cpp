// Copyright (C) 2024 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "logger.h"
#include "autogen/environment.h"
#include "Controller/asyncDecorator.h"
#include "Model/model.h"

int main(int argc, char *argv[])
{
    set_qt_environment();
    QApplication app(argc, argv);
    qSetMessagePattern(LOG_MESSAGE_PATTERN);
    QQmlApplicationEngine testAppView;
    Model testAppModel;

    AsyncDecorator testAppController(&testAppModel);
    const QUrl url(mainQmlFile);

    testAppView.rootContext()->setContextProperty("testAppModel", &testAppModel);
    testAppView.rootContext()->setContextProperty("testAppController", &testAppController);

    QObject::connect(
                &testAppView, &QQmlApplicationEngine::objectCreated, &app,
                [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    testAppView.addImportPath(QCoreApplication::applicationDirPath() + "/qml");
    testAppView.addImportPath(":/");
    testAppView.load(url);

    if (testAppView.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
