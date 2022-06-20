#include "GameView.h"

#include <QApplication>
#include <vector>
#include <fstream>

namespace
{
const int HorizontalTileCount(100);
const int VerticalTileCount(100);

const int NewGroundTileProbability(2);
const int IsleGroundTileProbability(60);
}

// forward declaration
std::vector<std::string> drawRandomMap(const int x, const int y);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameView w(drawRandomMap(HorizontalTileCount, VerticalTileCount));
    w.showMaximized();
    return a.exec();
}

std::vector<std::string> drawRandomMap(const int x, const int y)
{
    std::srand(std::time(nullptr));
    std::vector<std::string> map(y, std::string(x + 1, 'w'));

    // put the ground and water tiles
    for (int row = 0; row < y; ++row)
    {
        for (int column = 0; column < x; ++column)
        {
            int groundProbability = NewGroundTileProbability;
            if ((row && column)
                    && (map[row - 1][column] == 'g'
                        || map[row][column - 1] == 'g'))
            {
                groundProbability = IsleGroundTileProbability;
            }

            char tile = std::rand() % 100 < groundProbability ? 'g' : 'w';
            map[row][column] = tile;
        }
        map[row][x] = '\n';
    }

    // write the result to a file
    std::ofstream mapFile("map.txt");
    for (int row = 0; row < map.size(); ++row)
    {
        for (int column = 0; column < map[row].size(); ++column)
        {
            mapFile << map[row][column];
        }
    }
    mapFile.close();

    return map;
}
