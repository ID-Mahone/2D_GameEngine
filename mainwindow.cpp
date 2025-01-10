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

    // Set up the tile size (64x64 as per your requirement)
    const int tileSize = 64;

    // Calculate the window size based on map dimensions and tile size
    int windowWidth = map->getWidth() * tileSize;
    int windowHeight = map->getHeight() * tileSize;

    // Set the minimum size based on the map
    setMinimumSize(windowWidth, windowHeight);

    // Create the view and set it as the central widget
    view = new QGraphicsView(scene, this);
    setCentralWidget(view);

    // Set scene to match the full map size (20x15 grid with 64x64 tiles)
    scene->setSceneRect(0, 0, windowWidth, windowHeight);

    // Add the map, player, and frog to the scene
    scene->addItem(map);
    scene->addItem(player);
    scene->addItem(frog);

    // Set the initial position of the player
    player->setPos(32, 32);  // Adjust if necessary
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    // Create and position the enemy
    enemy->setPos(31, 31); // Set initial position for the enemy
    enemy->setZValue(2);

    // Create and position the frog
    frog->setPos(31, 31); // Set initial position for the frog
    frog->setZValue(2);

    // Add the enemy to the scene
    scene->addItem(enemy);

    // Map layout (same as before)
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

    // Load the map from the character layout
    map->loadFromCharMap(charMap);

    // Set up the timer for game updates
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
    scene->update();  // Update the scene (call this to refresh the game view)
}
