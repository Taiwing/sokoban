#include "niveaux.h"

void choixNiveau(SDL_Window* sokoban, int index[144], int niveau[144])
{
    //on ouvre le fichier de niveaux
    FILE * niveaux;
    niveaux = fopen("niveaux.lvl", "r");

    //on compte le nombre de niveaux
    char stringNiv[150]; //on crée un chaine de caractères pour lire le fichier
    int nbNiv = 0;
    while(fgets(stringNiv, 150, niveaux) != NULL)
    {
      nbNiv++; //on compte le nombre de niveaux dans le fichier
    }
    rewind(niveaux); //on revient au début du fichier
    printf("nbNib: %d\n", nbNiv);

    //on attend l'input du joueur pour qu'il change de niveau ou en sélectionne un
    SDL_Event event;
    int continuer = 1, input = 1, niv = 0, instructions = 1;
    while(continuer)
    {
      printf("niv: %d\n", niv);
      //si c'est la première fois que la boucle s'exécute ou que l'utilisateur appui sur 'i'
      while(instructions)
      {
        //on affiche les instructions
        afficherInstructions("images/instructions_choix_niveau.bmp", sokoban);

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
                input = 1; //on raffiche le niveau
                break;
            }
        }
      }

      //on charge le niveau et on l'affiche
      if(input) //s'il y a eu un input valide de la part du joueur
      {
        //on se place au bon endroit dans le fichier
        for(int i = 0; i < niv; i ++)
        {
          fgets(stringNiv, 150, niveaux);
        }
        chargerNiveau(niveaux, index, niveau);
        afficherNiveau(sokoban, niveau);
        rewind(niveaux); //on revient au début du fichier
        input = 0;
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
            case SDLK_RIGHT:
              if(niv < (nbNiv - 1)) //si on est pas à la fin de la liste
              {
                niv++; //on incrémente "niv" pour indiquer quel niveau doit s'afficher
                input = 1;
              }
              break;
            case SDLK_LEFT:
              if(niv > 0) //si on est pas au début de la liste
              {
                niv--; //on incrémente "niv" pour indiquer quel niveau doit s'afficher
                input = 1;
              }
              break;
            case SDLK_j: //si le joueur appuie sur "j" pour "jouer"
              continuer = 0; //alors on sort de la boucle, donc du menu, et le niveau choisi sera joué
              break;
            case SDLK_i: //si le joueur appuie sur 'i' pour "instructions"
              instructions = 1; //alors on envoit 1 à la boucle du début pour els afficher
              break;
          }
      }
    }
    //on ferme le fichier
    fclose(niveaux);
}

void chargerNiveau(FILE *niveaux, int index[144], int niveau[144])
{
  //variable "char" dans laquelle on récupère la valeur donnée par le fichier de niveau
  char valeur = '0';

  //on exécute la boucle une fois pour chaque case de la grille
  for(int i = 0; i < 144; i ++)
  {
    //on récupère la valeur de la case dans le fichier de niveau
    valeur = fgetc(niveaux);

    //on affecte cette valeur à la case du tableau correspondante
    switch(valeur)
    {
      case '0':
        index[i] = 0;
        break;
      case '1':
        index[i] = 1;
        break;
      case '2':
        index[i] = 2;
        break;
      case '3':
        index[i] = 3;
        break;
      case '4':
        index[i] = 4;
        break;
      case '5':
        index[i] = 5;
        break;
    }

    //on affecte également les valeurs de l'index au tableau de niveau
    niveau[i] = index[i];
    //si on a une caisse validée dans l'index
    if(index[i] == 5)
    {
      index[i] = 3; //on met un objectif à la place
      niveau[i] = 5; // et une caisse validée dessus
    }
  }
}

