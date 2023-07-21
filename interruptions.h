#ifndef INTERRUPTIONS_H
#define INTERRUPTIONS_H

#include "initialisations.h"

extern volatile char flag_telecommande;
extern volatile char flag_capteurs;
extern volatile char flag_batterie;
extern volatile char flag_moteur;
extern volatile char robot; // variable d'état du robot (1 = marche, 0 = arret)

void HighISR(void); // interruption haute

#endif INTERRUPTIONS_H