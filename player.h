#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsObject>
#include <QObject>

class Player : public QGraphicsObject {
    Q_OBJECT

public:
    Player();

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    void handleKeyPress(QKeyEvent *event);

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    void move(int dx, int dy);
    void jump();
    bool isJumping = false;
};

#endif // PLAYER_H
