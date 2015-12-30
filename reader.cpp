#include "reader.h"
#include "zippedbuffer.h"
#include "zippedbufferpool.h"

#include <iostream>
#include <QFile>

Reader::Reader(ZippedBufferPool &zippedPool, const QString &fileEcfPath) :
    zippedPool_(zippedPool), fileEcfPath_(fileEcfPath)
{
}

void Reader::run()
{
    QFile file(fileEcfPath_);
    if (file.open(QFile::ReadOnly) == true) {
        QDataStream stream(&file);
        int found = 0;

        while (!stream.atEnd()) {
            ZippedBuffer zippedBuffer;
            read(zippedBuffer, stream);
            zippedPool_.put(zippedBuffer);
            ++found;
        }

        file.close();
    } else {
        std::cout << "Impossible d'ouvrir le fichier ECF" << std::endl;
    }
}

void Reader::read(ZippedBuffer &zippedBuffer, QDataStream &stream)
{
    zippedBuffer.read(stream);
}
