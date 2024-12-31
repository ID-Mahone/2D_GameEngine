#include "player.h"
#include "map.h"
#include <QPainter>
#include <QPropertyAnimation>
#include <QKeyEvent>
#include <QSequentialAnimationGroup>

Player::Player(Map *map) : map(map) {
    // Player initialization
}

QRectF Player::boundingRect() const {
    // Define the bounds of the player object
    return QRectF(0, 0, 30, 30);
}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    // Draw the player object
    painter->setBrush(Qt::red);
    painter->drawRect(boundingRect());
}

void Player::handleKeyPress(QKeyEvent *event) {
    keyPressEvent(event);
}

void Player::keyPressEvent(QKeyEvent *event) {
    int dx = 0, dy = 0;
    int stepSize = map->getTileSize(); // Ensure movement matches tile size

    switch (event->key()) {
    case Qt::Key_W:
        dy = -stepSize;  // Move up by one tile
        break;
    case Qt::Key_S:
        dy = stepSize;   // Move down by one tile
        break;
    case Qt::Key_A:
        dx = -stepSize;  // Move left by one tile
        break;
    case Qt::Key_D:
        dx = stepSize;   // Move right by one tile
        break;
    case Qt::Key_Space:
        jump();          // Jump
        return;
    }

    // Only move if the target tile is walkable
    if (canMoveToTile(x() + dx, y() + dy)) {
        move(dx, dy);
    } else {
        qDebug() << "Blocked: Cannot move to (" << x() + dx << ", " << y() + dy << ")";
    }
}

void Player::move(int dx, int dy) {
    QPropertyAnimation *animation = new QPropertyAnimation(this, "pos");
    animation->setDuration(100);
    animation->setStartValue(pos());
    animation->setEndValue(pos() + QPointF(dx, dy));
    animation->setEasingCurve(QEasingCurve::InOutQuad);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void Player::jump() {
    if (isJumping) return;

    isJumping = true;

    QPropertyAnimation *jumpUp = new QPropertyAnimation(this, "pos");
    jumpUp->setDuration(200);
    jumpUp->setStartValue(pos());
    jumpUp->setEndValue(pos() + QPointF(0, -50));
    jumpUp->setEasingCurve(QEasingCurve::OutQuad);

    QPropertyAnimation *jumpDown = new QPropertyAnimation(this, "pos");
    jumpDown->setDuration(200);
    jumpDown->setStartValue(pos() + QPointF(0, -50));
    jumpDown->setEndValue(pos());
    jumpDown->setEasingCurve(QEasingCurve::InQuad);

    QSequentialAnimationGroup *jump = new QSequentialAnimationGroup(this);
    jump->addAnimation(jumpUp);
    jump->addAnimation(jumpDown);

    connect(jump, &QSequentialAnimationGroup::finished, [this]() {
        isJumping = false;
    });
    jump->start(QAbstractAnimation::DeleteWhenStopped);
}

bool Player::canMoveToTile(int x, int y) {
    // Convert pixel coordinates to tile coordinates
    int tileX = x / map->getTileSize();
    int tileY = y / map->getTileSize();

    // Check walkability of the tile
    return map->isWalkable(tileX, tileY);
}

