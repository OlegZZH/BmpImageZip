#ifndef FILESLISTMODEL_H
#define FILESLISTMODEL_H

#include <QAbstractListModel>

#include "file.h"

class FilesListModel : public QAbstractListModel {
    Q_OBJECT

public:
    enum FileRoles {
        NameRole = Qt::UserRole + 1,
        SizeRole
    };

    explicit FilesListModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override ;

    QVariant data(const QModelIndex &index, int role) const override ;

    QHash<int, QByteArray> roleNames() const override ;

    void addFile(File *file) ;

private:
    QList<File *> m_files;
};


#endif //FILESLISTMODEL_H
