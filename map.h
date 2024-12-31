#ifndef MAP_H
#define MAP_H

#include <QGraphicsItem>
#include <QPainter>
#include <vector>

class Tile {
public:
    enum TileType {
        Grass,
        Dirt,
        Water,
        Road,
        Tree, // New tile type
        Flower // New tile type
    };

    Tile(TileType type = Grass);
    void draw(QPainter &painter, int x, int y, int tileSize); // Add tileSize parameter

private:
    TileType type;
};

class Map : public QGraphicsItem {
public:
    Map(int width, int height, int tileSize); // Add tileSize to constructor
    void setTile(int x, int y, Tile::TileType type);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    int getTileSize() const { return tileSize; }

private:
    int width, height;
    int tileSize; // Store tile size
    std::vector<Tile> tiles;
};

#endif // MAP_H
