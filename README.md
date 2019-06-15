# TER : Bras Robot pour jeu de plateau

Équipe : Berriri Mehdi, Bounab Fayçal, Djema Sofiane, Doglio Arthur

Encadrants : Marie Pelleau, Philippe Renevier

Ce TER s’inscrit dans un projet de jeu de plateau physique multi-joueurs en ligne ou contre une IA. Par exemple, vous jouez 
avec le vrai jeu de Takenoko contre votre IA. Il faut pouvoir déplacer les éléments du jeu pour l’IA, c’est pourquoi vous 
utiliserez un bras robotique. Ce TER a plusieurs objectifs, à savoir :

-L'étude des caractéristiques et librairies disponibles pour l'utilisation des bras robotiques en général et en particulier pour le Joy-IT ROBOT02.

-Développer une librairie de commande du bras de robot Joy-It ROBOT02, ou améliorer une librairie existante.

-Mettre en oeuvre quelques mouvements dans un jeu réel, en fixant les emplacements ou en utilisant une librairie de reconnaissance pour les éléments d'un jeu.


## Comment marche le projet ?

### Installation de L'IDE et la librairie

Tout d'abord nous bossons sur l'IDE d'Arduino du coup voici le lien pour télécharger l'IDE :
https://www.arduino.cc/en/Main/Software#

Ensuite devons télécharger une librairie pour l'ajouter dans la librairie de notre IDE,
cette librairie peut être téléchargé sur le github ci-dessous :

https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library



### Lancer le bras

Pour lancer le projet, on doit d'abord connecter les différents fils du bras à la arduino. 
Une fois cette étape finie on compile puis on téléverse pour lancer le bras. 
Il faut ensuite entrer 3 coordonnées pour lui indiquer l'endroit où il doit se déplacer afin qu'il effectue un mouvement.
Et la valeur 0 pour dire s'il doit prendre un objet ou 1 s'il doit déposer un objet.
Lorsque nous entrons les coordonnées dans le moniteur, il faut séléctionner l'option "pas de fin de ligne".
Le mouvement est composé de 4 étapes, 
chacune d'elles représente la rotation d'un des servo-moteurs(les Servos 4 et 5 sont exclus).

### Demonstration vidéo

[![Alt text](https://img.youtube.com/vi/mupZESk5ud0/0.jpg)](https://www.youtube.com/watch?v=mupZESk5ud0)




