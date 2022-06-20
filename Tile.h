#ifndef TILE_H
#define TILE_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Tile : public QObject
{
    Q_OBJECT
public:
    Tile(QGraphicsPixmapItem *pixmap1, QGraphicsPixmapItem *pixmap2);
    Tile(Tile&& other);

    void animateTile();

    const std::pair<QGraphicsPixmapItem *, QGraphicsPixmapItem *> &tiles() const;
    bool isFirstTileShown() const;

private:
    std::pair<QGraphicsPixmapItem *, QGraphicsPixmapItem *> m_tiles;
    bool m_isFirstTileShown;
};

#endif // TILE_H
