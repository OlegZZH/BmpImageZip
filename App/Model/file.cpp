#include "file.h"

File::File(QObject *parent) : QObject(parent),name(""),size("") {
}

PROPERTY_IMPLEMENTATION(File, name, QString)
PROPERTY_IMPLEMENTATION(File, size, QString)
