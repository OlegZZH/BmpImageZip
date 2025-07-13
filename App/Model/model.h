#ifndef MODEL_H
#define MODEL_H

#include <QObject>

#include "filesListModel.h"
#include "App/macros.h"

enum class Mode { PACK, UNPACK };

class Model : public QObject {
    Q_OBJECT

public:
    explicit Model(QObject *parent = nullptr);

    PROPERTY_DEFINITION(currentPath, QString)

    PROPERTY_DEFINITION(currentFile, File*)

    PROPERTY_DEFINITION(mode, Mode)

    PROPERTY_DEFINITION(saveToPath, QString)

    PROPERTY_DEFINITION(filesListModel, FilesListModel*)
};


#endif //MODEL_H
