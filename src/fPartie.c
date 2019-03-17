#include "fPartie.h"


//parcourt le tableau de niveau pour déterminer la position du sprite à l'écran en fonction de sa position dans le tableau
void convCasePos(int coordCase, SDL_Rect* position)
{
  //on calucule x et y en fonction de la position dans le tableau
  position->x = (coordCase * 34) % 408;
  position->y = ((coordCase * 34) / 408) * 34;
}

void deplacementMario(int niveau[144], int index[144], char direction, SDL_Window* sokoban)
{
  //d'abord on trouve mario dans le tableau niveau
  int caseMario = 0;
  for(int i = 0; i < 144; i++) //on parcourt le tableau
  {
    if(niveau[i] == 4) //si la case parcourue est celle où se trouve mario
    {
      caseMario = i; //on enregistre la position de mario dans le tableau
      i = 143; //on sort de la boucle
    }
  }

  //on vérifie la légalité du déplacement, et on l'effectue si c'est bon
  int legal = 0; //variable booléenne indiquant la légalité du mouvement
  int nouvellePos = 0; //variable déterminant la case vers laquelle le déplacement est effectué
  switch(direction)
  {
    case 'h':
      nouvellePos = caseMario - 12; //on détermine la case d'arrivée
      if(nouvellePos < 0 || niveau[nouvellePos] == 0) //on vérifie que la nouvelle position se trouve bien dans la grille et n'est pas un mur
      {
        legal = 0; //si c'est le cas, le mouvement est illégal
      }
      else if(niveau[nouvellePos] == 2 || niveau[nouvellePos] == 5) //si la nouvelle position est une caisse, ou une caisse validée
      {
        legal = deplacementCaisse(nouvellePos, 'h', niveau, index, sokoban); //on déplace la caisse et on affecte son retour à "legal"
      }
      else //si le déplacement s'effectue dans le vide ou sur un objectif
      {
        legal = 1;
      }
      //on effectue le déplacement en question
      deplacerMario(caseMario, nouvellePos, 'h', legal, niveau, index, sokoban);
      break;
    case 'b':
      nouvellePos = caseMario + 12; //on détermine la case d'arrivée
      if(nouvellePos > 143 || niveau[nouvellePos] == 0) //on vérifie que la nouvelle position se trouve bien dans la grille et n'est pas un mur
      {
        legal = 0; //si c'est le cas, le mouvement est illégal
      }
      else if(niveau[nouvellePos] == 2 || niveau[nouvellePos] == 5) //si la nouvelle position est une caisse, ou une caisse validée
      {
        legal = deplacementCaisse(nouvellePos, 'b', niveau, index, sokoban); //on déplace la caisse et on affecte son retour à "legal"
      }
      else //si le déplacement s'effectue dans le vide ou sur un objectif
      {
        legal = 1;
      }
      //on effectue le déplacement en question
      deplacerMario(caseMario, nouvellePos, 'b', legal, niveau, index, sokoban);
      break;
    case 'd':
      nouvellePos = caseMario + 1; //on détermine la case d'arrivée
      if(nouvellePos % 12 == 0 || niveau[nouvellePos] == 0) //on vérifie que la nouvelle position se trouve bien dans la grille et n'est pas un mur
      {
        legal = 0; //si c'est le cas, le mouvement est illégal
      }
      else if(niveau[nouvellePos] == 2 || niveau[nouvellePos] == 5) //si la nouvelle position est une caisse, ou une caisse validée
      {
        legal = deplacementCaisse(nouvellePos, 'd', niveau, index, sokoban); //on déplace la caisse et on affecte son retour à "legal"
      }
      else //si le déplacement s'effectue dans le vide ou sur un objectif
      {
        legal = 1;
      }
      //on effectue le déplacement en question
      deplacerMario(caseMario, nouvellePos, 'd', legal, niveau, index, sokoban);
      break;
    case 'g':
      nouvellePos = caseMario - 1; //on détermine la case d'arrivée
      if(caseMario % 12 == 0 || niveau[nouvellePos] == 0) //on vérifie que la nouvelle position se trouve bien dans la grille et n'est pas un mur
      {
        legal = 0; //si c'est le cas, le mouvement est illégal
      }
      else if(niveau[nouvellePos] == 2 || niveau[nouvellePos] == 5) //si la nouvelle position est une caisse, ou une caisse validée
      {
        legal = deplacementCaisse(nouvellePos, 'g', niveau, index, sokoban); //on déplace la caisse et on affecte son retour à "legal"
      }
      else //si le déplacement s'effectue dans le vide ou sur un objectif
      {
        legal = 1;
      }
      //on effectue le déplacement en question
      deplacerMario(caseMario, nouvellePos, 'g', legal, niveau, index, sokoban);
      break;
  }
}

