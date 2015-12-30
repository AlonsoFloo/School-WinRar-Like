#ifndef ZIPPER_H
#define ZIPPER_H
#include <QThread>
/**
 * @brief La classe Zipper compressera le contenu des fichiers qu’elle récupèrera dans
 * le FilePool. Chaque fichier compressé est stocké dans une instance de la classe ZippedBuffer. Cette
 * instance est ajoutée au pool de fichiers compressés à écrire ZippedBufferPool..
 * Elle peut aussi décompresser des fichiers depuis le ZippedBufferPool et écrire le fichier sur le disque.
 */
class FilePool;
class ZippedBufferPool;
class ZippedBuffer;

class Zipper: public QThread
{
public:

    /**
     * @brief La classe Zipper hérite de QThread. Elle compressera le contenu des fichiers qu’elle récupèrera dans
     * le FilePool. Chaque fichier compressé est stocké dans une instance de la classe ZippedBuffer. Cette
     * instance est ajoutée au pool de fichiers compressés à écrire ZippedBufferPool. Elle peut aussi décompresser les fichers et les envoyer sur le disque.
     * @param pool est le pool de fichiers
     * @param zippedPool es le pool de fichers compréssés
     * @param folder dossier où il faut lire ou écrire
     * @param isCompressMode boléen qui indique si on est en mode compression ou décompression
     */
    Zipper(FilePool &pool, ZippedBufferPool &zippedPool, const QString &folder, const bool isCompressMode = true);
    /**
     * @brief run méthode du thread
     */
    virtual void run();

private:
    /**
     * @brief run méthode du thread qui permet de compresser
     */
    void runCompress();
    /**
     * @brief run méthode du thread qui permet de décompresser
     */
    void runUnCompress();
    /**
     * @brief compressFile méthode compressant le contenu du
     * fichier « fileName » et ajoute le fichier compresser au pool ZippedBufferPool
     * @param fileName nom du fichier
     */
    void compressFile(const QString &filename);
    /**
     * @brief unCompressFile est la méthode décompressant le fichier compressé et de l'écrire sur le disque.
     * @param zippedBuffer ficher compressé
     */
    void unCompressFile(const ZippedBuffer &zippedBuffer);
    /**
     * @param pool fichier de la class FilePool représentant un ensemble de
     * fichier à traiter.
     */
    FilePool &pool_;
    /**
     * @param zippedPool fichier de la class ZippedBufferPool permetant d'ajouter de nouveaux éléments dans le pool ou de récuperer les fichiers à traiter.
     */
    ZippedBufferPool &zippedPool_;
    /**
     * @param isCompressMode boléen qui indique si on est en mode compression ou décompression
     */
    bool isCompressMode_;
    /**
     * @brief folder_ path du dossier à analyser
     */
    QString folder_;
};

#endif // ZIPPER_H
