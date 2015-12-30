#ifndef WRITER_H
#define WRITER_H
#include <QThread>
#include <QString>
#include <QDataStream>

class ZippedBufferPool;
class ZippedBuffer;

/**
 * @brief La classe Writer est un thread
 * qui permet de d'écrire un fichier ECF
 */
class Writer: public QThread
{
public:
    /**
     * @brief Writer permet d'écrire le contenue d'un fichier ECF
     * @param zippedPool pool de données
     * @param fileEcfPath path complet du fichier ECF
     */
    Writer(ZippedBufferPool &zippedPool, const QString &fileEcfPath);
    /**
     * @brief run méthode du thread
     */
    virtual void run();

private:
    /**
     * @brief write écrit une partie d'un fichier et ajoute
     * les données dans le fichier ECF
     * @param zippedBuffer buffer à lire
     * @param stream stream d'écriture du fichier ECF
     */
    void write(ZippedBuffer &zippedBuffer, QDataStream &stream);
    /**
     * @brief zippedPool_ pool de données à remplir
     */
    ZippedBufferPool &zippedPool_;
    /**
     * @brief fileEcfPath_ path complet du fichier ECF
     */
    QString fileEcfPath_;
};

#endif // WRITER_H
