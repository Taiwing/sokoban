#include "fEditeur.h"

void afficherGrille(int posCase, int niveau[144], SDL_Window *sokoban)
{
  //on affiche la grille de l'éditeur
  SDL_Surface *surface = SDL_GetWindowSurface(sokoban); //on récupère la surface de la fenêtre
  int reaffichage = 0;
  SDL_Rect position; //on crée la variable pour les coordonnées des cases

  for(int i = 0; i < 144; i++)
  {
    if((niveau[i] != 6) && (posCase == 144)) //si une case est différente de sa valeur par défaut
      reaffichage = 1; //alors on met "reaffichage" à 1
  }

  if(posCase == 144) //si "posCase" est à 144 on qu'on réaffiche l'éditeur, alors on remplit l'écran de bleu
  {
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0, 0, 128)); //on remplie la surface de bleu
  }

  if(reaffichage) //si on raffiche l'éditeur
  {
    SDL_Surface *mur = SDL_LoadBMP("images/mur.bmp");
    SDL_Surface *passage = SDL_CreateRGBSurface(0, 34, 34, 32, 0, 0, 0, 0);
    SDL_FillRect(passage, NULL, SDL_MapRGB(passage->format, 255, 255, 255));
    SDL_Surface *caisse = SDL_LoadBMP("images/caisse.bmp");
    SDL_Surface *objectif = SDL_LoadBMP("images/objectif.bmp");
    SDL_Surface *depart = SDL_LoadBMP("images/mario_bas.bmp");
    SDL_Surface *caisseOk = SDL_LoadBMP("images/caisse_ok.bmp");

    for(int i = 0; i < 144; i++)
    {
      switch(niveau[i])
      {
        case 0:
          convCasePos(i, &position);
          SDL_BlitSurface(mur, NULL, surface, &position);
          break;
        case 1:
          convCasePos(i, &position);
          SDL_BlitSurface(passage, NULL, surface, &position);
          break;
        case 2:
          convCasePos(i, &position);
          SDL_BlitSurface(caisse, NULL, surface, &position);
          break;
        case 3:
          convCasePos(i, &position);
          SDL_BlitSurface(passage, NULL, surface, &position);
          SDL_BlitSurface(objectif, NULL, surface, &position);
          break;
        case 4:
          convCasePos(i, &position);
          SDL_BlitSurface(passage, NULL, surface, &position);
          SDL_BlitSurface(depart, NULL, surface, &position);
          break;
        case 5:
          convCasePos(i, &position);
          SDL_BlitSurface(caisseOk, NULL, surface, &position);
          break;
      }
    }

    //on libère la mémoire
    SDL_FreeSurface(mur);
    SDL_FreeSurface(passage);
    SDL_FreeSurface(caisse);
    SDL_FreeSurface(objectif);
    SDL_FreeSurface(depart);
    SDL_FreeSurface(caisseOk);
  }

  SDL_Surface *grilleCentre = SDL_LoadBMP("images/editeur/grille_centre.bmp");
  SDL_Surface *grilleGauche = SDL_LoadBMP("images/editeur/grille_gauche.bmp");
  SDL_Surface *grilleDroit = SDL_LoadBMP("images/editeur/grille_droit.bmp");
  SDL_Surface *grilleHaut = SDL_LoadBMP("images/editeur/grille_haut.bmp");
  SDL_Surface *grilleBas = SDL_LoadBMP("images/editeur/grille_bas.bmp");
  SDL_Surface *grilleCoinHautGauche = SDL_LoadBMP("images/editeur/grille_coin_haut_gauche.bmp");
  SDL_Surface *grilleCoinBasGauche = SDL_LoadBMP("images/editeur/grille_coin_bas_gauche.bmp");
  SDL_Surface *grilleCoinHautDroit = SDL_LoadBMP("images/editeur/grille_coin_haut_droit.bmp");
  SDL_Surface *grilleCoinBasDroit = SDL_LoadBMP("images/editeur/grille_coin_bas_droit.bmp");
  for(int i = 0; i < 144; i++)
  {
    if(posCase != 144) //si "posCase" n'est pas à sa valeur par défaut
      i = posCase; //on met "i" à la valeur précisée

    //on charge la position de la case
    convCasePos(i, &position);

    //on teste la valeur de "i"
    if(i == 0)
    {
      SDL_BlitSurface(grilleCoinHautGauche, NULL, surface, &position);
      if(posCase != 144) //si "posCase" n'est pas à sa valeur par défaut
        i = 144; //on sor de la boucle
    }
    else if(i == 11)
    {
      SDL_BlitSurface(grilleCoinHautDroit, NULL, surface, &position);
      if(posCase != 144) //si "posCase" n'est pas à sa valeur par défaut
        i = 144; //on sor de la boucle
    }
    else if(i == 132)
    {
      SDL_BlitSurface(grilleCoinBasGauche, NULL, surface, &position);
      if(posCase != 144) //si "posCase" n'est pas à sa valeur par défaut
        i = 144; //on sor de la boucle
    }
    else if(i == 143)
    {
      SDL_BlitSurface(grilleCoinBasDroit, NULL, surface, &position);
      if(posCase != 144) //si "posCase" n'est pas à sa valeur par défaut
        i = 144; //on sor de la boucle
    }
    else if((i > 0) && (i < 11))
    {
      SDL_BlitSurface(grilleHaut, NULL, surface, &position);
      if(posCase != 144) //si "posCase" n'est pas à sa valeur par défaut
        i = 144; //on sor de la boucle
    }
    else if((i > 132) && (i < 143))
    {
      SDL_BlitSurface(grilleBas, NULL, surface, &position);
      if(posCase != 144) //si "posCase" n'est pas à sa valeur par défaut
        i = 144; //on sor de la boucle
    }
    else if(((i % 12) == 0) && (i != 0) && (i != 132))
    {
      SDL_BlitSurface(grilleGauche, NULL, surface, &position);
      if(posCase != 144) //si "posCase" n'est pas à sa valeur par défaut
        i = 144; //on sor de la boucle
    }
    else if((((i + 1) % 12) == 0) && (i != 11) && (i != 143))
    {
      SDL_BlitSurface(grilleDroit, NULL, surface, &position);
      if(posCase != 144) //si "posCase" n'est pas à sa valeur par défaut
        i = 144; //on sor de la boucle
    }
    else
    {
      SDL_BlitSurface(grilleCentre, NULL, surface, &position);
      if(posCase != 144) //si "posCase" n'est pas à sa valeur par défaut
        i = 144; //on sor de la boucle
    }
  }
  SDL_UpdateWindowSurface(sokoban); //on affiche la grille

  SDL_FreeSurface(grilleCentre);
  SDL_FreeSurface(grilleGauche);
  SDL_FreeSurface(grilleDroit);
  SDL_FreeSurface(grilleHaut);
  SDL_FreeSurface(grilleBas);
  SDL_FreeSurface(grilleCoinHautGauche);
  SDL_FreeSurface(grilleCoinBasGauche);
  SDL_FreeSurface(grilleCoinHautDroit);
  SDL_FreeSurface(grilleCoinBasDroit);
  SDL_FreeSurface(surface);
}

