#ifndef NIVEAUX_H
#define NIVEAUX_H
#include "main.h"
#include "partie.h" //pour la fonction aventure
#include<time.h> //pour faire un nombre aléatoire

void choixNiveau(SDL_Window* sokoban, int index[144], int niveau[144]); //menu de choix de niveau
void chargerNiveau(FILE *niveaux, int index[144], int niveau[144]); //charge le niveau choisi
void niveauAleatoire(SDL_Window* sokoban, int index[144], int niveau[144]); //sélection aléatoire d'un niveau dans le fichier de niveaux
void afficherNiveau(SDL_Window* sokoban, int index[144]); //on affiche le niveau choisi dans la fenêtre de jeu
void aventure(SDL_Window *sokoban, int index[144], int niveau[144]); //joue les 20 premiers niveaux d'affilé

#endif
