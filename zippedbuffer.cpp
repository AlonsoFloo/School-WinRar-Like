#include "zippedbuffer.h"

ZippedBuffer::ZippedBuffer(const QString &path, const QByteArray &data) :
    path_(path), data_(data)
{
}

void ZippedBuffer::write(QDataStream &stream)
{
    stream << path_;
    stream << data_;
}

void ZippedBuffer::read(QDataStream &stream)
{
    stream >> path_;
    stream >> data_;
}


QString ZippedBuffer::getPath() const
{
    return path_;
}

QByteArray ZippedBuffer::getData() const
{
    return data_;
}
