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
        Tree,
        Flower
    };

    // Constructor to initialize the tile type
    Tile(TileType type = Grass);

    // Method to draw the tile at given coordinates with a specific tile size
    void draw(QPainter &painter, int x, int y, int tileSize);
    TileType getType() const { return type; } // Getter method for type

private:
    TileType type; // type of the tile (e.g. Grass, Dirt, etc.)
};


//Represent the
class Map : public QGraphicsItem {
public:
    // Constructor for map size
    Map(int width, int height, int tileSize);

    // Method to set the tile at a specific coordinate with a given type
    void loadFromCharMap(const char charMap[15][20]);


    // Method to load the map from a char-based map layout
    void setTile(int x, int y, Tile::TileType type);

    bool isWalkable(int x, int y) const;

    QRectF boundingRect() const override;


    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    Tile::TileType getTileType(int x, int y) const;

    int getTileSize() const { return tileSize; }

private:
    int width, height; // Width and height of the map in tiles
    int tileSize; // Size of each tile in pixels
    std::vector<Tile> tiles; // Vector to store all tiles
};

#endif // MAP_H
