#include "map.h"
#include "mainwindow.h"
#include <QDebug>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QPixmap>


Tile::Tile(TileType type) : type(type) {}

void Tile::draw(QPainter &painter, int x, int y, int tileSize) {
    switch (type) {
    case Grass:
        painter.fillRect(x, y, tileSize, tileSize, QColor(100, 180, 80)); // Green
        break;
    case Dirt:
        painter.fillRect(x, y, tileSize, tileSize, QColor(150, 100, 50)); // Brown
        break;
    case Water:
        painter.fillRect(x, y, tileSize, tileSize, QColor(50, 150, 200)); // Blue
        break;
    case Road:
        painter.fillRect(x, y, tileSize, tileSize, QColor(128, 128, 128)); // Gray
        break;
    case Tree:
        painter.fillRect(x, y, tileSize, tileSize, QColor(0, 100, 0)); // Dark Green
        break;
    case Flower:
        painter.fillRect(x, y, tileSize, tileSize, QColor(200, 50, 100)); //Pink/Red
        break;
    }
}



Map::Map(int width, int height, int tileSize)
    : width(width), height(height), tileSize(tileSize) {
    tiles.resize(width * height);
}


void Map::setTile(int x, int y, Tile::TileType type) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        tiles[y * width + x] = Tile(type);
    }else {
        qDebug() << "Invalid tile coordinates: x=" << x << ", y=" << y;

    }
}

void Map::loadFromCharMap( const char charMap[15][20]) {
    for ( int y = 0; y < height; ++y) {
        for ( int x = 0; x < width; ++x){
            switch (charMap[y][x]) {
            case 'G': setTile(x, y, Tile::Grass); break;
            case 'D': setTile(x, y, Tile::Dirt); break;
            case 'W': setTile(x, y, Tile::Water); break;
            case 'R': setTile(x, y, Tile::Road); break;
            case 'T': setTile(x, y, Tile::Tree); break;
            case 'F': setTile(x, y, Tile::Flower); break;
            default: setTile(x, y, Tile::Grass); break;
            }
        }
    }
}

bool Map::isWalkable(int x, int y) const {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        Tile::TileType tileType = tiles[y * width + x].getType();
        qDebug() << "Checking tile at position (" << x << ", " << y << ") - Type:" << tileType;

        // Only Grass and Dirt tiles should be walkable
        if (tileType == Tile::Grass || tileType == Tile::Dirt) {
            qDebug() << "Tile is walkable!";
            return true;
        } else {
            qDebug() << "Tile is blocked.";
            return false;
        }
    }
    qDebug() << "Position out of bounds: (" << x << ", " << y << ")";
    return false;  // Out of bounds tiles are non-walkable
}

QRectF Map::boundingRect() const {
    return QRectF(0, 0, width * tileSize, height * tileSize);
}

void Map::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    for (int y = 0; y < height; ++y){
        for (int x = 0; x < width; ++x) {
            tiles[y * width + x].draw(*painter, x * tileSize, y * tileSize, tileSize);
        }
    }
}

Tile::TileType Map::getTileType(int x, int y) const {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        return tiles[y * width + x].getType(); // Return the tile type at (x, y)
    }else {
        return Tile::Grass;
    }
}