void niveauAleatoire(SDL_Window* sokoban, int index[144], int niveau[144])
{
  //"nbNiv" va stocker le nombre de niveaux disponibles, et "ligneNiv" sera la ligne du niveau choisi
  int nbNiv = 0, ligneNiv = 0;

  //on ouvre le fichier de niveaux
  FILE *niveaux = NULL;
  niveaux = fopen("niveaux.lvl", "r");
  char stringNiv[150]; //on crée un chaine de caractères pour lire le fichier
  char valeur = '0'; //on crée une variable valeur pour récupérer le niveau dans un tableau

  while(fgets(stringNiv, 150, niveaux) != NULL)
  {
    nbNiv++; //on compte le nombre de niveaux dans le fichier
    //test
    printf("%s\n", stringNiv);
  }

  //test
  printf("valeur de nbNiv: %d\n", nbNiv);

  //Sélection aléatoire de la ligne et donc du niveau
  srand(time(NULL));
  ligneNiv = (rand() % nbNiv) + 1;

  //test
  printf("valeur de ligneNiv: %d\n", ligneNiv);

  rewind(niveaux); //on revient au début du fichier

  for(int i = 0; i < (ligneNiv - 1); i++) //on lit le fichier jusqu'à la ligne choisie aléatoirement
  {
    fgets(stringNiv, 150, niveaux);
    //test
    printf("%s\n", stringNiv);
  }

  for(int i = 0; i < 144; i ++) //on exécute la boucle une fois pour chaque case de la grille
  {
    //on récupère la valeur de la case dans le fichier de niveau
    valeur = fgetc(niveaux);

    //on affecte cette valeur à la case du tableau correspondante
    switch(valeur)
    {
      case '0':
        index[i] = 0;
        break;
      case '1':
        index[i] = 1;
        break;
      case '2':
        index[i] = 2;
        break;
      case '3':
        index[i] = 3;
        break;
      case '4':
        index[i] = 4;
        break;
      case '5':
        index[i] = 5;
        break;
    }

    //on affecte également les valeurs de l'index au tableau de niveau
    niveau[i] = index[i];
    if(index[i] == 5) //si la case est une caisse validée
    {
      index[i] = 3; //on met un objectif dans l'index
      niveau[i] = 5; //et la caisse dans le niveau
    }

    //test
    printf("%d", niveau[i]);
  }
  printf("\n");

  fclose(niveaux); //on referme le fichier une fois qu'on a fini de l'utiliser

  //on affiche le niveau choisi
  afficherNiveau(sokoban, niveau);
}

void afficherNiveau(SDL_Window* sokoban, int index[144])
{
  //on récupère la surface de la fenêtre
  SDL_Surface *surface = SDL_GetWindowSurface(sokoban);
  SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 255, 255, 255)); //on remplie la surface de blanc pour effacer le dernier écran

  //on charge les spites nécessaires à la construction du niveau
  SDL_Surface *mur = SDL_LoadBMP("images/mur.bmp");
  SDL_Surface *passage = SDL_CreateRGBSurface(0, 34, 34, 32, 0, 0, 0, 0);
  SDL_FillRect(passage, NULL, SDL_MapRGB(passage->format, 255, 255, 255));
  SDL_Surface *caisse = SDL_LoadBMP("images/caisse.bmp");
  SDL_Surface *objectif = SDL_LoadBMP("images/objectif.bmp");
  SDL_Surface *depart = SDL_LoadBMP("images/mario_bas.bmp");
  SDL_Surface *caisseOk = SDL_LoadBMP("images/caisse_ok.bmp");

  //on crée la variable "p" de position
  SDL_Rect p;
  p.x = 0;
  p.y = 0;

  //on lit le tableau "index", et on blit l'image en fonction de la valeur lue
  for(int i = 0; i < 144; i++)
  {
    //on switch la valeur de "index[i]"
    switch(index[i])
    {
      case 0:
        SDL_BlitSurface(mur, NULL, surface, &p);
        break;
      case 1:
        SDL_BlitSurface(passage, NULL, surface, &p);
        break;
      case 2:
        SDL_BlitSurface(caisse, NULL, surface, &p);
        break;
      case 3:
        SDL_BlitSurface(objectif, NULL, surface, &p);
        break;
      case 4:
        SDL_BlitSurface(depart, NULL, surface, &p);
        break;
      case 5:
        SDL_BlitSurface(caisseOk, NULL, surface, &p);
        break;
    }

    //on change les coordonnées pour charger le prochain sprite
    p.x += 34; //on se décale d'une case à droite (34 pixels)

    if(p.x == 408) //si on est arrivé au bout de la ligne
    {
      p.x = 0; //on revient au début de la ligne
      p.y += 34; //on saute une ligne
    }
  }

  //on met à jour la fenêtre
  SDL_UpdateWindowSurface(sokoban);

  //on libère la mémoire
  SDL_FreeSurface(mur);
  SDL_FreeSurface(passage);
  SDL_FreeSurface(caisse);
  SDL_FreeSurface(objectif);
  SDL_FreeSurface(depart);
  SDL_FreeSurface(surface);
}

void aventure(SDL_Window *sokoban, int index[144], int niveau[144])
{
  //on ouvre le fichier de niveaux
  FILE * niveaux;
  niveaux = fopen("niveaux.lvl", "r");

  //variables permettant de lire le fichier
  char stringNiv[150];
  int niv = 0;//permet de savoir à quel niveau on en est

  while(niv < 20) //la boucle s'exécute tant que le joueur n pas atteint terminé le niveau 20
  {
    printf("niveau: %d\n", (niv + 1));
    //on se place au bon endroit dans le fichier
    for(int i = 0; i < niv; i++)
    {
      fgets(stringNiv, 150, niveaux);
    }
    chargerNiveau(niveaux, index, niveau); //on lit le niveau dans le fichier
    rewind(niveaux); //on se replace au début
    afficherNiveau(sokoban, niveau);
    partie(sokoban, index, niveau);
    niv++; //on incrémente à chaque fois que le joueur termine un niveau
  }

  //quand le mode aventure est terminé on affiche un écran de félicitations

  //on ferme le fichier
  fclose(niveaux);
}
