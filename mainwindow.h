#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include "map.h"
#include "player.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void gameUpdate();

private:
    void setupScene();
    QGraphicsView *view;
    QGraphicsScene *scene;
    Player *player;
    Map *map;
    QTimer *timer;
};

#endif // MAINWINDOW_H
