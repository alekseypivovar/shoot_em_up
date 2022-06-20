#include <QDebug>
#include "Tile.h"

Tile::Tile(QGraphicsPixmapItem *pixmap1, QGraphicsPixmapItem *pixmap2) :
    QObject(nullptr),
    m_tiles(pixmap1, pixmap2),
    m_isFirstTileShown(true)
{

}

Tile::Tile(Tile &&other) :
    QObject(nullptr),
    m_tiles(other.tiles()),
    m_isFirstTileShown(other.isFirstTileShown())
{

}

void Tile::animateTile()
{
    m_tiles.first->setVisible(!m_isFirstTileShown);
    m_tiles.second->setVisible(m_isFirstTileShown);
    //qDebug() << m_tiles.first << !m_isFirstTileShown << m_tiles.second << m_isFirstTileShown;
    m_isFirstTileShown = !m_isFirstTileShown;
}

const std::pair<QGraphicsPixmapItem *, QGraphicsPixmapItem *> &Tile::tiles() const
{
    return m_tiles;
}

bool Tile::isFirstTileShown() const
{
    return m_isFirstTileShown;
}
