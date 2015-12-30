#include "zipper.h"
#include "filepool.h"
#include "zippedbuffer.h"
#include "zippedbufferpool.h"

#include <QFile>
#include <QDir>
#include <QTextStream>

Zipper::Zipper(FilePool &pool, ZippedBufferPool &zippedPool, const QString &folder, const bool isCompressMode) :
    pool_(pool), zippedPool_(zippedPool), isCompressMode_(isCompressMode), folder_(folder)
{
}

void Zipper::run()
{
    if (isCompressMode_) {
        runCompress();
    } else {
        runUnCompress();
    }
}

void Zipper::runCompress() {
    QString filename;
    filename = pool_.tryGetFile();

    while(filename != "") {
        compressFile(filename);
        filename = pool_.tryGetFile();
    }
}

void Zipper::runUnCompress() {
    QPair<bool,ZippedBuffer> zippedFilePair;
    zippedFilePair = zippedPool_.tryGet();

    while(zippedFilePair.first) {
        unCompressFile(zippedFilePair.second);
        zippedFilePair = zippedPool_.tryGet();
    }
}

void Zipper::compressFile(const QString &filename)
{
    QFile file(filename);
    if( file.open(QFile::ReadOnly) == true) {
        QByteArray arrayCompressed = qCompress(file.readAll());

        if(arrayCompressed.size() > 0){
            QString relativePath = filename.mid(folder_.size(),filename.size());
            ZippedBuffer buffer(relativePath, arrayCompressed);
            zippedPool_.put(buffer);
        }
        file.close();
     }
}


void Zipper::unCompressFile(const ZippedBuffer &zippedBuffer)
{
    QString filename(folder_);
    filename.append(zippedBuffer.getPath());
    QFile file(filename);

    QFileInfo fileInfo(filename);
    QDir dir(QDir::root());
    dir.mkpath(fileInfo.absoluteDir().absolutePath());

    if(file.open(QFile::WriteOnly | QFile::Truncate) == true) {
        QDataStream stream(&file);
        QByteArray arrayUnCompressed = qUncompress(zippedBuffer.getData());
        stream.writeRawData(arrayUnCompressed.constData(),arrayUnCompressed.size());

        file.close();
     }
}
