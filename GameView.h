#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QGraphicsView>
#include "WorldAnimator.h"

class GameView : public QGraphicsView
{
    Q_OBJECT
public:
    GameView(std::vector<std::string> &&map);
    ~GameView();

private:
    void drawMap();

    std::vector<std::string> m_map;
    std::unique_ptr<WorldAnimator> m_worldAnimator;
};

#endif // GAMEVIEW_H