void deplacerMario(int caseMario, int nouvellePos, char direction, int legal, int niveau[144], int index[144], SDL_Window* sokoban)
{
  //on récupère la surface de la fenêtre
  SDL_Surface *surface = SDL_GetWindowSurface(sokoban);

  //on charge les sprites nécessaires et les coordonnées pour afficher le mouvement
  SDL_Surface *mario = NULL;
  switch(direction)
  {
    case 'h':
      mario = SDL_LoadBMP("images/mario_haut.bmp");
      break;
    case 'b':
      mario = SDL_LoadBMP("images/mario_bas.bmp");
      break;
    case 'd':
      mario = SDL_LoadBMP("images/mario_droite.bmp");
      break;
    case 'g':
      mario = SDL_LoadBMP("images/mario_gauche.bmp");
      break;
  }
  SDL_Surface *casePrec = NULL;
  SDL_Rect posMario; //coordonnées où on va blitter mario et l'ancienne image
  //on crée une surface blanche pour effacer des cases
  SDL_Surface *blanc = SDL_CreateRGBSurface(0, 34, 34, 32, 0, 0, 0, 0);
  SDL_FillRect(blanc, NULL, SDL_MapRGB(blanc->format, 255, 255, 255));

  if(legal) //si le déplacement est légal
  {
    //on définie les nouvelles positions dans le tableau
    niveau[nouvellePos] = 4; //on place Mario à la nouvelle position dans le tableau
    niveau[caseMario] = index[caseMario]; //on remet la case où était mario à sa valeur par défaut
    if(index[caseMario] == 4 || index[caseMario] == 2) //s'il s'agit de la case du départ ou d'une caisse, alors on la remplace par du vide dans le tableau "niveau"
      niveau[caseMario] = 1;

    //on récupère les coordonnées des cases voulues grâce à la place qu'elles occupent dans le tableau
    convCasePos(nouvellePos, &posMario);
    SDL_Rect posPrec; //cordonnées de la case où était mario
    convCasePos(caseMario, &posPrec);
    switch(niveau[caseMario])
    {
      case 1: //si il était sur une case vide
        casePrec = SDL_CreateRGBSurface(0, 34, 34, 32, 0, 0, 0, 0);
        SDL_FillRect(casePrec, NULL, SDL_MapRGB(casePrec->format, 255, 255, 255)); //on la remplit de blanc
        break;
      case 3: //si c'était un objectif
        SDL_BlitSurface(blanc, NULL, surface, &posPrec); //on remplit la case de blanc avant de blitter l'objectif
        casePrec = SDL_LoadBMP("images/objectif.bmp"); //on y met l'image de l'objectif
        break;
    }
    //si mario se déplace vers une caisse dans l'index
    if(index[nouvellePos] == 2)
    {
      SDL_BlitSurface(blanc, NULL, surface, &posMario); //on remplit la nouvelle case de blanc avant de blitter mario
    }
    
    SDL_BlitSurface(mario, NULL, surface, &posMario); //on blitte le sprite de mario à la nouvelle position
    SDL_BlitSurface(casePrec, NULL, surface, &posPrec); //on blitte l'image par défaut de la case précédente sur celle-ci
  }
  else
  {
    //on récupère les coordonnées de mario
    convCasePos(caseMario, &posMario);

    casePrec = SDL_CreateRGBSurface(0, 34, 34, 32, 0, 0, 0, 0); //on crée une surface pour la case
    SDL_FillRect(casePrec, NULL, SDL_MapRGB(casePrec->format, 255, 255, 255));
    SDL_BlitSurface(casePrec, NULL, surface, &posMario); //on la remplit de blanc
    if(index[caseMario] == 3) //si mario est sur un objectif
    {
      SDL_Surface *objectif = SDL_LoadBMP("images/objectif.bmp");
      SDL_BlitSurface(objectif, NULL, surface, &posMario); //on le réaffiche sur la case avant mario
      SDL_FreeSurface(objectif);
    }
    SDL_BlitSurface(mario, NULL, surface, &posMario); //puis mario par dessus
  }

  //on affiche le résultat en fenêtre
  SDL_UpdateWindowSurface(sokoban);

  //on libère la mémoire
  SDL_FreeSurface(surface);
  SDL_FreeSurface(mario);
  SDL_FreeSurface(casePrec);
  SDL_FreeSurface(blanc);
}

