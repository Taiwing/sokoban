#include "main.h"
#include "fenetre.h"
#include "partie.h"
#include "editeur.h"

int main()
{
  //on initie la bibliothèque et on crée la fenêtre
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window *sokoban = fenetre();

  //"niveau" est un tableau représentant la grille du niveau
  int index[144]; //"index" va être notre référence au niveau de base pour les tests de mouvement
  int niveau[144]; //"niveau" va être indiquer les positions actuelles des sprites dans le niveau

  //on invoque une première fois le menu et on affecte la valeur qu'il renvoit à "choix"
  int choix = menuPrincipal(sokoban);
  int choixJouer = 0;

  //si "choix" n'est pas égal à 0, on lance le choix du joueur
  while(choix)
  {
    switch(choix)
    {
      case 1:
        //partie(sokoban);
        choixJouer = menuJouer(sokoban);
        switch(choixJouer)
        {
          case 1:
            //test
            printf("test choix niveau\n");
            //on lance le menu de choix du niveau
            choixNiveau(sokoban, index, niveau);
            //puis on lance la partie
            partie(sokoban, index, niveau);
            break;
          case 2:
            //test
            printf("test niveau aléatoire\n");
            //on lance la sélection aléatoire de niveau
            niveauAleatoire(sokoban, index, niveau);
            //puis on lance la partie
            partie(sokoban, index, niveau);
            break;
          case 3:
            //test
            printf("test aventure\n");
            //on lance le mode aventure
            aventure(sokoban, index, niveau);
            break;
        }
        break;
      case 2:
        editeur(sokoban);
        break;
    }

    choix = menuPrincipal(sokoban); //une fois la partie ou la création de niveau terminée, on relance le menu
  }

  fin(sokoban);

  return EXIT_SUCCESS;
}
