#include "filesListModel.h"

FilesListModel::FilesListModel(QObject *parent): QAbstractListModel(parent) {
}

int FilesListModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return m_files.size();
}

QVariant FilesListModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() < 0 || index.row() >= m_files.size())
        return {};

    File *file = m_files[index.row()];
    switch (role) {
        case NameRole: return file->name;
        case SizeRole: return file->size;
        default: return {};
    }
}

QHash<int, QByteArray> FilesListModel::roleNames() const {
    return {
        {NameRole, "name"},
        {SizeRole, "size"}
    };
}

void FilesListModel::addFile(File *file) {
    beginInsertRows(QModelIndex(), m_files.size(), m_files.size());
    m_files.append(file);
    endInsertRows();
}
