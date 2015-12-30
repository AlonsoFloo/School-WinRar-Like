#ifndef ZIPPEDBUFFER_H
#define ZIPPEDBUFFER_H
#include <QString>
#include <QByteArray>
#include <QDataStream>

/**
 * @brief La classe ZippedBuffer permet
 * de lire/écrire et stocker les données d'un flux
 * de données
 */
class ZippedBuffer
{
public:
    ZippedBuffer() {};
    /**
     * @brief ZippedBuffer permet de stocker les données d'un fichier compressé
     * @param path chemin vers le fichier à lire/ecrire
     * @param data tableau de byte contenant les données à lire/écrire
     */
    ZippedBuffer(const QString &path, const QByteArray &data);
    /**
     * @brief write permet d'écrire le chemin du fichier
     * ainsi que les données de celui-ci dans le flux de données
     * @param stream flux de données
     */
    void write(QDataStream &stream);
    /**
     * @brief read permet de lire le chemin du fichier
     * ainsi que les données de celui-ci du flux de données
     * @param stream flux de données
     */
    void read(QDataStream &stream);
    /**
     * @brief getPath permet de récupérer le chemin relatif du fichier
     *
     */
    QString getPath() const;
    /**
     * @brief getData permet de récupérer les données d'un fichier
     */
    QByteArray getData() const;

private:
    /**
     * @brief patch chemin du fichier
     */
    QString path_;
    /**
     * @brief data données du fichier
     */
    QByteArray data_;
};

#endif // ZIPPEDBUFFER_H
