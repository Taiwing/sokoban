#ifndef FPARTIE_H
#define FPARTIE_H
#include "main.h"

void convCasePos(int coordCase, SDL_Rect* position);
void deplacementMario(int niveau[144], int index[144], char direction, SDL_Window* sokoban);
void deplacerMario(int caseMario, int nouvellePos, char direction, int legal, int niveau[144], int index[144], SDL_Window* sokoban);
int deplacementCaisse(int caseCaisse, char direction, int niveau[144], int index[144], SDL_Window* sokoban);
void deplacerCaisse(int caseCaisse, int nouvellePos, char direction, int niveau[144], int index[144], SDL_Window* sokoban);
void testVictoire(int* continuer, int niveau[144], int index[144], SDL_Window* sokoban);

#endif
