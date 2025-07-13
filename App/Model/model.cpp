#include "model.h"

Model::Model(QObject *parent) : QObject(parent), currentPath(""),currentFile(nullptr), saveToPath(""), filesListModel(new FilesListModel) {
}

PROPERTY_IMPLEMENTATION(Model, currentPath, QString)
PROPERTY_IMPLEMENTATION(Model, currentFile, File*)
PROPERTY_IMPLEMENTATION(Model, mode, Mode)
PROPERTY_IMPLEMENTATION(Model, saveToPath, QString)
PROPERTY_IMPLEMENTATION(Model, filesListModel, FilesListModel*)
