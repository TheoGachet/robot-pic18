#include "fonctions.h"

volatile unsigned int dist = -1;   // Distance moyenne lue par les capteurs
volatile unsigned int dist_D = -1; // Distance lue par le capteur droit
volatile unsigned int dist_G = -1; // Distance lue par le capteur gauche
volatile unsigned int UBAT = 255;

int liste_UBAT[NB_MESURES_BATT] = {VALEUR_TENSION_CRITIQUE, VALEUR_TENSION_CRITIQUE, VALEUR_TENSION_CRITIQUE, VALEUR_TENSION_CRITIQUE};
int liste_dist[NB_MESURES_IR] = {50, 50, 50, 50, 50, 50, 50, 50};

void affichage_LED_I2C(unsigned char adresse, unsigned char donnee)
{
	SSPCON2bits.SEN = 1; // on envoie Start sur le bus I2C
	while (!PIR1bits.SSPIF)
		; // on boucle jusqu'à ce que le signal de départ ait bien été envoyé (SSPIF=1)
	PIR1bits.SSPIF = 0;

	SSPBUF = adresse; // on envoie l'adresse de l'appareil que l'on veut atteindre avec le bus I2C
	while (!PIR1bits.SSPIF)
		;
	PIR1bits.SSPIF = 0;

	while (SSPCON2bits.ACKSTAT)
		; // on attend que la cible réponde avec un signal d'acquittement (ACK) pour confirmer la réception de l'adresse

	SSPBUF = donnee; // on envoie la donnee a la cible
	while (!PIR1bits.SSPIF)
		;
	PIR1bits.SSPIF = 0;

	while (SSPCON2bits.ACKSTAT)
		; // on attend que la cible réponde en envoyant un signal d'acquittement (ACK) pour confirmer la réception des donnees

	SSPCON2bits.PEN = 1; // on envoie un signal de fin (Stop) sur le bus I2C pour indiquer la fin de la transmission
	while (!PIR1bits.SSPIF)
		; // on attend que le signal de fin soit envoyé avec succès
	PIR1bits.SSPIF = 0;
}

void vitesse_moteur(int PWM_droite, int PWM_gauche)
{
	// vitesse de rotation
	CCPR1L = PWM_droite; // PWM Droite
	CCPR2L = PWM_gauche; // PWM Gauche
	// sens de rotation
	PORTAbits.RA6 = 0; // DIRD
	PORTAbits.RA7 = 0; // DIRG
}

int moyenne(unsigned int liste[], int taille_liste)
{
	int valeur_moyennee = 0;
	int i;
	for (i = 0; i < taille_liste; i++)
	{
		valeur_moyennee = valeur_moyennee + liste[i];
	}
	return valeur_moyennee / taille_liste;
}

void surveillance_capt(void)
{
    int val_moy; // utile pour stocker la moyenne des distances
    int i;

    // décalage des valeurs vers la droite
    for (i = NB_MESURES_IR-1; i>0; i--)
    {
        liste_dist[i] = liste_dist[i-1];
    }
    
    // capteur IR droit
    ADCON0bits.CHS = 0; // channel 0
    ADCON0bits.GO = 1;
    while (ADCON0bits.DONE);

    dist_D = (int)ADRESH;

    // capteur IR gauche
    ADCON0bits.CHS = 1; // channel 1
    ADCON0bits.GO = 1;
    while (ADCON0bits.DONE);

    dist_G = (int)ADRESH;

    dist = (dist_G + dist_D) / 2; // moyenne des deux capteurs
    liste_dist[0] = dist;

    val_moy = moyenne(liste_dist, NB_MESURES_IR); // moyenne des 8 mesures

    printf("dist_D : %d \r\ndist_G : %d\r\n\r\n", dist_D, dist_G);

    if (robot == 1 && val_moy > VALEUR_DISTANCE_IR_MAX && val_moy < VALEUR_DISTANCE_IR_MIN)
    {
        vitesse_moteur(PWM_D, PWM_G);
    }
    else
    {
        vitesse_moteur(STOP_MOTEURS, STOP_MOTEURS);
    }
}

void surveillance_tele(void)
{
    char buffer_telec[3]; // tableau utilisé pour stocker les donnees lues

    Lire_i2c_Telecom(ADRESSE_TELEC, buffer_telec); // lecture des donnees et envoi dans le tableau, l'adresse de la telecommande est 0xA2

    if (buffer_telec[1] == ADRESSE_BOUTON) // on verifie que c'est la touche centrale qui est appuyee
    {
        robot = (robot == 0);
        PORTBbits.RB5 = (robot == 1);
    }
}

void surveillance_batt(void)
{
    // Decalage des indices
    int i;
    int val_moy;

    // décalage des valeurs vers la droite
    for (i = NB_MESURES_BATT-1; i>0; i--)
    {
        liste_UBAT[i] = liste_UBAT[i-1];
    }

    // Selection du channel 2
    ADCON0bits.CHS0 = 0;
    ADCON0bits.CHS1 = 1;
    ADCON0bits.CHS2 = 0;
    ADCON0bits.CHS3 = 0;

    // Demarrage de la conversion
    ADCON0bits.GO = 1;

    while (ADCON0bits.DONE);

    // Les registres ADRESH et ADRESL contiennent le résultat de la conversion AN
    UBAT = (unsigned int)ADRESH;   // on lit ADRESH qui contient les bits de poids fort

    liste_UBAT[0] = UBAT;

    val_moy = moyenne(liste_UBAT, NB_MESURES_BATT); // 4 mesures/seconde ?

    if (val_moy < VALEUR_TENSION_CRITIQUE)
    {
        PORTBbits.RB5 = 1;  // on allume la LED Test
        printf("Valeur batterie : %d (batterie faible)\r\n", val_moy);
        affichage_batterie(val_moy);
    }
    else
    {
		PORTBbits.RB5 = 0;  // on allume la LED Test
        printf("\r\nValeur batterie : %d \r\n", val_moy);
        affichage_batterie(val_moy);
    }
}

void affichage_batterie(int valeur_batterie)
{
    int valeur_led = 0b11111111;

    if (1) 
    {
        int pourcentage_batterie = 100 * valeur_batterie / 255;
	    printf("pourcentage = %d \n\r", pourcentage_batterie);

        if (pourcentage_batterie > 88) valeur_led = 0b00000000;
        else if (pourcentage_batterie > 75 && pourcentage_batterie <= 88) valeur_led = 0b10000000;
        else if (pourcentage_batterie > 63 && pourcentage_batterie <= 75) valeur_led = 0b11000000;
        else if (pourcentage_batterie > 50 && pourcentage_batterie <= 63) valeur_led = 0b11100000;
        else if (pourcentage_batterie > 38 && pourcentage_batterie <= 50) valeur_led = 0b11110000;
        else if (pourcentage_batterie > 25 && pourcentage_batterie <= 38) valeur_led = 0b11111000;
        else if (pourcentage_batterie > 13 && pourcentage_batterie <= 25) valeur_led = 0b11111100;
        else if (pourcentage_batterie > 0 && pourcentage_batterie <= 13) valeur_led = 0b11111110;
        affichage_LED_I2C(ADRESSE_U8, valeur_led);
    }
}