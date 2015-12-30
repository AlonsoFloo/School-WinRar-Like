#include "winuscompressor.h"
#include "filepool.h"
#include "zippedbufferpool.h"
#include "writer.h"
#include "reader.h"
#include "zipper.h"

#include <QThread>
#include <QDir>
#include <list>
#include <memory>
#include <iostream>


using namespace std;

WinUsCompressor::WinUsCompressor(const int threadCount) :
    threadCount_(threadCount)
{
}

void WinUsCompressor::compress(const QString &folder, const QString &ecfFileName)
{
    FilePool pool(folder);
    ZippedBufferPool zippedPool;

    typedef unique_ptr<Zipper> ZipperPtr;
    list<ZipperPtr> zippers;
    for(int i = 0;i < threadCount_;++i) {
        auto ptr = new Zipper(pool, zippedPool, folder, true);
        zippers.push_back(ZipperPtr(ptr));
        zippers.back()->start();
    }

    auto writerPtr = new Writer(zippedPool, ecfFileName);
    writerPtr->start();

    while(zippers.empty() == false) {
        zippers.front()->wait();
        zippers.pop_front();
    }
    zippedPool.done();

    writerPtr->wait();
    delete writerPtr;
}

void WinUsCompressor::uncompress(const QString &ecfFileName, const QString &folder)
{
    ZippedBufferPool zippedPool;
    auto readerPtr = new Reader(zippedPool, ecfFileName);
    readerPtr->start();

    FilePool pool(folder);

    typedef unique_ptr<Zipper> ZipperPtr;
    list<ZipperPtr> zippers;
    for(int i = 0;i < threadCount_;++i) {
        auto ptr = new Zipper(pool, zippedPool, folder, false);
        zippers.push_back(ZipperPtr(ptr));
        zippers.back()->start();
    }

    readerPtr->wait();

    zippedPool.done();

    while(zippers.empty() == false) {
        zippers.front()->wait();
        zippers.pop_front();
    }
    delete readerPtr;
}
