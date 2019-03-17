#ifndef FEDITEUR_H
#define FEDITEUR_H
#include "main.h"
#include "fPartie.h" //pour "convCasePos"

void afficherGrille(int posCase, int niveau[144], SDL_Window *sokoban);
void afficherCurseur(int curseur, SDL_Surface *surface, SDL_Window *sokoban);
void enregistrerNiveau(int niveau[144]);
void reafficherCase(int niveau[144], int posCase);
int erreurNiveau(int niveau[144]);

#endif
