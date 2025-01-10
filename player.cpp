#include "player.h"
#include "map.h"
#include <QPainter>
#include <QKeyEvent>
#include <QTimer>
#include <QPixmap>
#include <QTransform>
#include <QDebug>

Player::Player(Map *map)
    : currentFrame(0), currentRow(0), map(map), dx(0), dy(0),
    isFacingRight(true), isDashing(false), dashSpeed(4.0f), moveSpeed(1.5f) {

    spriteSheet.load(":/resources/player2.png/player2.png");

    if (spriteSheet.isNull()) {
        qDebug() << "Failed to load sprite sheet!";
    } else {
        qDebug() << "Sprite sheet loaded successfully.";
    }

    setFlag(QGraphicsItem::ItemIsFocusable); // Allow player to receive focus
    setFocus(); // Set initial focus on the player

    animationTimer = new QTimer(this);
    connect(animationTimer, &QTimer::timeout, this, &Player::updateFrame);
    animationTimer->start(16); // ~60 FPS

    dashTimer = new QTimer(this);
    connect(dashTimer, &QTimer::timeout, this, &Player::endDash);

    updateTimer = new QTimer(this);
    connect(updateTimer, &QTimer::timeout, this, &Player::updatePosition);
    updateTimer->start(16); // ~60 FPS
}

QRectF Player::boundingRect() const {
    return QRectF(0, 0, 48, 48);
}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    int frameX = currentFrame * 48;
    int frameY = currentRow * 48;

    QPixmap frame = spriteSheet.copy(frameX, frameY, 48, 48);
    frame = frame.scaled(48, 48, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    if (!isFacingRight) {
        QTransform transform;
        transform.scale(-1, 1);
        frame = frame.transformed(transform);
        painter->drawPixmap(0, 0, frame);
    } else {
        painter->drawPixmap(0, 0, frame);
    }
}

void Player::keyPressEvent(QKeyEvent *event) {
    qDebug() << "Key pressed:" << event->key();

    if (event->key() == Qt::Key_Shift && !isDashing) {
        startDash();
    }

    if (event->key() == Qt::Key_W) keyW = true;
    if (event->key() == Qt::Key_S) keyS = true;
    if (event->key() == Qt::Key_A) keyA = true;
    if (event->key() == Qt::Key_D) keyD = true;
}

void Player::keyReleaseEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_W) keyW = false;
    if (event->key() == Qt::Key_S) keyS = false;
    if (event->key() == Qt::Key_A) keyA = false;
    if (event->key() == Qt::Key_D) keyD = false;

    qDebug() << "Key released. W:" << keyW << " A:" << keyA << " S:" << keyS << " D:" << keyD;

    // Stop movement if no keys are pressed
    if (!keyW && !keyS && !keyA && !keyD) {
        dx = 0;
        dy = 0;
    }
}

void Player::updatePosition() {
    dx = 0;
    dy = 0;

    if (keyW) dy -= moveSpeed;
    if (keyS) dy += moveSpeed;
    if (keyA) dx -= moveSpeed;
    if (keyD) dx += moveSpeed;

    // Update facing direction
    if (dx > 0) isFacingRight = false;
    if (dx < 0) isFacingRight = true;

    if (dx == 0 && dy == 0) {
        return; // No movement; skip processing
    }

    // Normalize diagonal movement
    if (dx != 0 && dy != 0) {
        dx /= 1.414; // Normalize
        dy /= 1.414;
    }

    float speedMultiplier = isDashing ? dashSpeed : moveSpeed;
    float actualDx = dx * speedMultiplier;
    float actualDy = dy * speedMultiplier;

    float newX = x() + actualDx;
    float newY = y() + actualDy;

    if (canMoveToTile(newX, newY)) {
        setPos(newX, newY);
    }
    update();
}

bool Player::canMoveToTile(float dx, float dy) {
    int tileX = dx / map->getTileSize();
    int tileY = dy / map->getTileSize();

    return map->isWalkable(tileX, tileY);
}

void Player::move(int dx, int dy) {
    float newX = x() + dx;
    float newY = y() + dy;

    if (canMoveToTile(newX, newY)) {
        setPos(newX, newY);
    }
}

void Player::updateFrame() {
    currentFrame = (currentFrame + 1) % 3;
    update();
}

void Player::setAnimationRow(int row) {
    currentRow = row;
    currentFrame = 0;
}

void Player::startDash() {
    isDashing = true;
    dashTimer->start(400);
}

void Player::endDash() {
    isDashing = false;
    dashTimer->stop();
}

void Player::focusInEvent(QFocusEvent *event) {
    qDebug() << "Player gained focus";
    QGraphicsItem::focusInEvent(event);
}

void Player::focusOutEvent(QFocusEvent *event) {
    qDebug() << "Player lost focus. Reapplying focus...";
    setFocus(); // Ensure the Player retains focus
    QGraphicsItem::focusOutEvent(event);
}
