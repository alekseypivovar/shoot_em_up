#include "GameView.h"

#include <QDebug>
#include <QGraphicsPixmapItem>

namespace
{
int TileSize(64);
int TileGroundOffset(10);
int TileWaterOffset(0);
}

GameView::GameView(std::vector<std::string> &&map) :
    m_map(std::move(map))
{
    setScene(new QGraphicsScene());
    drawMap();
}

GameView::~GameView()
{

}

void GameView::drawMap()
{
    scene()->setSceneRect(0,0, (m_map.at(0).size() - 1) * TileSize, m_map.size() * TileSize);
    std::vector<Tile> tiles;
    tiles.reserve(m_map.size() * m_map.at(0).size());

    for (int row = 0; row < m_map.size(); ++row)
    {
        for (int column = 0; column < m_map[row].size(); ++column)
        {
            QString tile1;
            QString tile2;
            char randomTileNumber = std::rand() % 5 + 1;
            int tileOffset(TileWaterOffset);
            if (m_map[row][column] == 'g')
            {
                tile1 = ":/images/g" + QString::number(randomTileNumber) + "1.png";
                tile2 = ":/images/g" + QString::number(randomTileNumber) + "2.png";
                tileOffset = TileGroundOffset;
            }
            else
            {
                tile1 = ":/images/w" + QString::number(randomTileNumber) + "2.png";
                tile2 = ":/images/w" + QString::number(randomTileNumber) + "1.png";
            }

            QGraphicsPixmapItem* pItem1 = scene()->addPixmap(QPixmap(tile1));
            pItem1->setPos(QPoint(column * TileSize - tileOffset, row * TileSize - tileOffset));

            QGraphicsPixmapItem* pItem2 = scene()->addPixmap(QPixmap(tile2));
            pItem2->setPos(QPoint(column * TileSize - tileOffset, row * TileSize - tileOffset));
            pItem2->setVisible(false);

            tiles.emplace_back(Tile(pItem1, pItem2));
        }
    }
    m_worldAnimator = std::make_unique<WorldAnimator>(std::move(tiles));
}
