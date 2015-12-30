#include "filepool.h"
#include <QDir>
#include <QMutexLocker>


FilePool::FilePool(const QString &folder) : folder_(folder)
{
    findFileInFolderAndSubfolders(folder);
}

void FilePool::findFileInFolderAndSubfolders(const QString &folder)
{
    QDir dir(folder);

    foreach (const QFileInfo &entry,
             dir.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot)) {

        if( entry.isDir() == true )
        {
            findFileInFolderAndSubfolders(entry.filePath());
        } else if(entry.isFile() == true) {
            files_.append(entry.absoluteFilePath());
        }
    }
}

int FilePool::count() {
    QMutexLocker locker(&mutex_);
    return files_.size();
}

QString FilePool::tryGetFile() {
    QMutexLocker locker(&mutex_);
    QString file;

    if(files_.isEmpty() == false) {
        file = files_.front();
        files_.pop_front();
    }
    return file;
}
