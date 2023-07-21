#include "interruptions.h"

volatile unsigned char compteur = 0;
volatile char flag_telecommande = 0;
volatile char flag_capteurs_IR = 0;
volatile char flag_batterie = 0;
volatile char robot = 0;

#pragma code HighVector = 0x08

void IntHighVector(void)
{
	_asm goto HighISR _endasm
}

#pragma code
#pragma interrupt HighISR

void HighISR(void)
{
	//printf("Test dans HighISR\n\r");

	// IT telecommande (Int0)
	if (INTCONbits.INT0IF)
	{
		INTCONbits.INT0IF = 0; // IT acquittée
		flag_telecommande = 1;
		//printf("IT Telecommande\n\r"); // fonctionne
	}

	// IT Timer0
	if (INTCONbits.TMR0IF)
	{
		INTCONbits.TMR0IF = 0; // IT acquittée
		flag_capteurs_IR = 1;
		//printf("IT Timer0\n\r"); // fonctionne
		compteur++;

		// p.17r pour les valeurs
		TMR0H = 0xB1;
		TMR0L = 0xDF;

		if (compteur == 1) // 10 // le compteur se déclenche toutes les 10*20 = 200 ms
		{
			flag_batterie = 1;
			compteur = 0;
			//printf("IT Batterie\n\r"); // fonctionne
		}
	}
}