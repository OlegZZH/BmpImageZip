
#ifndef FILE_H
#define FILE_H
#include <QObject>

#include "App/macros.h"


class File : public QObject {
    Q_OBJECT

public:
    explicit File(QObject *parent = nullptr);

    PROPERTY_DEFINITION(name, QString)
    PROPERTY_DEFINITION(size, QString)


};



#endif //FILE_H
