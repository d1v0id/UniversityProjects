#include "gamescene.h"
#include <QBrush>
#include <QPixmap>
#include <QTransform>
#include <QMessageBox>
#include <QtDebug>

GameScene::GameScene(QObject *parent) : QGraphicsScene(parent)
{
    spaceShip = addPixmap(QPixmap("./spaceShip.png"));
    QTransform transform = spaceShip->transform();
    transform.translate(270, 240);
    spaceShip->setTransform(transform);
    spaceShip->setData(0, "SpaceShip");

    timeCount = 0;
    makePipes();
    setBackgroundBrush(QBrush(QColor(255, 255, 255), QPixmap("bg.png")));

    pipesTimer = new QTimer(this);
    connect(pipesTimer, SIGNAL(timeout()), this, SLOT(move_pipes()));

    shipTimer = new QTimer(this);
    connect(shipTimer, SIGNAL(timeout()), this, SLOT(move_ship()));

    timeTimer = new QTimer(this);
    connect(timeTimer, SIGNAL(timeout()), this, SLOT(time_tick()));

    isActiveGame = false;
    isGameOver = false;

    startTextItem = new QGraphicsTextItem("Tap <Space> for Sofa jump!");
    startTextItem->setFont(QFont("Times", 28, QFont::Bold));
    startTextItem->setPos(140, 220);
    startTextItem->setDefaultTextColor(Qt::white);
    addItem(startTextItem);
}

void GameScene::keyPressEvent(QKeyEvent *keyEvent)
{
    if ((keyEvent->key() == Qt::Key_Space) && !isActiveGame && !isGameOver) {
        isActiveGame = true;
        pipesTimer->start(20);
        shipTimer->start(50);
        timeTimer->start(1000);
        removeItem(startTextItem);
    }

    if ((keyEvent->key() == Qt::Key_Space) && isActiveGame && !isGameOver) {
        int delta = getRandomDelta(40, 70);
        QPointF point;
        point.setX(0);
        point.setY(-delta);

        QTransform transform = spaceShip->transform();
        transform.translate(point.x(), point.y());
        spaceShip->setTransform(transform);

        checkShipPosition();
    }
}

QGraphicsItem *GameScene::itemCollidesWith(QGraphicsItem *item)
{
    QList<QGraphicsItem *> collisions = collidingItems(item);

    foreach (QGraphicsItem *it, collisions) {
        if (it == item) {
            continue;
        }

        return it;
    }

    return NULL;
}

void GameScene::move_ship()
{
    QPointF point;
    point.setX(0);
    point.setY(getRandomDelta(10, 60));

    QTransform transform = spaceShip->transform();
    transform.translate(point.x(), point.y());
    spaceShip->setTransform(transform);

    checkShipPosition();
}

void GameScene::move_pipes()
{
    int maxXValue = 0;

    foreach (QGraphicsItem *item, pipes) {
        int xValue = item->data(1).toInt();

        if (maxXValue < xValue) {
            maxXValue = xValue;
        }
    }

    foreach (QGraphicsItem *item, pipes) {
        QPointF point;
        point.setX(item->x() - 1);
        point.setY(item->y());

        QTransform transform = item->transform();
        transform.translate(point.x(), point.y());

        item->setTransform(transform);
        item->setData(1, item->data(1).toInt() - 1);

        int delta = item->data(1).toInt();

        if (delta < 0) {
            transform = item->transform();
            transform.translate(maxXValue + 150, point.y());
            item->setTransform(transform);
            item->setData(1, maxXValue + 150);
        }
    }
}

void GameScene::makePipes()
{
    float pipesCoords[10][4] = { {0, 420, 50, 210}, {0, 0, 50, 210},
                          {150, 420, 50, 210}, {150, 0, 50, 210},
                          {300, 420, 50, 210}, {300, 0, 50, 210},
                          {450, 420, 50, 210}, {450, 0, 50, 210},
                          {600, 420, 50, 210}, {600, 0, 50, 210} };

    QBrush brush1(QColor(255, 255, 255), QPixmap("./yellow_pipe1.png"));
    QBrush brush2(QColor(255, 255, 255), QPixmap("./yellow_pipe2.png"));
    QPen pen(Qt::NoPen);

    for (int i = 0; i < 10; i++) {
        QGraphicsItem *item = addRect(QRectF(pipesCoords[i][0],
                                      pipesCoords[i][1],
                                      pipesCoords[i][2],
                                      pipesCoords[i][3]), pen, (i % 2 == 0) ? brush1 : brush2);
        item->setData(0, "Pipe");
        item->setData(1, pipesCoords[i][0]);
        item->setData(2, i);

        pipes.append(item);
    }
}

void GameScene::checkShipPosition()
{
    QGraphicsItem *obstacle = itemCollidesWith(spaceShip);

    if (obstacle) {
        if (obstacle->data(0) == "Pipe") {
            isGameOver = true;

            pipesTimer->stop();
            shipTimer->stop();

            QGraphicsTextItem *textItem1 = new QGraphicsTextItem("Game Over!");
            textItem1->setFont(QFont("Times", 48, QFont::Bold));
            textItem1->setPos(200, 250);
            textItem1->setDefaultTextColor(Qt::white);
            addItem(textItem1);

            QGraphicsTextItem *textItem2 = new QGraphicsTextItem("Time: " + QString::number(timeCount));
            textItem2->setFont(QFont("Times", 28, QFont::Bold));
            textItem2->setPos(280, 350);
            textItem2->setDefaultTextColor(Qt::yellow);
            addItem(textItem2);

            qDebug() << timeCount;
        }
    }
}

int GameScene::getRandomDelta(int n, int m)
{
    unsigned int delta = qrand() % m;

    while (delta >= n) {
        delta = qrand() % m;
    }

    return delta;
}

void GameScene::time_tick()
{
    timeCount++;
}
