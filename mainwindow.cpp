#include "mainwindow.h"
#include "player.h"
#include "enemy.h"
#include "frog.h"
#include "map.h"
#include <QGraphicsView>
#include <QTimer>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    scene(new QGraphicsScene(this)),
    map(new Map(20, 15, 31)),  // Map initialized before player
    player(new Player(map)),   // Player initialized after map
    enemy(new Enemy(map)),
    frog(new Frog(map)),    // Enemy initialized after player
    timer(new QTimer(this)) {
    //setFixedSize(800, 600);

    //view = new QGraphicsView(scene, this);
    //setCentralWidget(view);

    const int tileSize = 32;

    // Calculate the minimum window size based on map dimensions
    int minWidth = map->getWidth() * tileSize;
    int minHeight = map->getHeight() * tileSize;

    setMinimumSize(minWidth, minHeight);


    //showFullScreen();

    view = new QGraphicsView(scene, this);
    setCentralWidget(view);

    scene->setSceneRect(0, 0, 800, 600);

    scene->addItem(map);
    scene->addItem(player);
    scene->addItem(frog);

    player->setPos(32, 32);
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    Enemy *enemy = new Enemy(map);
    enemy->setPos(31, 31); // Set initial position for the enemy
    enemy->setZValue(2);

    Frog *frog = new Frog(map);
    frog->setPos(30, 30); // Set initial position for the enemy
    frog->setZValue(3);

    scene->addItem(enemy);



    const char charMap[15][20] = {
                                  {'T', 'T', 'T', 'T', 'T', 'T', 'T', 'T', 'T', 'T', 'T', 'T', 'T', 'T', 'T', 'T', 'T', 'T', 'T', 'T'},
                                  {'T', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'T'},
                                  {'T', 'G', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'G', 'T'},
                                  {'T', 'G', 'D', 'G', 'G', 'G', 'G', 'G', 'R', 'R', 'R', 'R', 'G', 'G', 'G', 'G', 'G', 'D', 'G', 'T'},
                                  {'T', 'G', 'D', 'G', 'R', 'R', 'R', 'R', 'G', 'G', 'G', 'R', 'R', 'R', 'R', 'G', 'G', 'D', 'G', 'T'},
                                  {'T', 'G', 'D', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'D', 'G', 'T'},
                                  {'T', 'G', 'D', 'G', 'G', 'G', 'G', 'G', 'F', 'G', 'G', 'F', 'G', 'G', 'F', 'G', 'G', 'D', 'D', 'D'},
                                  {'T', 'G', 'D', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'D', 'G', 'T'},
                                  {'T', 'G', 'D', 'G', 'G', 'G', 'G', 'G', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'G', 'G', 'D', 'G', 'T'},
                                  {'T', 'G', 'D', 'G', 'G', 'G', 'G', 'G', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'G', 'G', 'D', 'G', 'T'},
                                  {'T', 'G', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'G', 'T'},
                                  {'T', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'T'},
                                  {'T', 'T', 'T', 'T', 'T', 'T', 'T', 'T', 'T', 'T', 'T', 'T', 'T', 'T', 'T', 'T', 'T', 'T', 'T', 'T'},
                                  };

    // Load the map
    map->loadFromCharMap(charMap);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::gameUpdate);
    timer->start(16); // Update every 16ms (60FPS)

}

MainWindow::~MainWindow() {
    delete map;
    delete player;
    delete enemy;
    delete frog;
    delete scene;
    delete view;
}

void MainWindow::gameUpdate() {
    scene->update();
}
