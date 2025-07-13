#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QObject>

#include "App/Model/model.h"
#include "compressor.h"


class Controller : public QObject {
    Q_OBJECT

public:
    explicit Controller(Model *model, QObject *parent = nullptr);

public slots:
    void selectPackMode();

    void selectUnpackMode();

    void selectPath(const QString &path);

    void selectFile(int fileIndex);

    void selectSaveAsPath(const QString &path);

    void saveFile(const QString &name);

    void convert();

signals:
    void notifyUserSignal(QString message);

protected:
    Model *model;
    void updateFilesListModel();
    RawImageData tempData;
};


#endif //CONTROLLER_H
