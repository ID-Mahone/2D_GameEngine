#include <QTimer>
#include <QPixmap>
#include <QTransform>
#include <QRandomGenerator>
#include <QDebug>
#include <QObject>
#include "enemy.h"
#include "map.h"

Enemy::Enemy(Map *map)
    : currentFrame(0), currentRow(0), map(map), isFacingRight(true) {

    spriteSheet.load(":/resources/enemy.png/slime.png");
    if (spriteSheet.isNull()) {
        qDebug() << "Failed to load enemy sprite!";
    } else {
        qDebug() << "Enemy sprite sheet loaded successfully.";
    }

    moveTimer = new QTimer(this);
    connect(moveTimer, &QTimer::timeout, this, &Enemy::moveRandomly);
    moveTimer->start(500);  // Move every 500 ms for smoother movement

    animationTimer = new QTimer(this);
    connect(animationTimer, &QTimer::timeout, this, &Enemy::updateAnimation);
    animationTimer->start(200);  // Update animation every 1 s
}
void Enemy::moveRandomly() {
    int dx = 0;
    int dy = 0;
    int stepSize = map->getTileSize(); // Assuming 32x32 grid

    int direction = QRandomGenerator::global()->bounded(4);  // Randomly choose 0, 1, 2, or 3

    switch (direction) {
    case 0:  // Move up
        dy = -stepSize;
        break;
    case 1:  // Move down
        dy = stepSize;
        break;
    case 2:  // Move left
        dx = -stepSize;
        break;
    case 3:  // Move right
        dx = stepSize;
        break;
    }

    // Calculate the potential new position (in terms of pixels)
    int newX = x() + dx;
    int newY = y() + dy;

    // Log position attempts for debugging
    qDebug() << "Attempting to move to: (" << newX << ", " << newY << ")";

    // Convert the new pixel positions into tile coordinates (grid-based)
    int tileX = newX / stepSize;
    int tileY = newY / stepSize;

    // Ensure the new position is walkable
    if (map->isWalkable(tileX, tileY)) {
        setPos(newX, newY);  // Update position
        setAnimationState(1); // Update the animation state to moving
    } else {
        qDebug() << "Blocked at: (" << newX << ", " << newY << ")";
    }
}




QRectF Enemy::boundingRect() const {
    return QRectF(0, 0, 32, 32);  // Assuming slime uses 32x32 grid size
}

void Enemy::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    int frameX = currentFrame * 32;  // Slime uses 32x32 sprite grid
    int frameY = currentRow * 32;

    QPixmap frame = spriteSheet.copy(frameX, frameY, 32, 32);  // Use 32x32 size for slime sprite
    frame = frame.scaled(48, 48, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);  // Scale to match player size

    if (!isFacingRight) {
        QTransform transform;
        transform.scale(-1, 1);  // Flip horizontally
        frame = frame.transformed(transform);
        painter->drawPixmap(0, 0, frame);  // Offset by sprite width
    } else {
        painter->drawPixmap(0, 0, frame);
    }

    qDebug() << "Drawing enemy at position" << x() << y();  // Debug log to check rendering
}

void Enemy::updateAnimation() {
    // Update animation frame for the current row (idle, moving, attacking, etc.)
    if (currentRow == 3 || currentRow == 6) {  // Moving or attacking
        currentFrame = (currentFrame + 1) % 3;  // Loop through 3 frames for movement or attack
    } else if (currentRow == 0) {  // Idle state
        currentFrame = (currentFrame + 1) % 3;  // Loop through 3 frames for idle
    }
    update();  // Trigger repaint of the enemy
}

bool Enemy::canMoveToTile(float dx, float dy) {
    int tileX = static_cast<int>(dx / map->getTileSize());
    int tileY = static_cast<int>(dy / map->getTileSize());

    bool walkable = map->isWalkable(tileX, tileY);
    return walkable;
}

void Enemy::setAnimationState(int state) {
    switch (state) {
    case 0:  // Idle
        currentRow = 0;  // Set to idle row
        break;
    case 1:  // Moving
        currentRow = 3;  // Set to moving row
        break;
    case 2:  // Attacking
        currentRow = 6;  // Set to attacking row
        break;
    case 3:  // Damaged
        currentRow = 9;  // Set to damaged row
        break;
    case 4:  // Death
        currentRow = 12;  // Set to death row
        break;
    default:
        currentRow = 0;  // Default to idle if an unknown state is passed
        break;
    }
    currentFrame = 0;  // Reset the frame to the start of the animation row
    update();  // Request a repaint of the enemy
}
