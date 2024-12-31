#include "player.h"
#include <QPainter>
#include <QPropertyAnimation>
#include <QKeyEvent>
#include <QSequentialAnimationGroup>

Player::Player() {
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

void Player::handleKeyPress(QKeyEvent *event){
    keyPressEvent(event);
}

void Player::keyPressEvent(QKeyEvent *event) {
    int dx = 0, dy = 0;
    switch (event->key()) {
    case Qt::Key_W:
        dy = -10;  // Move up
        break;
    case Qt::Key_S:
        dy = 10;  // Move down
        break;
    case Qt::Key_A:
        dx = -10;  // Move left
        break;
    case Qt::Key_D:
        dx = 10;  // Move right
        break;
    case Qt::Key_Space:
        jump();  //  jump
        return;
    }


    move(dx, dy);
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
