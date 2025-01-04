#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>  // Add this include for QObject
#include <QTimer>
#include <QGraphicsItem>
#include <QPainter>
#include "map.h"

class Enemy : public QObject, public QGraphicsItem {  // Inherit from QObject and QGraphicsItem
    Q_OBJECT  // Add the Q_OBJECT macro to enable signal/slot mechanisms

public:
    Enemy(Map *map);  // Constructor declaration
    QRectF boundingRect() const override;
    void moveRandomly();
    bool canMoveToTile(float dx, float dy);
    void updateAnimation();
    void setAnimationState(int state);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    QTimer *moveTimer;
    QTimer *animationTimer;
    QPixmap spriteSheet;
    int currentFrame;
    int currentRow;
    Map *map;
    bool isFacingRight;
};

#endif // ENEMY_H
