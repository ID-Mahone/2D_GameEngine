#include <QMovie>
#include <QPainter>
#include <QDebug>
#include <QRandomGenerator>
#include "frog.h"
#include "map.h"

Frog::Frog(Map *map)
    : map(map), isFacingRight(true) {

    movie = new QMovie(":/new/prefix1/frog.gif");
    if (!movie->isValid()) {
        qDebug() << "Failed to load frog GIF!";
    } else {
        qDebug() << "Frog GIF loaded successfully.";
        movie->start();
    }

    // Connect the frameChanged signal to trigger the repaint when the frame changes
    connect(movie, &QMovie::frameChanged, this, [this]() {
        update();  // Trigger repaint when the frame changes
    });

    moveTimer = new QTimer(this);
    connect(moveTimer, &QTimer::timeout, this, &Frog::moveRandomly);
    moveTimer->start(500);  // Move every 500 ms
}

void Frog::moveRandomly() {
    int dx = 0;
    int dy = 0;
    int stepSize = map->getTileSize();

    int direction = QRandomGenerator::global()->bounded(4);

    switch (direction) {
    case 0:  // Move up
        dy = -stepSize;
        break;
    case 1:  // Move down
        dy = stepSize;
        break;
    case 2:  // Move left
        dx = -stepSize;
        isFacingRight = false;
        break;
    case 3:  // Move right
        dx = stepSize;
        isFacingRight = true;
        break;
    }

    int newX = x() + dx;
    int newY = y() + dy;

    int tileX = newX / stepSize;
    int tileY = newY / stepSize;

    if (map->isWalkable(tileX, tileY)) {
        setPos(newX, newY);
    } else {
        qDebug() << "Blocked at: (" << tileX << ", " << tileY << ")";
    }
}

void Frog::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    // Get the current frame from the movie
    QPixmap frame = movie->currentPixmap();
    if (frame.isNull()) return;  // If the frame is not valid, return early

    // Flip the frame if the frog is facing left
    if (!isFacingRight) {
        QTransform transform;
        transform.scale(-1, 1);  // Flip horizontally
        frame = frame.transformed(transform);
    }

    // Draw the frame at the correct size
    painter->drawPixmap(0, 0, frame.scaled(48, 48, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

QRectF Frog::boundingRect() const {
    return QRectF(0, 0, 48, 48);  // Bounding box for the frog
}
