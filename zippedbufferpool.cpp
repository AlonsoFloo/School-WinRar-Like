#include "zippedbufferpool.h"

#include <QMutexLocker>

ZippedBufferPool::ZippedBufferPool()
{
    isAlimented_ = true;
}

void ZippedBufferPool::put(ZippedBuffer &zb)
{
    QMutexLocker locker(&mutex_);
    zippedBufferList_.push_back(zb);
    waitCondition_.wakeOne();
}

QPair<bool,ZippedBuffer> ZippedBufferPool::tryGet()
{
    QMutexLocker locker(&mutex_);
    if (isAlimented_ && zippedBufferList_.isEmpty()) {
        waitCondition_.wait(&mutex_);
    }
	
    ZippedBuffer zippedBuffer;
    bool fileIsValid = isAlimented_ || !zippedBufferList_.isEmpty();
    if (fileIsValid) {
        zippedBuffer = zippedBufferList_.front();
        zippedBufferList_.pop_front();
    }

    QPair<bool,ZippedBuffer> zippedFile(fileIsValid, zippedBuffer);

    return zippedFile;
}

void ZippedBufferPool::done()
{
    isAlimented_ = false;
    waitCondition_.wakeAll();
}
