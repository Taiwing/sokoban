#include "menus.h"

int menuPrincipal(SDL_Window *sokoban)
{
  //variable qu'on mettre en return
  int choix = 0;

  //on charge l'image du menu
  SDL_Surface *surface = SDL_GetWindowSurface(sokoban);
  SDL_Surface *menu = SDL_LoadBMP("images/menu.bmp");
  SDL_Rect pMenu;
  pMenu.x = 0;
  pMenu.y = 0;
  SDL_BlitSurface(menu, NULL, surface, &pMenu);
  SDL_UpdateWindowSurface(sokoban);

  //menu
  int continuer = 1;
  SDL_Event event;
  while(continuer)
  {
    SDL_WaitEvent(&event); //on attend qu'un évènement se produise et on l'affecte à "event"

    switch(event.type)
    {
      case SDL_QUIT: //si l'utilisateur choisi de fermer la fenêtre
        continuer = 0; //on sort du menu
        choix = 0; //et "menuPrincipal" va renvoyer 0 pour fermer le programme
        break;
      case SDL_KEYDOWN: //si l'utilisateur appuie sur une touche
        switch(event.key.keysym.sym)
        {
          case SDLK_j: //si l'utilisateur tape sur 'j'
            continuer = 0;
            choix = 1; //on met "choix" à 1
            break;
          case SDLK_e: //si l'utilisateur tape sur 'e'
            continuer = 0;
            choix = 2; //on met "choix" à 2
            break;
        }
        break;
    }
  }

  //on libère la mémoire
  SDL_FreeSurface(surface);
  SDL_FreeSurface(menu);

  return choix;
}

int menuJouer(SDL_Window *sokoban)
{
  //on charge l'image du menu
  SDL_Surface *surface = SDL_GetWindowSurface(sokoban);
  SDL_Surface *menu = SDL_LoadBMP("images/menu_jouer.bmp");
  SDL_Rect pMenu;
  pMenu.x = 0;
  pMenu.y = 0;
  SDL_BlitSurface(menu, NULL, surface, &pMenu);
  SDL_UpdateWindowSurface(sokoban);

  //menu
  int continuer = 1, choix = 0;
  SDL_Event event;
  while(continuer)
  {
    SDL_WaitEvent(&event); //on attend qu'un évènement se produise et on l'affecte à "event"

    switch(event.type)
    {
      case SDL_QUIT: //si l'utilisateur choisi de fermer la fenêtre
        exit(EXIT_SUCCESS); //on sort du programme
        break;
      case SDL_KEYDOWN: //si l'utilisateur appuie sur une touche
        switch(event.key.keysym.sym)
        {
          case SDLK_c: //si l'utilisateur tape sur 'c'
            continuer = 0;
            choix = 1; //on met "choix" à 1
            break;
          case SDLK_h: //si l'utilisateur tape sur 'h'
            continuer = 0;
            choix = 2; //on met "choix" à 2
            break;
          case SDLK_a: //si l'utilisateur tape sur 'a'
            continuer = 0;
            choix = 3; //on met "choix" à 3
            break;
        }
        break;
    }
  }

  //on retourne la valeur de "choix" au main
  printf("valeur de choix: %d\n", choix);
  return choix;
}

void afficherInstructions(char fichier[], SDL_Window *sokoban)
{
  //test
  printf("test afficherInstructions:\nfichier: %s\n", fichier);

  //on récupère la surface pour afficher les instructions
  SDL_Surface *surface = SDL_GetWindowSurface(sokoban);

  //on charge l'image et les coordonnées
  SDL_Surface *instructions = SDL_LoadBMP(fichier);
  SDL_Rect pos;
  pos.x = 0;
  pos.y = 0;

  //on blitte l'image voulue
  SDL_BlitSurface(instructions, NULL, surface, &pos);

  //on met à jour la fenêtre (gahagahgah)
  SDL_UpdateWindowSurface(sokoban);

  //on libère la mémoire
  SDL_FreeSurface(surface);
  SDL_FreeSurface(instructions);
}
