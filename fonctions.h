#ifndef FONCTIONS_H
#define FONCTIONS_H

#include "initialisations.h"

#define ADRESSE_U8 0x40		// adresse des 8 LED
#define ADRESSE_TELEC 0xA2	// adresse de la telecommande
#define ADRESSE_BOUTON 0x33 // adresse de la touche du milieu
#define EXIT_SUCCESS 0
#define EXIT_FAILURE -1
#define PWM_G 50
#define PWM_D 50
#define STOP_MOTEURS 0
#define NB_MESURES_BATT 4			// nombre de mesures pour la batterie
#define NB_MESURES_IR 8				// nombre de mesures pour les capteurs
#define VALEUR_TENSION_CRITIQUE 159 // 595
#define VALEUR_DISTANCE_IR_MIN 58	// 71 // 0.4 m
#define VALEUR_DISTANCE_IR_MAX 20	// 269 // 1.5 m

extern volatile unsigned int UBAT;
extern volatile unsigned int IR_D;		  // distance capteur IR droit
extern volatile unsigned int IR_G;		  // distance cpateur IR gauche
extern volatile unsigned int distance_IR; // distance moyenne capteurs IR

void surveillance_batt(void);
void surveillance_tele(void);
void surveillance_capt(void);
void vitesse_moteur(int PWM_droite, int PWM_gauche);
void affichage_LED_I2C(unsigned char adresse, unsigned char donnee); // allumage des LED via le bus I2C
void affichage_batterie(int valeur_batterie);						 // affichage de la batterie sur les 8 LED
int moyenne(unsigned int liste[], int taille_liste);

#endif FONCTIONS_H