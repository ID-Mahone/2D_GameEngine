#include "mainwindow.h"
#include "player.h"
#include "enemy.h"
#include "frog.h"
#include "map.h"
#include <QGraphicsView>
#include <QTimer>
#include <QKeyEvent>
#include <cstdlib> // For rand()

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    scene(new QGraphicsScene(this)),
    map(new Map(20, 15, 31)),  // Map initialized before player
    player(new Player(map)),   // Player initialized after map
    enemy(new Enemy(map)),     // Enemy initialized after player
    frog(new Frog(map)),       // Frog initialized after player
    timer(new QTimer(this)) {

    const int tileSize = 32;

    // Calculate the minimum window size based on map dimensions
    int minWidth = map->getWidth() * tileSize;
    int minHeight = map->getHeight() * tileSize;

    setMinimumSize(minWidth, minHeight);  // Fixed spelling mistake

    view = new QGraphicsView(scene, this);
    setCentralWidget(view);

    scene->setSceneRect(0, 0, 800, 600);

    scene->addItem(map);
    scene->addItem(player);

    // Randomly position the frog on the map (excluding certain areas)
    int randX = rand() % map->getWidth();
    int randY = rand() % map->getHeight();
    frog->setPos(randX * tileSize, randY * tileSize);
    frog->setZValue(3);
    scene->addItem(frog);  // Add frog to the scene

    player->setPos(32, 32);
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    enemy->setPos(31, 31); // Set initial position for the enemy
    enemy->setZValue(2);
    scene->addItem(enemy); // Add enemy to the scene

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
        {'T', 'T', 'T', 'T', 'T', 'T', 'T', 'T', 'T', 'T', 'T', 'T', 'T', 'T', 'T', 'T', 'T', 'T', 'T', 'T'}
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
