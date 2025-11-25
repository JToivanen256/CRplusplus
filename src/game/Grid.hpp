#include <vector>
#include <utility>
#include <SFML/Graphics.hpp>

class Grid
{
public:

    enum class TileFlag { Grass, Water, Bridge };

    struct Tile
    {
        sf::RectangleShape shape;
        bool walkable = true;
        float cost = 1.f; //if we want to have different tiles with different walking speeds
        std::vector<int> occupants; //Mby with an id that the unit class has? Don't know if this is even necessary
        TileFlag flag = TileFlag::Grass; 
    };

private:
    int tileSize = 13;
    int columns, rows;
    std::vector<Tile> tiles;

public:
    Grid(int xSize, int ySize);
    ~Grid() = default;

    void draw(sf::RenderWindow& window);
    void defaultGridMap();

    int getColumns() const;
    int getRows() const;
    int getTileSize() const;

    Tile& at(int row, int col);
    const Tile& at(int row, int col) const;

    bool inBounds(int row, int col) const;
    int toIndex(int row, int col) const;


    //Converts free coordinates to grid Tiles and vice versa 
    std::pair<int,int> worldToGrid(const sf::Vector2f& worldPos) const;
    sf::Vector2f gridToWorld(int row, int col) const; // just a helper for the centering function
    sf::Vector2f gridToWorldCenter(int row, int col) const; //use this in the movement logic

    void addOccupant(int row, int col, int unitId);
    void removeOccupant(int row, int col, int unitId);
    const std::vector<int>& getOccupants(int row, int col) const;
    bool isOccupied(int row, int col) const;

    // neighbor helper for A* pathfinding
    std::vector<std::pair<int,int>> getNeighbors(int row, int col, bool diagonals = false) const;
};