#include "Grid.hpp"
#include <algorithm>

Grid::Grid(int xSize, int ySize): columns(xSize), rows(ySize), tiles(xSize * ySize)
{
    for(int row = 0; row < rows; row++)
    {
        for(int column = 0; column < columns; column++)
        {
            auto& t = tiles[row * columns + column];
            t.shape.setSize(sf::Vector2f(static_cast<float>(tileSize), static_cast<float>(tileSize)));
            t.shape.setPosition(static_cast<float>(column) * tileSize, static_cast<float>(row) * tileSize);
            t.shape.setOutlineThickness(1.f);
            t.shape.setOutlineColor(sf::Color::Black);
            t.walkable = true;
            t.cost = 1.f;
            t.occupants.clear();
            t.flag = TileFlag::Grass;
        }
    }
}

Grid::Tile& Grid::at(int row, int col)
{
    return tiles[row * columns + col];
}

const Grid::Tile& Grid::at(int row, int col) const
{
    return tiles[row * columns + col];
}

int Grid::getColumns() const { return columns; }
int Grid::getRows() const { return rows; }
int Grid::getTileSize() const { return tileSize; }

bool Grid::inBounds(int row, int col) const
{
    return row >= 0 && row < rows && col >= 0 && col < columns;
}

int Grid::toIndex(int row, int col) const
{
    return row * columns + col;
}

std::pair<int,int> Grid::worldToGrid(const sf::Vector2f& worldPos) const
{
    int col = static_cast<int>(worldPos.x) / tileSize;
    int row = static_cast<int>(worldPos.y) / tileSize;
    return {row, col};
}

sf::Vector2f Grid::gridToWorld(int row, int col) const
{
    return sf::Vector2f(static_cast<float>(col * tileSize), static_cast<float>(row * tileSize));
}

sf::Vector2f Grid::gridToWorldCenter(int row, int col) const
{
    auto topLeft = gridToWorld(row, col);
    return topLeft + sf::Vector2f(tileSize * 0.5f, tileSize * 0.5f);
}

void Grid::addOccupant(int row, int col, int unitId)
{
    if(!inBounds(row,col)) return;
    auto& occ = tiles[toIndex(row,col)].occupants;
    if(std::find(occ.begin(), occ.end(), unitId) == occ.end())
        occ.push_back(unitId);
}

void Grid::removeOccupant(int row, int col, int unitId)
{
    if(!inBounds(row,col)) return;
    auto& occ = tiles[toIndex(row,col)].occupants;
    auto it = std::find(occ.begin(), occ.end(), unitId);
    if(it != occ.end()) occ.erase(it);
}

const std::vector<int>& Grid::getOccupants(int row, int col) const
{
    static const std::vector<int> empty;
    if(!inBounds(row,col)) return empty;
    return tiles[toIndex(row,col)].occupants;
}

bool Grid::isOccupied(int row, int col) const
{
    if(!inBounds(row,col)) return false;
    return !tiles[toIndex(row,col)].occupants.empty();
}

std::vector<std::pair<int,int>> Grid::getNeighbors(int row, int col, bool diagonals) const
{
    //Multidimensional arrays for both diagonal checking and non-diagonal chcking
    static const int d4[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};
    static const int d8[8][2] = {{-1,0},{1,0},{0,-1},{0,1},{-1,-1},{-1,1},{1,-1},{1,1}};

    std::vector<std::pair<int,int>> out;
    if(diagonals)
    {
        for(auto &d : d8)
        {
            int r = row + d[0], c = col + d[1];
            if(inBounds(r,c)) out.emplace_back(r,c);
        }
    }
    else
    {
        for(auto &d : d4)
        {
            int r = row + d[0], c = col + d[1];
            if(inBounds(r,c)) out.emplace_back(r,c);
        }
    }
    return out;
}

void Grid::draw(sf::RenderWindow& window)
{
    for (auto& t : tiles)
    {
        window.draw(t.shape);
    }
}

void Grid::defaultGridMap()
{
    for(int row = 0; row < rows; row++)
    {
        for(int column = 0; column < columns; column++)
        {
            auto& t = tiles[row * columns + column];
            if(row == (rows/2) || row == ((rows/2) - 1) || row == ((rows/2) - 2) || row == ((rows/2) + 1))
            {
                if(column == (columns/4) || column == ((columns/4) + 1) || column == (((columns/4) * 3)) || column == ((((columns/4) * 3) +1)))
                {
                    // bridge tiles
                    t.shape.setFillColor(sf::Color(210,105,30));
                    t.walkable = false;
                    t.flag = TileFlag::Bridge;
                    // for instance: t.cost = 10.f;
                }
                else //WAter tiles
                {

                    t.shape.setFillColor(sf::Color(0, 153, 255));
                    t.walkable = true;
                    t.cost = 1.f;
                    t.flag = TileFlag::Water;
                }
            }
            else //Ground tiles
            {
                
                t.shape.setFillColor(sf::Color::Green);
                t.walkable = true;
                t.cost = 1.f;
                t.flag = TileFlag::Grass;
            }
        }
    }
}