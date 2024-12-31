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
    // Create main window
    explicit MainWindow(QWidget *parent = nullptr);

    // Destructor to clean up resources
    ~MainWindow();

private slots:
    void gameUpdate();

private:
    void setupScene();

    QGraphicsView *view;
    QGraphicsScene *scene;
    Map *map;          // Move this declaration before player
    Player *player;    // Now player is declared after map
    QTimer *timer;
};

#endif // MAINWINDOW_H
