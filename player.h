#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsObject>
#include <QObject>

class Map;  // Forward declaration of the Map class
class QKeyEvent;

class Player : public QGraphicsObject {
    Q_OBJECT

public:
    explicit Player(Map *map);  // Constructor that accepts a map reference

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    void handleKeyPress(QKeyEvent *event);

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    void move(int dx, int dy);
    void jump();
    bool canMoveToTile(int x, int y);  // Check if the tile is walkable
    bool isJumping = false;

    Map *map;  // Reference to the map for checking walkability
};

#endif // PLAYER_H
