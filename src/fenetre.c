#include "fenetre.h"

SDL_Window* fenetre()
{
  SDL_Window *window = SDL_CreateWindow("Mario Sokoban", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 408, 408, SDL_WINDOW_SHOWN);
  SDL_SetWindowIcon(window, SDL_LoadBMP("images/caisse.bmp"));

  return window;
}

void fin(SDL_Window *sokoban)
{
  SDL_DestroyWindow(sokoban);
  SDL_Quit();
}
