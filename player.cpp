#include "player.h"
#include "map.h"
#include <QPainter>
#include <QKeyEvent>
#include <QTimer>
#include <QPixmap>
#include <QTransform>
#include <QDebug>

Player::Player(Map *map)
    : currentFrame(0), currentRow(0), map(map), dx(0), dy(0) {

    spriteSheet.load(":/resources/player.png/player.png");  // Load the sprite sheet from resources

    if (spriteSheet.isNull()) {
        qDebug() << "Failed to load sprite sheet!";
    } else {
        qDebug() << "Sprite sheet loaded successfully.";
    }

    animationTimer = new QTimer(this);
    connect(animationTimer, &QTimer::timeout, this, &Player::updateFrame);
    animationTimer->start(1000);  // Update the frame every 100ms
}

QRectF Player::boundingRect() const {
    return QRectF(0, 0, 48, 48);  // Assuming 48x48 sprite size
}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    int frameX = currentFrame * 48;
    int frameY = currentRow * 48;

    QPixmap frame = spriteSheet.copy(frameX, frameY, 48, 48);

    frame = frame.scaled(48, 48, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    if (!isFacingRight) {
        QTransform transform;
        transform.scale(-1, 1);  // Flip horizontally
        frame = frame.transformed(transform);

        painter->drawPixmap(0, 0, frame);  // Offset by sprite width
    } else {
        painter->drawPixmap(0, 0, frame);
    }
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
    // Update the position of the player (implement logic for movement)
    float newX = x() + dx;
    float newY = y() + dy;

    if(canMoveToTile(newX, newY)) {
        setPos(newX, newY);
    }
}

void Player::jump() {
    if (!isJumping) {
        // Implement jump logic
        isJumping = true;
        setAnimationRow(6);  // Set to the jump/attack row
        QTimer::singleShot(500, this, [this]() {  // Simulate jump completion
            isJumping = false;
            setAnimationRow(0);  // Return to idle row
        });
    }
}

bool Player::canMoveToTile(float dx, float dy) {
    // Convert world coordinates to tile coordinates
    int tileX = dx / map->getTileSize();
    int tileY = dy / map->getTileSize();

    qDebug() << "Checking walkability at tile coordinates (" << tileX << ", "<< tileY <<")";

    bool walkable = map->isWalkable(tileX, tileY);
    qDebug() << "Tile at (" << tileX << ", " << tileY << ") is walkable:" << walkable;


    // Check if the tile is walkable using the map's isWalkable method
    return walkable;
}

void Player::updateFrame() {
    // Update the frame for the animation
    currentFrame = (currentFrame + 1) % 3;  // Loop through 3 frames for the current action
    update();  // Trigger a repaint of the player
}

void Player::setAnimationRow(int row) {
    currentRow = row;  // Set the row based on the current action
    currentFrame = 0;  // Reset the frame to the start of the animation
}

