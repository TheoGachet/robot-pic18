#include "initialisations.h"

void init_frequence(void) // fréquence d'horloge = 8MHz
{
	OSCCONbits.IRCF0 = 1;
	OSCCONbits.IRCF1 = 1;
	OSCCONbits.IRCF2 = 1;
}

void init_entrees_sorties(void)
{
	// entrées
	TRISCbits.TRISC3 = 1; // SCL en entree (p176)
	TRISCbits.TRISC4 = 1; // SDA en entree (p176)
	TRISAbits.RA0 = 1;	// IR droit
	TRISAbits.RA1 = 1;	// IR gauche

	// sorties
	TRISCbits.RC1 = 0; // PWM Droit
	TRISCbits.RC2 = 0; // PWM Gauche
	TRISBbits.RB5 = 0; // LED Test
	TRISBbits.RB1 = 0; // IR_ON (alim)
	PORTBbits.RB1 = 0;
}

void init_moteurs(void)
{
	T2CONbits.T2CKPS1 = 0; // Prescaler = 4 (p135)
	T2CONbits.T2CKPS0 = 1;
	PR2 = 124;
	CCPR1L = 0; // le robot est initialement immobile
	CCPR2L = 0;
	CCP1CONbits.DC1B0 = 0; // p149
	CCP1CONbits.DC1B1 = 0;
	CCP2CONbits.DC2B0 = 0;
	CCP2CONbits.DC2B1 = 0;

	CCP1CONbits.CCP1M3 = 1; // mode PWM (p146)
	CCP1CONbits.CCP1M2 = 1;
	CCP2CONbits.CCP2M3 = 1;
	CCP2CONbits.CCP2M2 = 1;

	T2CONbits.TMR2ON = 1; // Timer2
	T2CONbits.T2OUTPS = 9;
	PIE1bits.TMR2IE = 1;
}

void init_uart(void)
{
	BAUDCONbits.BRG16 = 1;
	TXSTAbits.BRGH = 1; // p204
	TXSTAbits.SYNC = 0; // p207

	// p207
	SPBRG = 207;
	SPBRGH = 0;

	TRISCbits.RC6 = 1;
	TRISCbits.TRISC6 = 1; // TX1 en entree
	TRISCbits.TRISC7 = 1; // RX1 en entree
	RCSTAbits.SPEN = 1;	  // Port srie activ (p205)
	TXSTAbits.TXEN = 1;	  // Activation transmission (p204)
	RCSTAbits.CREN = 1;	  // Activation rception continue (p205)
}

void init_I2C(void)
{
	SSPSTAT = 0x80;     // Slew rate 100KHz
	SSPCON1 = 0x28;     // Master Mode Enable, Sclock = FOSC/(4 * (SSPADD + 1)) I2C bus
	SSPCON2 = 0x00;
	SSPADD  = 0x27;     // 50kHz - Prediviseur pour SCL = 100KHz a 8MHz
}

void init_ADC(void)
{
	// p227
	ADCON1bits.VCFG0 = 0;
	ADCON1bits.VCFG1 = 0;

	ADCON1bits.PCFG0 = 0; // entrees analogiques AN0, AN1 et AN2
	ADCON1bits.PCFG1 = 0;
	ADCON1bits.PCFG2 = 1;
	ADCON1bits.PCFG3 = 1;

	ADCON2bits.ADCS0 = 0; // Tad = 8 * Tosc = 1 µs
	ADCON2bits.ADCS1 = 0;
	ADCON2bits.ADCS2 = 1;

	ADCON2bits.ACQT0 = 0; // Tacqt = 6 * Tad = 6 µs
	ADCON2bits.ACQT1 = 1;
	ADCON2bits.ACQT2 = 0;

	PIE1bits.ADIE = 1;

	ADCON2bits.ADFM = 0; // on justifie à droite
	ADCON0bits.ADON = 1; // activation du CAN
	ADCON0bits.GO = 1;	 // début de la conversion

	ADCON0bits.CHS0 = 0;
	ADCON0bits.CHS1 = 1;
	ADCON0bits.CHS2 = 0;
	ADCON0bits.CHS3 = 0;
	PIE1bits.ADIE = 1;
	PIE1bits.TXIE = 1;
	PIR1bits.TXIF = 0;
}

void init_timer(void) // Timer0
{
	// p125
	T0CONbits.T08BIT = 0; // timer en 16 bits
	T0CONbits.T0CS = 0;	  // horloge interne
	T0CONbits.T0PS = 1;	  // PRE = 1:4

	T0CONbits.PSA = 0;	   // L'horloge du Timer0 vient de la sortie du préscalaire
	INTCONbits.TMR0IE = 1; // on active l'IT overflow du Timer0

	TMR0H = 0xD8; // B1 bits de poids fort
	TMR0L = 0xEF; // DF bits de poids faible

	T0CONbits.TMR0ON = 1; // on active le Timer0
}

void valider_IT(void)
{

	INTCONbits.INT0IE = 1;
	INTCON2bits.INTEDG0 = 0; // front descendant
	INTCONbits.GIE = 1;		 // on active les IT globales
	
}