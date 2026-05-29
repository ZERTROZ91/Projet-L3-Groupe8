#include "Catapulte.h"
#include "Tunnel.h"

int Etat_capteur_precedant = 0;
int Etat_capteur = 0;
int n_var = 0;
int n_a = 0;
int angle = 0;
int compteur_tours = 0;
float DistTir = 150;
int angle_calcule = 0;
int angle_normalise = 0;

bool moteurC_en_avant = false;



// COMMANDES MOTEUR_C (inclinaison)


void moteurC_avant(byte vitesse) {
  piloterTir(MOTEUR_C, AVANT, vitesse);
  moteurC_en_avant = true;
  Serial.println("[MOT_C] AVANT — compteur actif");
}

void moteurC_arriere(byte vitesse) {
  piloterTir(MOTEUR_C, ARRIERE, vitesse);
  moteurC_en_avant = false;
  Serial.println("[MOT_C] ARRIERE — compteur inactif");
}

void moteurC_stop() {
  piloterTir(MOTEUR_C, ARRET, 0);
  moteurC_en_avant = false;
  Serial.println("[MOT_C] ARRET");
}


// COMMANDES MOTEUR_D (goupille)


void moteurD_avant(byte vitesse) {
  piloterTir(MOTEUR_D, AVANT, vitesse);
}

void moteurD_stop() {
  piloterTir(MOTEUR_D, ARRET, 0);
}

// ENCODEUR — RESET

void encodeur_reset() {
  n_var = 0;
  n_a = 0;
  angle = 0;
  compteur_tours = 0;
  Etat_capteur_precedant = digitalRead(A);
  Serial.println("Reset");
}

// ENCODEUR — LECTURE
// Incremente UNIQUEMENT si moteurC_en_avant = true


int encodeur_lire() {
  Etat_capteur = digitalRead(A);

  if (Etat_capteur != Etat_capteur_precedant) {
    Etat_capteur_precedant = Etat_capteur;
    n_var++;

    if (n_var == 2) {
      n_var = 0;
      n_a++;

      if (moteurC_en_avant) {
        angle = n_a * DEG_PAR_IMPULSION;

        if (n_a % IMPULSIONS_PAR_TOUR == 0) {
          compteur_tours++;
          Serial.print("Tour complet N° ");
          Serial.println(compteur_tours);
        }

        Serial.print("Angle : ");
        Serial.print(angle);
        Serial.print(" deg | Tours : ");
        Serial.println(compteur_tours);

      } else {
        Serial.println("[ENC] Impulsion ignoree (retour)");
      }
    }
  }

  return angle;
}


// PHASE 1 — INCLINAISON


void phase_inclinaison(int angle_cible) {
  encodeur_reset();

  
  Serial.print("Angle cible : ");
  Serial.print(angle_cible);
  Serial.println(" deg");

  moteurC_avant(VITESSE_INCLINAISON);

  unsigned long t0 = millis();

  while (encodeur_lire() < angle_cible) {
    if ((millis() - t0) > TIMEOUT_MOTEUR) {
      Serial.println("TIMEOUT !");
      break;
    }
    delayMicroseconds(1000);
  }

  moteurC_stop();

  Serial.print("Angle atteint : ");
  Serial.print(angle);
  Serial.println(" deg");
}


// PHASE 2 — RETRAIT GOUPILLE


void phase_goupille() {
  Serial.println(" PHASE 2 : GOUPILLE ");
  moteurD_avant(VITESSE_GOUPILLE);
  //delay(DUREE_GOUPILLE);
  //moteurD_stop();
  Serial.println("Goupille retiree ");
}

// SEQUENCE COMPLETE


void sequence_complete(int angle_cible) {
 
  Serial.println(" DEBUT SEQUENCE TIR");
  Serial.print(" Angle cible : ");
  Serial.print(angle_cible);
  Serial.println(" deg");


  phase_inclinaison(angle_cible);
  delay(500);
  phase_goupille();
  //delay(1000);
  //phase_retour();

  
  Serial.println("SEQUENCE TERMINEE");
  Serial.print(" Angle final : ");
  Serial.print(angle);
  Serial.print(" deg | Tours : ");
  Serial.println(compteur_tours);

}
void CalculAngle(){
  DistTir = ultrasonic.MeasureInCentimeters();
  angle_calcule = ((DistTir/100) - 0.42 - 0.0192)/0.04976;
  angle_normalise = round(angle_calcule / 5)*5;
  Serial.println(angle_normalise);
}

void Catapulte() {
  CalculAngle();
  sequence_complete(angle_normalise);
  /*
  Etat_capteur = digitalRead(A);
  Serial.print("Etat A = ");
  Serial.println(Etat_capteur);
  delay(1000);
  */
}