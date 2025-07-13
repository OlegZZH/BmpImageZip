#include "controller.h"
#include <QDir>

#include <qcoreapplication.h>


Controller::Controller(Model *model, QObject *parent): model(model), QObject(parent) {
    qDebug() << "App started";
    selectPath(QCoreApplication::applicationDirPath());
}

void Controller::selectPackMode() {
    model->set_mode(Mode::PACK);
}

void Controller::selectUnpackMode() {
    model->set_mode(Mode::UNPACK);
}

void Controller::selectPath(const QString &path) {
    qDebug() << "Selected path:" << path;
    model->set_currentPath(path);
    model->set_saveToPath(path);
    updateFilesListModel();
}

void Controller::selectFile(const int fileIndex) {
    auto file = model->filesListModel->getFile(fileIndex);
    qDebug() << "Selected file:" << file->name;

    QFileInfo fileInfo(file->name);
    QString extension = fileInfo.suffix();
    if (extension == "bmp") {
        selectPackMode();
    } else if (extension == "barch") {
        selectUnpackMode();
    }

    model->set_currentFile(file);
}

void Controller::selectSaveAsPath(const QString &path) {
    qDebug() << "Save path:" << path;
    model->set_saveToPath(path);
}

void Controller::saveFile(const QString &name) {
    qDebug()<<"Save file:" << name<<" to "<<model->saveToPath;
    if (model->mode==Mode::PACK) {
        saveBarch(tempData, (model->saveToPath+"/"+name).toStdString());
    }
    else if (model->mode==Mode::UNPACK) {
        saveAsGrayscaleBMP(tempData, (model->saveToPath+"/"+name).toStdString());
    }
}

void Controller::convert() {
    qDebug() << "Convert";
    QFileInfo fileInfo(model->currentFile->name);
    QString extension = fileInfo.suffix();
    if (extension == "png") {
        throw std::runtime_error("Unsupported png");
    }
    if (model->mode==Mode::PACK) {
        tempData = loadGrayscaleBMP((model->currentPath+"/"+model->currentFile->name).toStdString());
    }
    else if (model->mode==Mode::UNPACK) {
        tempData = loadBarch((model->currentPath+"/"+model->currentFile->name).toStdString());
    }
}

void Controller::updateFilesListModel() {
    qDebug() << "Update files list model";
    QDir dir(model->currentPath);

    QStringList nameFilters;
    nameFilters << "*.png" << "*.bmp" << "*.barch";

    QStringList files = dir.entryList(nameFilters, QDir::Files);
    model->filesListModel->clear();
    for (const QString &fileName: files) {
        QFileInfo fileInfo(dir.absoluteFilePath(fileName));
        QString name = fileInfo.fileName();
        qint64 size = fileInfo.size();

        auto file = new File();
        file->set_name(name);
        file->set_size(size);
        model->filesListModel->addFile(file);
    }

}
