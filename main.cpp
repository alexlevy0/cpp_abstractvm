#include <cstdlib>
#include "Core.hpp"

int main()
{
  Core game;

  if (game.initialize() == false)
    return (-1);
  while (game.update() == true)
    game.draw();
  return EXIT_SUCCESS;
}
