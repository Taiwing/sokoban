#include "partie.h"

void partie(SDL_Window* sokoban, int index[144], int niveau[144])
{
  //d'abord on sauvegarde le niveau si le joueur veut le recommencer
  int sauvegardeNiv[144];
  for(int i = 0; i < 144; i++)
  {
    sauvegardeNiv[i] = niveau[i];
  }

  //maintenant on attend l'input du joueur
  SDL_Event event;
  int continuer = 1, instructions = 0;
  int legal = 0; //variable de test de la fonction testMouvement
  while(continuer)
  {
    //si l'utilisateur appuie sur 'i'
    while(instructions)
    {
      //on affiche les instructions
      afficherInstructions("images/instructions_mario_sokoban.bmp", sokoban);

      //on attend un évènement (input du joueur)
      SDL_WaitEvent(&event);

      //on teste l'évènement
      switch(event.type)
      {
        case SDL_QUIT: //s'il veut quitter
          exit(EXIT_SUCCESS);
          break;
        case SDL_KEYDOWN:
          switch(event.key.keysym.sym)
          {
            case SDLK_i: //si l'utilisateur appui sur 'i'
              instructions = 0; //on sort de la page d'instructions
              afficherNiveau(sokoban, niveau); //on raffiche le niveau
              break;
          }
      }
    }
    //on attend un évènement (input du joueur)
    SDL_WaitEvent(&event);

    //on teste l'évènement
    switch(event.type)
    {
      case SDL_QUIT: //s'il veut quitter
        exit(EXIT_SUCCESS);
        break;
      case SDL_KEYDOWN:
        switch(event.key.keysym.sym)
        {
          case SDLK_UP:
            //on effectue le déplacement
            deplacementMario(niveau, index, 'h', sokoban);
            testVictoire(&continuer, niveau, index, sokoban);
            break;
          case SDLK_DOWN:
            //on effectue le déplacement
            deplacementMario(niveau, index, 'b', sokoban);
            testVictoire(&continuer, niveau, index, sokoban);
            break;
          case SDLK_RIGHT:
            //on effectue le déplacement
            deplacementMario(niveau, index, 'd', sokoban);
            testVictoire(&continuer, niveau, index, sokoban);
            break;
          case SDLK_LEFT:
            //on effectue le déplacement
            deplacementMario(niveau, index, 'g', sokoban);
            testVictoire(&continuer, niveau, index, sokoban);
            break;
          case SDLK_i:
            //on affiche les instructions
            instructions = 1;
            break;
          case SDLK_r:
            for(int i = 0; i < 144; i++)
            {
              niveau[i] = sauvegardeNiv[i]; //on redonne à "niveau" ses valeurs par défaut
            }
            afficherNiveau(sokoban, niveau); //puis on raffiche le niveau
            break;
        }
    }
  }

}
