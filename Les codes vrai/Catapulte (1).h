#include "piloterTir.h"


// MOTEUR_C (0x60) = gros moteur => inclinaison du lanceur
// MOTEUR_D (0x65) = petit moteur => retrait de la goupille
//
// Logique :
// 1. MOTEUR_C tourne AVANT => inclinaison du bras
// Encodeur incremente angle UNIQUEMENT direction AVANT
// 2. Angle cible atteint => MOTEUR_C stop
// 3. MOTEUR_D tourne => retrait goupille → tir
// 4. MOTEUR_C recule => retour position initiale


#include <Wire.h>


// ADRESSES I2C DRV8830


#define MOTEUR_C 0x65
#define MOTEUR_D 0x60

#define ARRET 0x00
#define AVANT 0x01
#define ARRIERE 0x02
#define FREIN 0x03


// BROCHES ENCODEUR

#define A 2
#define B 6


// PARAMETRES AJUSTABLES


#define DEG_PAR_IMPULSION 5
#define ANGLE_CIBLE 25 // << changer ici
#define ANGLE_MAX_RETOUR 150
#define IMPULSIONS_PAR_TOUR 12

#define VITESSE_INCLINAISON 200
#define VITESSE_RETOUR 20
#define VITESSE_GOUPILLE 200
#define DUREE_GOUPILLE 10000
#define TIMEOUT_MOTEUR 10000


// VARIABLES ENCODEUR


extern int Etat_capteur_precedant;
extern int Etat_capteur;
extern int n_var;
extern int n_a;
extern int angle;
extern int compteur_tours;
extern float DistTir;
extern int angle_calcule;
extern int angle_normalise;

extern bool moteurC_en_avant;
void moteurC_avant(byte vitesse);
void moteurC_arriere(byte vitesse);
void moteurC_stop();
void moteurD_avant(byte vitesse);
void moteurD_stop();
void encodeur_reset();
int encodeur_lire();
void phase_inclinaison(int angle_cible) ;
void phase_goupille() ;
void sequence_complete(int angle_cible) ;
void Catapulte();
void CalculAngle();