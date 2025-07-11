#include "model.h"

Model::Model(QObject *parent) : QObject(parent), currentPath(""), saveToPath(""), filesListModel(new FilesListModel) {
}

PROPERTY_IMPLEMENTATION(Model, currentPath, QString)
PROPERTY_IMPLEMENTATION(Model, mode, Mode)
PROPERTY_IMPLEMENTATION(Model, saveToPath, QString)
PROPERTY_IMPLEMENTATION(Model, filesListModel, FilesListModel*)
