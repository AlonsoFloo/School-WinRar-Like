#ifndef ZIPPEDBUFFERPOOL_H
#define ZIPPEDBUFFERPOOL_H
#include <QMutex>
#include <QPair>
#include <QWaitCondition>
#include <QVector>
#include "zippedbuffer.h"
/**
 * @brief La classe ZippedBufferPool permet d'ajouter de nouveaux éléments dans le pool.Elle
 * possède 3 méthodes « thread-safe ».
 */
class ZippedBufferPool
{
public:

    /**
     * @brief ZippedBufferPool est le pool de fichiers compréssés.
     */

    ZippedBufferPool();
    /**
     * @brief put est la méthode permettant d’ajouter un nouvel élément dans le pool.
     * @param zb nouvel élément du pool
     * @note Cette méthode est thread-safe
     */
    void put(ZippedBuffer &zb);
    /**
     * @brief tryGet est le méthode permettant de récupérer un élément du pool. Cette méthode renvoie un objet de type QPair . Le booléen est vrai si le pool ZippedBuffer est
     * valide. Cette méthode est bloquante si le pool ne contient pas de ZippedBuffer. Elle est
     * débloquée lorsqu’un ZippedBuffer est disponible ou quand la méthode done() est appelée.
     * @note Cette méthode est thread-safe
     */
    QPair<bool,ZippedBuffer> tryGet();
    /**
     * @brief : Cette méthode signale au pool que plus aucun objet ne sera ajouté. Elle sera appelée
     * quand tous les Zippers auront terminé leur exécution.
     */
    void done();

private:
    /**
     * @brief : isAlimented_ booléen qui permet de savoir si le pool est toujours alimenté.
     */
    bool isAlimented_;
    /**
     * @brief : waitCondition_ condition d'attente pour les threads.
     */
    QWaitCondition waitCondition_;
    /**
     * @brief mutex_ utilsé lors de l'accés à zippedBufferList_
     */
    QMutex mutex_;
    /**
     * @brief zippedBufferList_ tableau de buffer
     */
    QVector<ZippedBuffer> zippedBufferList_;
};

#endif // ZIPPEDBUFFERPOOL_H
