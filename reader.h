#ifndef READER_H
#define READER_H
#include <QThread>
#include <QString>
#include <QDataStream>

class ZippedBufferPool;
class ZippedBuffer;


/**
 * @brief La class Reader est un thread
 * qui permet de lire un fichier ECF
 */
class Reader : public QThread
{
public:
    /**
     * @brief Reader permet de lire le contenue d'un fichier ECF
     * et l'ajoute au ZippedBufferPool
     * @param zippedPool pool de données
     * @param fileEcfPath path complet du fichier ECF
     */
    Reader(ZippedBufferPool &zippedPool, const QString &fileEcfPath);
    /**
     * @brief run méthode du thread
     */
    virtual void run();

private:
    /**
     * @brief read lit une partie d'un fichier et ajoute
     * les données dans un ZippedBuffer
     * @param zippedBuffer buffer à remplir
     * @param stream stream de lecture du fichier ECF
     */
    void read(ZippedBuffer &zippedBuffer, QDataStream &stream);

    /**
     * @brief zippedPool_ pool de données à remplir
     */
    ZippedBufferPool &zippedPool_;
    /**
     * @brief fileEcfPath_ path complet du fichier ECF
     */
    QString fileEcfPath_;
};

#endif // READER_H
