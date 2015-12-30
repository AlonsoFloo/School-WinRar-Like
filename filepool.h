#ifndef FILEPOOL_H
#define FILEPOOL_H
#include <QStringList>
#include <QMutex>
/**
 * @brief La class FilePool représente un ensemble de
 * fichier à traiter.
 */
class FilePool
{
public:
    /**
     * @brief FilePool contruit un nouveau pool en l'initialisant
     * la liste des fichiers à partir du répertoire donné. Uniquement
     * les fichiers ayant le suffix passé sont ajoutés dans le pool.
     * Dès qu'il est construit, le pool peut être utilisé.
     * @param folder répertoire à partir duquel les fichiers sont recherchés
     * @param suffix des fichiers devant être ajoutés dans le pool
     */
    FilePool(const QString &folder);
    /**
     * @brief count retourne le nombre de fichiers restant dans le pool
     * @return
     * @note Cette méthode est thread-safe
     */
    int count();
    /**
     * @brief tryGetFile permet de récupérer le nom d'un fichier. Si il n'y a
     * plus de fichiers, cette méthode retourne une chaine vide. Le nom de fichier
     * retourné est supprimé du pool.
     * @return Un nom de fichier ou une chaine vide
     * @note Cette méthode est thread-safe
     */
    QString tryGetFile();
private:
    /**
     * @brief findFileInFolderAndSubfolders initialise le pool en parcourant récurcivement
     * le répertoire et les sous répertoires
     * @param folder le répertoire à parcourir
     */
    void findFileInFolderAndSubfolders(const QString &folder);
    /**
     * @brief files_ liste des fichiers contenu dans le pool
     */
    QStringList files_;
    /**
     * @brief mutex_ utilsé lors de l'accés à files_
     */
    QMutex mutex_;
    /**
     * @brief folder_ path du folder à analyser
     */
    QString folder_;
};

#endif // FILEPOOL_H
