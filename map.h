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
    virtual void draw(QPainter &painter, int x, int y, int tileSize);
    TileType getType() const { return type; } // Getter method for type

private:
    TileType type; // type of the tile (e.g. Grass, Dirt, etc.)
};

// Represent the Map which contains tiles
class Map : public QGraphicsItem {
public:
    // Constructor for map size and tile size
    Map(int width, int height, int tileSize);

    // Method to load the map from a char-based map layout
    void loadFromCharMap(const char charMap[15][20]);

    // Method to set the tile at a specific coordinate with a given type
    void setTile(int x, int y, Tile::TileType type);

    // Check if the tile is walkable at a given coordinate
    bool isWalkable(int x, int y) const;

    // Return the bounding rectangle of the map
    QRectF boundingRect() const override;

    // Paint method to draw the map
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    // Get the tile type at a specific coordinate
    Tile::TileType getTileType(int x, int y) const;

    // Get the tile size in pixels
    int getTileSize() const { return tileSize; }

    // Get the width and height of the map in tiles
    int getWidth() const { return width; }
    int getHeight() const { return height; }

private:
    int width, height; // Width and height of the map in tiles
    int tileSize;      // Size of each tile in pixels
    std::vector<Tile> tiles; // Vector to store all tiles in the map
};

#endif // MAP_H