int deplacementCaisse(int caseCaisse, char direction, int niveau[144], int index[144], SDL_Window* sokoban)
{
  //on vérifie la légalité du déplacement, et on l'effectue si c'est bon
  int legal = 0; //variable booléenne indiquant la légalité du mouvement
  int nouvellePos = 0; //variable déterminant la case vers laquelle le déplacement est effectué

  switch(direction)
  {
    case 'h':
      nouvellePos = caseCaisse - 12; //on détermine la case d'arrivée
      //on vérifie que la nouvelle position se trouve bien dans la grille et n'est pas un mur, ou une caisse
      if(nouvellePos < 0 || niveau[nouvellePos] == 0 || niveau[nouvellePos] == 2 || niveau[nouvellePos] == 5)
      {
        legal = 0; //si c'est le cas, le mouvement est illégal
      }
      else if(niveau[nouvellePos] == 1 || niveau[nouvellePos] == 3) //si le déplacement s'effectue dans le vide
      {
        legal = 1;
      }
      //on effectue le déplacement en question
      if(legal)
        deplacerCaisse(caseCaisse, nouvellePos, 'd', niveau, index, sokoban);
      break;
    case 'b':
      nouvellePos = caseCaisse + 12; //on détermine la case d'arrivée
      //on vérifie que la nouvelle position se trouve bien dans la grille et n'est pas un mur, ou une caisse
      if(nouvellePos > 143 || niveau[nouvellePos] == 0 || niveau[nouvellePos] == 2 || niveau[nouvellePos] == 5)
      {
        legal = 0; //si c'est le cas, le mouvement est illégal
      }
      else if(niveau[nouvellePos] == 1 || niveau[nouvellePos] == 3) //si le déplacement s'effectue dans le vide
      {
        legal = 1;
      }
      //on effectue le déplacement en question
      if(legal)
        deplacerCaisse(caseCaisse, nouvellePos, 'b', niveau, index, sokoban);
      break;
    case 'd':
      nouvellePos = caseCaisse + 1; //on détermine la case d'arrivée
      //on vérifie que la nouvelle position se trouve bien dans la grille et n'est pas un mur, ou une caisse
      if(nouvellePos % 12 == 0 || niveau[nouvellePos] == 0 || niveau[nouvellePos] == 2 || niveau[nouvellePos] == 5)
      {
        legal = 0; //si c'est le cas, le mouvement est illégal
      }
      else if(niveau[nouvellePos] == 1 || niveau[nouvellePos] == 3) //si le déplacement s'effectue dans le vide
      {
        legal = 1;
      }
      //on effectue le déplacement en question
      if(legal)
        deplacerCaisse(caseCaisse, nouvellePos, 'd', niveau, index, sokoban);
      break;
    case 'g':
      nouvellePos = caseCaisse - 1; //on détermine la case d'arrivée
      //on vérifie que la nouvelle position se trouve bien dans la grille et n'est pas un mur, ou une caisse
      if(caseCaisse % 12 == 0 || niveau[nouvellePos] == 0 || niveau[nouvellePos] == 2 || niveau[nouvellePos] == 5)
      {
        legal = 0; //si c'est le cas, le mouvement est illégal
      }
      else if(niveau[nouvellePos] == 1 || niveau[nouvellePos] == 3) //si le déplacement s'effectue dans le vide
      {
        legal = 1;
      }
      //on effectue le déplacement en question
      if(legal)
        deplacerCaisse(caseCaisse, nouvellePos, 'g', niveau, index, sokoban);
      break;
  }

  //puis on envoit la valeur de "legal" à "deplacementMario"
  return legal;
}

