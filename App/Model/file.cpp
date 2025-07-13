#include "file.h"

File::File(QObject *parent) : QObject(parent),name(""),size(0) {
}

PROPERTY_IMPLEMENTATION(File, name, QString)
PROPERTY_IMPLEMENTATION(File, size, qint64)
