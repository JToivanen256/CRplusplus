#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <SFML/Graphics.hpp>
#include "Map.hpp"

class Renderer {
private:
  Map& map_;

public:
  void renderAll();
};

#endif