void deplacerCaisse(int caseCaisse, int nouvellePos, char direction, int niveau[144], int index[144], SDL_Window* sokoban)
{
  //on récupère la surface de la fenêtre
  SDL_Surface *surface = SDL_GetWindowSurface(sokoban);

  //on définit les nouvelles positions dans le tableau
  niveau[caseCaisse] = index[caseCaisse]; //on remet la case où était la caisse à sa valeur par défaut
  if(index[caseCaisse] == 4) //s'il s'agit de la case du départ, alors on la remplace par du vide dans le tableau "niveau"
    niveau[caseCaisse] = 1;

  //on charge les sprites nécessaires et les coordonnées pour afficher le mouvement
  SDL_Surface *caisse = NULL;
  switch(index[nouvellePos]) //on vérifie si la nouvelle position est un objectif ou non
  {
    case 3: //si c'est un objectif
      caisse = SDL_LoadBMP("images/caisse_ok.bmp");
      niveau[nouvellePos] = 5; //on place la caisse validée à la nouvelle position dans le tableau
      break;
    default: //sinon
      caisse = SDL_LoadBMP("images/caisse.bmp"); //si ce n'en est pas un
      niveau[nouvellePos] = 2; //on place la caisse à la nouvelle position dans le tableau
      break;
  }
  SDL_Surface *casePrec = NULL;
  casePrec = SDL_CreateRGBSurface(0, 34, 34, 32, 0, 0, 0, 0);
  SDL_FillRect(casePrec, NULL, SDL_MapRGB(casePrec->format, 255, 255, 255)); //on la remplit de blanc

  //on récupère les coordonnées des cases voulues grâce à la place qu'elles occupent dans le tableau
  SDL_Rect posCaisse; //coordonnées où on va blitter la caisse
  convCasePos(nouvellePos, &posCaisse);
  SDL_Rect posPrec; //cordonnées de la case où était la caisse avant le mouvement
  convCasePos(caseCaisse, &posPrec);

  SDL_BlitSurface(casePrec, NULL, surface, &posPrec); //on blitte l'image par défaut de la case précédente sur celle-ci
  if(niveau[caseCaisse] == 3) //si la case quittée est un objectif
  {
    SDL_Surface *objectif = SDL_LoadBMP("images/objectif.bmp"); //on charge l'image de l'objectif
    SDL_BlitSurface(objectif, NULL, surface, &posPrec); //on la blitte à l'ancienne position
    SDL_FreeSurface(objectif); //on libère la mémoire
  }
  SDL_BlitSurface(caisse, NULL, surface, &posCaisse); //on blitte le sprite de la caisse à la nouvelle position

  //on affiche le résultat en fenêtre
  SDL_UpdateWindowSurface(sokoban);

  //on libère la mémoire
  SDL_FreeSurface(surface);
  SDL_FreeSurface(caisse);
  SDL_FreeSurface(casePrec);
}

void testVictoire(int* continuer, int niveau[144], int index[144], SDL_Window* sokoban)
{
  //variable bool indiquant s'il y a un objectif ou pas
  int objectif = 0;

  //on lit le tableau pour voir s'il reste des objectifs
  for(int i = 0; i < 144; i++)
  {
    if(niveau[i] == 3) //si on trouve un objectif
    {
      objectif = 1; //alors on indique qu'il y a un objectif
      i = 143; //on sort de la boucle
    }

    if(niveau[i] == 4 && index[i] == 3) //si mario est sur un objectif
    {
      objectif = 1; //alors on indique qu'il y a un objectif
      i = 143; //on sort de la boucle
    }
  }

  //si aucun objectif n'a été trouvé
  if(!objectif)
  {
    //on indique à la boucle d'évènements dans partie.c de se terminer
    *continuer = 0;

    //on charge la surface de la fenêtre
    SDL_Surface* surface = SDL_GetWindowSurface(sokoban);

    //on valide toutes les caisses
    SDL_Surface *caisseValide = SDL_LoadBMP("images/caisse_validee.bmp"); //on charge l'image
    SDL_Rect posCaisse; //on crée la variable de coordonnées
    for(int i = 0; i < 144; i++) //on parcourt l'index
    {
      if(index[i] == 3) //si la case de l'index correspond à un objectif
      {
        convCasePos(i, &posCaisse); //on charge les coordonnées de la case trouvée
        SDL_BlitSurface(caisseValide, NULL, surface, &posCaisse); //on blitte l'image à la bonne position
      }
    }
    SDL_UpdateWindowSurface(sokoban); //on affiche les changements à l'écran

    //on met un petit delay, pour que le joueur puisse voir son dernier coup
    SDL_Delay(1500);

    //on charge le message de victoire dans la surface de la fenêtre
    SDL_Surface* victoire = SDL_LoadBMP("images/victoire.bmp");
    SDL_Rect pVictoire;
    pVictoire.x = 0;
    pVictoire.y = 0;
    SDL_BlitSurface(victoire, NULL, surface, &pVictoire);
    SDL_UpdateWindowSurface(sokoban);

    //on refait une pause pour que l'utilisateur puisse voir le message
    SDL_Delay(2000);

    //on libère la mémoire
    SDL_FreeSurface(surface);
    SDL_FreeSurface(victoire);
    SDL_FreeSurface(caisseValide);
  }
}
