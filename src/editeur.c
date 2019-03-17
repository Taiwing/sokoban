#include "editeur.h"

void editeur(SDL_Window* sokoban)
{
  //on crée le tableau qui va servir à enregistrer le niveau créé
  int niveau[144];
  for(int i = 0; i < 144; i++) //on initie tout le tableau à 6 pour commencer
  {
    niveau[i] = 6;
  }

  //on charge les images dont on aura besoin
  SDL_Surface *surface = SDL_GetWindowSurface(sokoban);
  SDL_Surface *mur = SDL_LoadBMP("images/mur.bmp");
  SDL_Surface *passage = SDL_CreateRGBSurface(0, 34, 34, 32, 0, 0, 0, 0);
  SDL_FillRect(passage, NULL, SDL_MapRGB(passage->format, 255, 255, 255));
  SDL_Surface *caisse = SDL_LoadBMP("images/caisse.bmp");
  SDL_Surface *objectif = SDL_LoadBMP("images/objectif.bmp");
  SDL_Surface *depart = SDL_LoadBMP("images/mario_bas.bmp");
  SDL_Surface *caisseOk = SDL_LoadBMP("images/caisse_ok.bmp");
  SDL_Surface *bleu = SDL_CreateRGBSurface(0, 34, 34, 32, 0, 0, 0, 0);
  SDL_FillRect(bleu, NULL, SDL_MapRGB(bleu->format, 0, 0, 128));

  //maintenant on attend l'input du joueur
  SDL_Event event;
  int continuer = 1, curseur = 0, preCurseur = 1, input = 1, instructions = 1, erreur = 0;
  char stringErreur[50]; //variable dans laquelle on va stocker l'adresse de l'image d'erreur s'il y en a
  SDL_Rect position;
  while(continuer)
  {
    //si c'est la première fois que la boucle s'exécute ou que l'utilisateur appui sur 'i'
    while(instructions)
    {
      //on affiche les instructions
      afficherInstructions("images/instructions_editeur.bmp", sokoban);

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
              input = 1; //on raffiche le curseur
              afficherGrille(144, niveau, sokoban); //on raffiche l'éditeur
              break;
          }
      }
    }

    //on affiche le curseur
    if(input)
    {
      afficherCurseur(curseur, surface, sokoban);
      input = 0;
    }

    //on réaffiche la case précédente sans le curseur
    convCasePos(preCurseur, &position); //on définit la position pointée
    switch(niveau[preCurseur])
    {
      case 0:
        SDL_BlitSurface(mur, NULL, surface, &position); //on blitte l'image
        afficherGrille(preCurseur, niveau, sokoban); //on réaffiche la grille sur cette case
        break;
      case 1:
        SDL_BlitSurface(passage, NULL, surface, &position); //on blitte l'image
        afficherGrille(preCurseur, niveau, sokoban); //on réaffiche la grille sur cette case
        break;
      case 2:
        SDL_BlitSurface(caisse, NULL, surface, &position); //on blitte l'image
        afficherGrille(preCurseur, niveau, sokoban); //on réaffiche la grille sur cette case
        break;
      case 3:
        SDL_BlitSurface(passage, NULL, surface, &position); //on efface l'image
        SDL_BlitSurface(objectif, NULL, surface, &position); //on blitte l'image
        afficherGrille(preCurseur, niveau, sokoban); //on réaffiche la grille sur cette case
        break;
      case 4:
        SDL_BlitSurface(passage, NULL, surface, &position); //on efface l'image
        SDL_BlitSurface(depart, NULL, surface, &position); //on blitte l'image
        afficherGrille(preCurseur, niveau, sokoban); //on réaffiche la grille sur cette case
        break;
      case 5:
        SDL_BlitSurface(caisseOk, NULL, surface, &position); //on blitte l'image
        afficherGrille(preCurseur, niveau, sokoban); //on réaffiche la grille sur cette case
        break;
      case 6:
        SDL_BlitSurface(bleu, NULL, surface, &position); //on blitte l'image
        afficherGrille(preCurseur, niveau, sokoban); //on réaffiche la grille sur cette case
        break;
    }
    SDL_UpdateWindowSurface(sokoban); //on affiche les changements

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
            if(curseur > 11) //on ne monte pas si on est à la première ligne
            {
              preCurseur = curseur;
              curseur -= 12;
              input = 1; //s'il y a eu un input valide du joueur
            }
            break;
          case SDLK_DOWN:
            if(curseur < 132) //on ne descend pas si on est à la dernière ligne
            {
              preCurseur = curseur;
              curseur += 12;
              input = 1; //s'il y a eu un input valide du joueur
            }
            break;
          case SDLK_RIGHT:
            if(curseur < 143) //si on est pas sur la dernière case
            {
              preCurseur = curseur;
              curseur ++;
              input = 1; //s'il y a eu un input valide du joueur
            }
            break;
          case SDLK_LEFT:
            if(curseur > 0) // si on est pas sur la première case
            {
              preCurseur = curseur;
              curseur--;
              input = 1; //s'il y a eu un input valide du joueur
            }
            break;
          case SDLK_m:
            niveau[curseur] = 0; //on change la valeur de la case dans le tableau
            convCasePos(curseur, &position); //on définit la position pointée
            SDL_BlitSurface(mur, NULL, surface, &position); //on blitte l'image sur la surface
            afficherGrille(curseur, niveau, sokoban); //on réaffiche la grille sur cette case
            SDL_UpdateWindowSurface(sokoban); //on affiche les changements
            input = 1; //s'il y a eu un input valide du joueur
            break;
          case SDLK_p:
            niveau[curseur] = 1; //on change la valeur de la case dans le tableau
            convCasePos(curseur, &position); //on définit la position pointée
            SDL_BlitSurface(passage, NULL, surface, &position); //on blitte l'image sur la surface
            afficherGrille(curseur, niveau, sokoban); //on réaffiche la grille sur cette case
            SDL_UpdateWindowSurface(sokoban); //on affiche les changements
            input = 1; //s'il y a eu un input valide du joueur
            break;
          case SDLK_c:
            niveau[curseur] = 2; //on change la valeur de la case dans le tableau
            convCasePos(curseur, &position); //on définit la position pointée
            SDL_BlitSurface(caisse, NULL, surface, &position); //on blitte l'image sur la surface
            afficherGrille(curseur, niveau, sokoban); //on réaffiche la grille sur cette case
            SDL_UpdateWindowSurface(sokoban); //on affiche les changements
            input = 1; //s'il y a eu un input valide du joueur
            break;
          case SDLK_o:
            niveau[curseur] = 3; //on change la valeur de la case dans le tableau
            convCasePos(curseur, &position); //on définit la position pointée
            SDL_BlitSurface(passage, NULL, surface, &position); //on efface la case
            SDL_BlitSurface(objectif, NULL, surface, &position); //on blitte l'image sur la surface
            afficherGrille(curseur, niveau, sokoban); //on réaffiche la grille sur cette case
            SDL_UpdateWindowSurface(sokoban); //on affiche les changements
            input = 1; //s'il y a eu un input valide du joueur
            break;
          case SDLK_d:
            niveau[curseur] = 4; //on change la valeur de la case dans le tableau
            convCasePos(curseur, &position); //on définit la position pointée
            SDL_BlitSurface(passage, NULL, surface, &position); //on efface la case
            SDL_BlitSurface(depart, NULL, surface, &position); //on blitte l'image sur la surface
            afficherGrille(curseur, niveau, sokoban); //on réaffiche la grille sur cette case
            SDL_UpdateWindowSurface(sokoban); //on affiche les changements
            input = 1; //s'il y a eu un input valide du joueur
            break;
          case SDLK_v:
            niveau[curseur] = 5; //on change la valeur de la case dans le tableau
            convCasePos(curseur, &position); //on définit la position pointée
            SDL_BlitSurface(caisseOk, NULL, surface, &position); //on blitte l'image sur la surface
            afficherGrille(curseur, niveau, sokoban); //on réaffiche la grille sur cette case
            SDL_UpdateWindowSurface(sokoban); //on affiche les changements
            input = 1; //s'il y a eu un input valide du joueur
            break;
          case SDLK_e: //si le joueur veut enregistrer son niveau
            erreur = erreurNiveau(niveau); //on vérifie s'il ya des erreurs
            if(!erreur) //s'il n'y a pas d'erreurs
            {
              enregistrerNiveau(niveau); //on enregistre le niveau
              afficherInstructions("images/editeur/niveau_enregistre.bmp", sokoban);
              SDL_Delay(2000); //on laisse passer deux secondes pour que le joueur voit le message
              continuer = 0; //on sort de la boucle
            }
            break;
          case SDLK_i: //si le joueur appuie sur 'i' pour "instructions"
            instructions = 1;
            break;
        }
    }

  while(erreur)
  {
    switch(erreur)
    {
      case 1: //s'il n'y a pas de départ
        sprintf(stringErreur, "images/editeur/erreur1.bmp"); //"sprintf" permet d'écrire dans une chaîne
        break;
      case 2: //s'il y a plus d'un départ
        sprintf(stringErreur, "images/editeur/erreur2.bmp");
        break;
      case 3: //s'il y a plus d'objectifs que de caisses
        sprintf(stringErreur, "images/editeur/erreur3.bmp");
        break;
      case 4: //s'il y a plus d'objectifs que de caisses et pas de départ
        sprintf(stringErreur, "images/editeur/erreur4.bmp");
        break;
      case 5: //s'il y a plus d'objectifs que de caisses et plus d'un départ
        sprintf(stringErreur, "images/editeur/erreur5.bmp");
        break;
    }

    //on affiche l'erreur
    afficherInstructions(stringErreur, sokoban);

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
          case SDLK_r: //si l'utilisateur appui sur 'r'
            erreur = 0; //on sort de la page d'erreur
            input = 1; //on raffiche le curseur
            afficherGrille(144, niveau, sokoban); //on raffiche l'éditeur
            break;
        }
    }
  }

  }

  //on libère la mémoire
  SDL_FreeSurface(surface);
  SDL_FreeSurface(mur);
  SDL_FreeSurface(passage);
  SDL_FreeSurface(caisse);
  SDL_FreeSurface(objectif);
  SDL_FreeSurface(depart);
  SDL_FreeSurface(caisseOk);
  SDL_FreeSurface(bleu);
}
