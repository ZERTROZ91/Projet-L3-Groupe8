Robot autonome de suivi de ligne
Description
Ce projet a été réalisé dans le cadre d’un défi de robotique. L’objectif est de concevoir un robot autonome capable de suivre une ligne noire, d’éviter des obstacles, de traverser un tunnel, de détecter une couleur, d’afficher des informations et de lancer une balle dans une cible.

Fonctionnalités
Suivi de ligne autonome à l’aide du capteur Me RGB Line Follower
Évitement d’obstacles à l’aide du capteur à ultrasons et du servomoteur
Traversée autonome du tunnel
Détection de couleur
Affichage de la couleur sur un ruban LED RGB
Chronométrage d’une section du parcours
Affichage de distance sur écran LCD
Lancement d’une balle dans une cible
Matériel utilisé
Arduino Uno
Me RGB Line Follower
Capteur à ultrasons Grove
Servomoteur Grove
Capteur de couleur Grove
Ruban LED RGB Grove
Driver moteur I2C
Écran LCD Grove
Structure du projet
Programme principal
Le fichier principal contient les fonctions setup() et loop(), permettant d’initialiser les différents composants et de gérer l’enchaînement des étapes du parcours.

Suivi de ligne
Le suivi de ligne est réalisé grâce au capteur Me RGB Line Follower. Les données du capteur sont interprétées à l’aide d’une table de vérité afin de déterminer la position de la ligne et d’adapter la vitesse des moteurs pour corriger la trajectoire du robot.

Évitement d’obstacles
L’évitement des obstacles repose sur l’utilisation du capteur à ultrasons associé à un servomoteur. Lorsqu’un obstacle est détecté, le servomoteur oriente le capteur dans différentes directions afin de mesurer l’espace disponible. Le robot choisit ensuite la trajectoire la plus adaptée pour contourner l’obstacle avant de récupérer la ligne.

Traversée du tunnel
Dans le tunnel, le servomoteur et le capteur à ultrasons permettent au robot de mesurer en permanence sa distance par rapport aux parois. Si le robot se rapproche d’un mur, la vitesse des moteurs est ajustée afin de le recentrer dans le tunnel. À la sortie, il recherche puis récupère la ligne noire pour poursuivre son parcours.

Détection de couleur
Le capteur de couleur permet d’identifier la couleur affichée sur le panneau. La couleur détectée est ensuite affichée sur le ruban LED conformément au cahier des charges.

Auteurs
Projet réalisé dans le cadre du concours de robotique 2026.

Tassadit CHAIB

Remarque : ce dépôt a été réalisé depuis le compte GitHub d’un collègue, car je n’ai pas pu accéder à mon compte GitHub personnel au moment de la remise du projet
