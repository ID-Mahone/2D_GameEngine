#include "mainwindow.h"
#include "player.h"
#include "map.h"
#include <QGraphicsView>
#include <QTimer>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), scene(new QGraphicsScene(this)), player(new Player()), map(new Map(20, 15, 32)) {
    setFixedSize(800, 600);

    view = new QGraphicsView(scene, this);
    setCentralWidget(view);

    scene->setSceneRect(0, 0, 800, 600);

    scene->addItem(map);
    scene->addItem(player);

    player->setPos(48, 48);
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    for (int x = 0; x < 20; ++x) {
        for (int y = 0; y < 15; ++y){
            if (x > 2 && x < 17 && y > 2 && y < 12)
            {
                if(x==8 && y==7)
                    map->setTile(x, y, Tile::Flower);
                else if(x == 8 && y == 7)
                    map->setTile(x, y, Tile::Flower);
                else
                    map->setTile(x, y, Tile::Grass);
            }
            else if (x == 2 || x==17 || y ==2 || y==12)
                map->setTile(x, y, Tile::Tree);
            else
                map->setTile(x, y, Tile::Dirt);
        }
    }
    for(int x=7; x<11; x++)
        map->setTile(x, 4, Tile::Road);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::gameUpdate);
    timer->start(16);
}

MainWindow::~MainWindow() {
    delete map;
    delete player;
    delete scene;
    delete view;
}

void MainWindow::gameUpdate() {
    scene->update();
}

