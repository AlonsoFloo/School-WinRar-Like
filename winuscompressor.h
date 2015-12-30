#ifndef WINUSCOMPRESSOR_H
#define WINUSCOMPRESSOR_H
#include <QString>

/**
 * @brief WinUsCompressor est le controller central du logiciel
 * Il gêre les thread et l'ordre d'appel des méthode
 */
class WinUsCompressor
{
public:
    /**
     * @brief WinUsCompressor est le controller central du logiciel
     * Il gêre les thread et l'ordre d'appel des méthode
     * @param threadCount nombre du thread à utilisé
     */
    WinUsCompressor(const int threadCount);
    /**
     * @brief compress méthode compressant le contenu du
     * répertoire « folder » dans le fichier « ecfFileName »
     * @param folder path du dossier
     * @param ecfFileName path du fichier ECF
     */
    void compress(const QString &folder, const QString &ecfFileName);
    /**
     * @brief uncompress est la méthode décompressant le fichier
     * « ecfFileName » dans le répertoire « folder ».
     * @param ecfFileName path du fichier ECF
     * @param folder path du dossier
     */
    void uncompress(const QString &ecfFileName, const QString &folder);

private:
    /**
     * @brief threadCount_ nombre du thread à utilisé
     */
    int threadCount_;

};

#endif // WINUSCOMPRESSOR_H
