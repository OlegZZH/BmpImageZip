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
        {NameRole, "nameRole"},
        {SizeRole, "sizeRole"}
    };
}

void FilesListModel::addFile(File *file) {
    beginInsertRows(QModelIndex(), m_files.size(), m_files.size());
    m_files.append(file);
    endInsertRows();
}

void FilesListModel::clear() {
    beginResetModel();

    for (File *file: m_files) {
        if (file)
            file->deleteLater();
    }

    m_files.clear();
    endResetModel();
}

File *FilesListModel::getFile(int index) const {
    if (index >= 0 && index < m_files.size())
        return m_files[index];
    return nullptr;
}
