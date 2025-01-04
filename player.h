#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsObject>
#include <QObject>
#include <QPixmap>
#include <QTimer>

class Map;  // Forward declaration of the Map class
class QKeyEvent;

class Player : public QGraphicsObject {
    Q_OBJECT

public:
    explicit Player(Map *map);  // Constructor that accepts a map reference

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    void handleKeyPress(QKeyEvent *event);

    void move(int dx, int dy);
    void jump();
protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    bool isJumping = false;            // Flag for jumping
    bool isFacingRight = false;         // Direction the player is facing
    int currentFrame = 0;              // Current animation frame
    int currentRow = 0;                // Current row (action) in the sprite sheet

    QPixmap spriteSheet;               // Sprite sheet image (loaded from file)
    QTimer *animationTimer;            // Timer to update animation frames
    Map *map;

    float dx = 0;
    float dy = 0;
    float moveSpeed = 2.0f;        // Reference to the map for checking walkability


    void updateFrame();                // Advance the current animation frame
    //  void move(int dx, int dy);         // Move the player                     // Jump action
    void setAnimationRow(int row);     // Set the animation row for the current action
    bool canMoveToTile(float newX, float newY);  // Check if the tile is walkable
};

#endif // PLAYER_H
