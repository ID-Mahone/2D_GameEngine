#include "map.h"
#include <QDebug>

Tile::Tile(TileType type) : type(type) {}

void Tile::draw(QPainter &painter, int x, int y, int tileSize) {
    switch (type) {
    case Tile::Grass:
        painter.fillRect(x, y, tileSize, tileSize, QColor(100, 180, 80)); // Green
        break;
    case Tile::Dirt:
        painter.fillRect(x, y, tileSize, tileSize, QColor(150, 100, 50)); // Brown
        break;
    case Tile::Water:
        painter.fillRect(x, y, tileSize, tileSize, QColor(50, 150, 200)); // Blue
        break;
    case Tile::Road:
        painter.fillRect(x, y, tileSize, tileSize, QColor(128, 128, 128)); // Gray
        break;
    case Tile::Tree:
        painter.fillRect(x, y, tileSize, tileSize, QColor(0, 100, 0)); // Dark Green
        break;
    case Tile::Flower:
        painter.fillRect(x, y, tileSize, tileSize, QColor(200, 50, 100)); // Pink/Red
        break;
    }
}

Map::Map(int width, int height, int tileSize) : width(width), height(height), tileSize(tileSize) {
    tiles.resize(width * height);
}

void Map::setTile(int x, int y, Tile::TileType type) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        tiles[y * width + x] = Tile(type);
    } else {
        qDebug() << "Invalid tile coordinates: x=" << x << ", y=" << y;
    }
}

QRectF Map::boundingRect() const {
    return QRectF(0, 0, width * tileSize, height * tileSize);
}

void Map::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            tiles[y * width + x].draw(*painter, x * tileSize, y * tileSize, tileSize);
        }
    }
}