void afficherCurseur(int curseur, SDL_Surface *surface, SDL_Window *sokoban)
{
  //on initie la position de la case
  SDL_Rect position;
  convCasePos(curseur, &position);

  //on charge l'image du curseur
  SDL_Surface *imageCurseur = SDL_LoadBMP("images/curseur.bmp");
  SDL_BlitSurface(imageCurseur, NULL, surface, &position);

  //on affiche les changements
  SDL_UpdateWindowSurface(sokoban);

  //on libère la mémoire
  SDL_FreeSurface(imageCurseur);
}

void enregistrerNiveau(int niveau[144])
{
  //on parcourt le tableau pour remettre les cases 6 à 0
  for(int i = 0; i < 144; i++)
  {
    if(niveau[i] == 6)
      niveau[i] = 0;
  }

  //on ouvre le fichier en mode ajout (écrit à la toute fin)
  FILE *niveaux = fopen("niveaux.lvl", "a");

  //on y enregistre le niveau voulu
  for(int i = 0; i < 145; i++)
  {
    switch(i)
    {
      case 144: //si on a fini de parcourir le tableau
        fputc('\n', niveaux); //on saute une ligne à la fin
        break;
      default: //tant qu'il y a des caractères à lire
        switch(niveau[i])
        {
          case 0:
            fputc('0', niveaux); //on écrit le caractère correspondant dans le fichier
            break;
          case 1:
            fputc('1', niveaux); //on écrit le caractère correspondant dans le fichier
            break;
          case 2:
            fputc('2', niveaux); //on écrit le caractère correspondant dans le fichier
            break;
          case 3:
            fputc('3', niveaux); //on écrit le caractère correspondant dans le fichier
            break;
          case 4:
            fputc('4', niveaux); //on écrit le caractère correspondant dans le fichier
            break;
          case 5:
            fputc('5', niveaux); //on écrit le caractère correspondant dans le fichier
            break;
        }
        break;
    }
  }

  //on ferme le fichier
  fclose(niveaux);
}

int erreurNiveau(int niveau[144])
{
  //valeur qui sera retournée par la fonction pour dire à l'éditeur si le niveau est valide ou non
  int erreur = 0;

  //valeurs de test
  int nbDepart = 0, nbCaisses = 0, nbObjectifs = 0;

  //on parcourt le tableau puis on vérifie que le niveau est valide
  for(int i = 0; i < 144; i ++)
  {
    switch(niveau[i])
    {
      case 2: //si c'est une caisse
        nbCaisses++;
        break;
      case 3: //si c'est un objectif
        nbObjectifs++;
        break;
      case 4: //si c'est un départ
        nbDepart++;
        break;
    }
  }
  if(nbDepart != 1) //si le nombre de départ n'est pas strictement égal à 1
  {
    switch(nbDepart)
    {
      case 0: //s'il n'y a pas de départ
        erreur++; //on incrémente "erreur" de 1
        break;
      default: //s'il y a plus d'un départ
        erreur += 2; //on incrémente "erreur" de 2
        break;
    }
  }
  if(nbCaisses < nbObjectifs) //s'il y a moins de caisses que d'objectifs
   erreur += 3; //on incrémente "erreur" de 3

  //on retourne la valeur trouvée
  return erreur;
}
