# TER : Bras Robot pour jeu de plateau

Équipe : Berriri Mehdi, Bounab Fayçal, Djema Sofiane, Doglio Arthur

Encadrants : Marie Pelleau, Philippe Renevier

Ce TER s’inscrit dans un projet de jeu de plateau physique multi-joueurs en ligne ou contre une IA. Par exemple, vous jouez 
avec le vrai jeu de Takenoko contre votre IA. Il faut pouvoir déplacer les éléments du jeu pour l’IA, c’est pourquoi vous 
utiliserez un bras robotique. Ce TER a plusieurs objectifs, à savoir :

-L'étude des caractéristiques et librairies disponibles pour l'utilisation des bras robotiques en général et en particulier pour le Joy-IT ROBOT02.

-Développer une librairie de commande du bras de robot Joy-It ROBOT02, ou améliorer une librairie existante.

-Mettre en oeuvre quelques mouvements dans un jeu réel, en fixant les emplacements ou en utilisant une librairie de reconnaissance pour les éléments d'un jeu.


## Comment fonctionne le projet ?

### Installation de L'IDE et de la librairie

Nous travaillons sur l'IDE d'Arduino, voici le lien pour télécharger l'IDE :
https://www.arduino.cc/en/Main/Software#

Il faut ensuite télécharger une librairie. Celle-ci peut être télécharger sur lien le github ci-dessous :
https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library


### Utilisation du bras

Pour lancer le projet, on doit d'abord connecter les différents fils du bras à la carte Arduino.
Ils doivent être connecté en les prenant de bas en haut sur les ports 0 à 5 de la carte.
Il faut ensuite séléctionner le type de carte : UNO WIFI REV2.
Dans le fichier arduino_secrets.h, il faut écrire le nom de votre réseau ainsi que le mot de passe.
Une fois ces étape finies, on téléverse le code dans la carte. 
On attend que la carte se connecte à votre réseau.
Puis on connecte l'ordinateur au même réseau que la carte et on entre dans le navigateur l'IP du réseau wifi (l'adresse s'affiche sur la console de l'IDE).
Enfin, on entre le coup qu'on veut jouer et on appuie sur "Envoyer".


### Demonstration vidéo

[![Alt text](https://img.youtube.com/vi/mupZESk5ud0/0.jpg)](https://www.youtube.com/watch?v=mupZESk5ud0)




