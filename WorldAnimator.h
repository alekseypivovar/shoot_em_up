#ifndef WORLDANIMATOR_H
#define WORLDANIMATOR_H

#include <QObject>
#include <QThread>
#include "Tile.h"

class WorldAnimator : public QObject
{
    Q_OBJECT
public:
    explicit WorldAnimator(std::vector<Tile>&& tiles, QObject *parent = nullptr);
    ~WorldAnimator();

signals:
    void updateTile();

private:
    void timerEvent(QTimerEvent *event);

    std::vector<Tile> m_tiles;
    QThread m_worldThread;
    int m_timerId;
};

#endif // WORLDANIMATOR_H
