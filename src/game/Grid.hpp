#include <vector>
#include <SFML/Graphics.hpp>


class Grid
{
private:
    int tileSize = 25;
    int columns, rows;
    std::vector<sf::RectangleShape> tiles;

public:
    Grid(int xSize, int ySize);
    ~Grid() = default;

    void draw(sf::RenderWindow& window);

    int getColumns() const;
    int getRows() const;

    sf::RectangleShape& at(int row, int col);

};

