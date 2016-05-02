#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QKeyEvent>

class GameScene : public QGraphicsScene
{
    Q_OBJECT

public:
    GameScene(QObject *parent = 0);

private slots:
    void move_pipes();
    void move_ship();
    void time_tick();

protected:
    virtual void keyPressEvent(QKeyEvent *);

private:
    bool isActiveGame;
    bool isGameOver;
    int timeCount;
    QTimer *pipesTimer;
    QTimer *shipTimer;
    QTimer *timeTimer;
    QGraphicsTextItem *startTextItem;
    QGraphicsPixmapItem *spaceShip;
    QList<QGraphicsItem *> pipes;

    void makePipes();
    void checkShipPosition();
    QGraphicsItem *itemCollidesWith(QGraphicsItem *);
    int getRandomDelta(int, int);
};

#endif // GAMESCENE_H
