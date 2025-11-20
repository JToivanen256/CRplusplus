#include "Grid.hpp"

Grid::Grid(int xSize, int ySize): columns(xSize), rows(ySize), tiles(xSize * ySize)
{
    for(int row = 0; row < rows; row++)
    {
        for(int column = 0; column < columns; column++)
        {
            //gets the current tile. Meaning that row * columns is just which row we are at
            //and + column gets the current column if that makes sense :D 
            auto& t = tiles[row * columns + column];
            t.setSize(sf::Vector2f(tileSize, tileSize));
            //type casts the index number in for loop to a float in order to calculate the setposition as float 
            t.setPosition(static_cast<float>(column) * tileSize, tileSize * static_cast<float>(row));
            
            /*
            if(row == 10 - 1 && column == 3 - 1)
            {
                t.setFillColor(sf::Color::Blue);

            }
            else
            {
                t.setFillColor(sf::Color::Green);

            }
            */



            t.setOutlineThickness(1.f);
            t.setOutlineColor(sf::Color::Black);
        }
    }
}

sf::RectangleShape& Grid::at(int row, int col)
{
    return tiles[row * columns + col];
}

int Grid::getColumns() const 
{
    return columns; 
}
int Grid::getRows() const 
{
    return rows; 
}

void Grid::draw(sf::RenderWindow& window)
{
    for (auto& t : tiles) 
    { 
        window.draw(t); 
    }
}

void Grid::defaultGridMap()
{
    for(int row = 0; row < rows; row++)
    {
        for(int column = 0; column < columns; column++)
        {
            //gets the current tile. Meaning that row * columns is just which row we are at
            //and + column gets the current column if that makes sense :D 
            auto& t = tiles[row * columns + column];

            if(row == (rows/2) || row == ((rows/2) - 1) || row == ((rows/2) - 2) || row == ((rows/2) + 1))
            {
                if(column == (columns/4) || column == ((columns/4) + 1) || column == (((columns/4) * 3)) || column == ((((columns/4) * 3) +1)))
                {
                    t.setFillColor(sf::Color(210,105,30));

                }
                else
                {

                    t.setFillColor(sf::Color::Blue);
                }

            }
            
            else
            {
                t.setFillColor(sf::Color::Green);

            }
        }
    }
}
