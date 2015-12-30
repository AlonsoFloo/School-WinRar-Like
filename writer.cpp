#include "writer.h"
#include "zippedbuffer.h"
#include "zippedbufferpool.h"

#include <iostream>
#include <QFile>
#include <QDir>

Writer::Writer(ZippedBufferPool &zippedPool, const QString &fileEcfPath) :
    zippedPool_(zippedPool), fileEcfPath_(fileEcfPath)
{
}

void Writer::run()
{
    QFile file(fileEcfPath_);
    QFileInfo fileInfo(fileEcfPath_);
    QDir dir(QDir::root());
    dir.mkpath(fileInfo.absoluteDir().absolutePath());

    if (file.open(QFile::WriteOnly | QFile::Truncate) == true) {
        QDataStream stream(&file);
        QPair<bool,ZippedBuffer> zippedFilePair;
        zippedFilePair = zippedPool_.tryGet();

        while(zippedFilePair.first) {
            write(zippedFilePair.second, stream);
            zippedFilePair = zippedPool_.tryGet();;
        }

        file.close();
    } else {
        std::cout << "Impossible d'ouvrir le fichier ECF" << std::endl;
    }
}

void Writer::write(ZippedBuffer &zippedBuffer, QDataStream &stream)
{
    zippedBuffer.write(stream);
}
