#include <QDebug>
#include "WorldAnimator.h"

namespace
{
int WorldAnimationInterval(400);
}

WorldAnimator::WorldAnimator(std::vector<Tile>&& tiles, QObject *parent)
    : QObject(parent),
      m_tiles(std::move(tiles)),
      m_timerId(0)
{
    moveToThread(&m_worldThread);

    for (auto& tile : m_tiles)
    {
        connect(this, &WorldAnimator::updateTile, &tile, &Tile::animateTile);
    }

    connect(&m_worldThread, &QThread::started, this, [this]()
    {
        m_timerId = startTimer(WorldAnimationInterval);
    });

    m_worldThread.start();
}

WorldAnimator::~WorldAnimator()
{
    if (m_timerId)
    {
        killTimer(m_timerId);
    }
    m_worldThread.quit();
    m_worldThread.wait();
}

void WorldAnimator::timerEvent(QTimerEvent *event)
{
    emit updateTile();
}
