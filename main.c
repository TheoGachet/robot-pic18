#include "initialisations.h"

#include <p18f2520.h>
#include <stdio.h>
#include "MI2C.h"

#pragma config OSC = INTIO67
#pragma config PBADEN = OFF, WDT = OFF, LVP = OFF, DEBUG = ON

void main(void)
{
	init_uart();
	init_frequence();
	init_entrees_sorties();
	init_moteurs();
	init_timer();
	init_I2C();
	init_ADC();
	valider_IT();
	
	while (1)
    {
        if (flag_batterie == 1)
        {
            flag_batterie = 0;          // le flag est remis a 0
            surveillance_batt();    	// on demarre la surveillance batterie
        }
        if (flag_capteurs_IR == 1)
        {
            flag_capteurs_IR = 0;       // le flag est remis a 0
            surveillance_capt();        // on demarre la lecture des capteurs IR
        }
        if (flag_telecommande == 1)
        {
            flag_telecommande = 0;      // le flag est remis a 0
            surveillance_tele();		// on demarre la surveillance telecommande
        }
    }
}