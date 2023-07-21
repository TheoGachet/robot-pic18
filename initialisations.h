#ifndef INITIALISATIONS_H
#define INITIALISATIONS_H

#include <p18f2520.h>
#include "MI2C.h"

#include "fonctions.h"
#include "interruptions.h"

void init_frequence(void);
void init_entrees_sorties(void);
void init_moteurs(void);
void init_timer(void);
void init_uart(void);
void init_I2C(void);
void init_ADC(void);
void valider_IT(void);

#endif INITIALISATIONS_H