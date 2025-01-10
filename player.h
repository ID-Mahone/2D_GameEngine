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
    explicit Player(Map *map);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    void move(int dx, int dy);

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

    void focusInEvent(QFocusEvent *event) override;
    void focusOutEvent(QFocusEvent *event) override;

private:
    // Movement-related
    float dx = 0;
    float dy = 0;
    float moveSpeed = 1.5f;  // Default movement speed
    float dashSpeed = 50.0f;  // Speed when dashing
    bool isDashing = false;

    // State variables
    bool isFacingRight = true;
    int currentFrame = 0;
    int currentRow = 0;

    // Animation-related
    QPixmap spriteSheet;
    QTimer *animationTimer;  // Handles sprite animation
    QTimer *updateTimer;     // Handles smooth movement updates
    QTimer *dashTimer;       // Timer for dash duration

    // Input state
    bool keyW = false, keyA = false, keyS = false, keyD = false;

    // Associated map
    Map *map;

    // Functions
    void updatePosition();         // Updates the player's position based on input
    void updateFrame();            // Updates the sprite animation
    void setAnimationRow(int row); // Sets the current animation row
    bool canMoveToTile(float newX, float newY); // Checks if movement is valid
    void startDash();              // Initiates a dash
    void endDash();                // Ends dash when the timer completes
};

#endif // PLAYER_H
