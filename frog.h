#ifndef FROG_H
#define FROG_H

#include <QObject>
#include <QGraphicsItem>
#include <QMovie>
#include <QTimer>
#include "map.h"

class Frog : public QObject, public QGraphicsItem {
    Q_OBJECT

public:
    explicit Frog(Map *map);  // Constructor
    QRectF boundingRect() const override;  // Define the bounding rectangle of the frog
    void moveRandomly();  // Random movement logic

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;  // Paint method to render the frog

private:
    QTimer *moveTimer;  // Timer for movement
    QMovie *movie;      // Movie for GIF animation
    Map *map;           // Pointer to the map
    bool isFacingRight; // Flag to indicate whether the frog is facing right
};

#endif // FROG_H
